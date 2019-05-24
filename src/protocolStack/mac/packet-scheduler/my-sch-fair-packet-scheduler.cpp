#include "my-sch-fair-packet-scheduler.h"
#include "flows/radio-bearer.h"
#include "protocolStack/rrc/rrc-entity.h"
#include "protocolStack/mac/mac-entity.h"
#include "device/NetworkNode.h"
#include "flows/application/Application.h"
#include "device/ENodeB.h"
#include "protocolStack/mac/AMCModule.h"
#include "phy/lte-phy.h"
#include "core/spectrum/bandwidth-manager.h"
#include "utility/eesm-effective-sinr.h"

#include <map>

MY_SCH_FAIR_PacketScheduler::MY_SCH_FAIR_PacketScheduler()
{
	SetMacEntity(0);
	CreateFlowsToSchedule();
}

MY_SCH_FAIR_PacketScheduler::~MY_SCH_FAIR_PacketScheduler()
{
	Destroy();
}

void MY_SCH_FAIR_PacketScheduler::DoSchedule()
{
	UpdateAverageTransmissionRate();
	SelectFlowsToScheduleFair();

	if (!GetFlowsToSchedule()->empty())
	{
		RBsAllocation();
		FinalizeAllocation();
	} 
	else
	{
		m_UserIdsScheduledInPrevTTI.clear();
	}

	StopSchedule();
}

void MY_SCH_FAIR_PacketScheduler::RBsAllocation()
{
	auto flows = GetFlowsToSchedule(HIGH);
	int nbOfRBs = GetMacEntity()->GetDevice()->GetPhy()->GetBandwidthManager()->GetDlSubChannels().size();

	vector<int> allocatedRBs;
	vector<int> scheduledUsers;

	while(allocatedRBs.size() != nbOfRBs)
	{
		int max = 0;
		int rbToAllocate = 0;
		FlowToSchedule* flowToSchedule = nullptr;

		for (auto& flow : *flows)
		{
			int user = flow->GetUserNetworkNodeId();
			if (std::find(scheduledUsers.begin(), scheduledUsers.end(), user) != scheduledUsers.end()) continue;

			for(int j = 0; j < nbOfRBs; j++)
			{
				if (m_CQIFeedbackMatrix[user][j] > max)
				{
					max = m_CQIFeedbackMatrix[user][j];
					flowToSchedule = flow;
					rbToAllocate = j;
				}
			}
		}

		if(flowToSchedule != nullptr)
		{
			scheduledUsers.push_back(flowToSchedule->GetUserNetworkNodeId());
			flowToSchedule->GetListOfAllocatedRBs()->push_back(rbToAllocate);
			allocatedRBs.push_back(rbToAllocate);
		}
		else
		{
			break;
		}
	}

	// Find free RBs
	vector<int> freeRBs;

	for(int i = 0; i < nbOfRBs; i++)
	{
		if (std::find(allocatedRBs.begin(), allocatedRBs.end(), i) == allocatedRBs.end())
		{
			freeRBs.push_back(i);
		}
	}

	if (freeRBs.empty()) return;

	// Normal RBsAlocation
	auto lowPriorityFlows = GetFlowsToSchedule(LOW);
	std::vector<std::vector<double>> metrics(freeRBs.size(), std::vector<double>(lowPriorityFlows->size()));

	for(int i = 0; i < freeRBs.size(); i++)
	{
		for (int j = 0; j < lowPriorityFlows->size(); j++)
		{
			metrics[i][j] = ComputeSchedulingMetric(lowPriorityFlows->at(j)->GetBearer(),
				lowPriorityFlows->at(j)->GetSpectralEfficiency().at(i), i);
		}
	}

	auto amc = GetMacEntity()->GetAmcModule();
	double l_dAllocatedRBCounter = 0;

	bool * l_bFlowScheduled = new bool[lowPriorityFlows->size()];
	int l_iScheduledFlows = 0;
	auto l_bFlowScheduledSINR = new std::vector<double>[lowPriorityFlows->size()];
	for (int k = 0; k < lowPriorityFlows->size(); k++) l_bFlowScheduled[k] = false;

	for (int s = 0; s < freeRBs.size(); s++)
	{
		if (l_iScheduledFlows == lowPriorityFlows->size()) break;

		double targetMetric = 0;
		bool RBIsAllocated = false;
		FlowToSchedule* scheduledFlow;
		int l_iScheduledFlowIndex = 0;

		for (int k = 0; k < lowPriorityFlows->size(); k++)
		{
			if (metrics[s][k] > targetMetric && !l_bFlowScheduled[k])
			{
				targetMetric = metrics[s][k];
				RBIsAllocated = true;
				scheduledFlow = lowPriorityFlows->at(k);
				l_iScheduledFlowIndex = k;
			}
		}

		if (RBIsAllocated)
		{
			l_dAllocatedRBCounter++;
			scheduledFlow->GetListOfAllocatedRBs()->push_back(s);

			double sinr = amc->GetSinrFromCQI(scheduledFlow->GetCqiFeedbacks().at(s));
			l_bFlowScheduledSINR[l_iScheduledFlowIndex].push_back(sinr);

			double effectiveSinr = GetEesmEffectiveSinr(l_bFlowScheduledSINR[l_iScheduledFlowIndex]);
			int mcs = amc->GetMCSFromCQI(amc->GetCQIFromSinr(effectiveSinr));
			int transportBlockSize = amc->GetTBSizeFromMCS(mcs, scheduledFlow->GetListOfAllocatedRBs()->size());
			if (transportBlockSize >= scheduledFlow->GetDataToTransmit() * 8)
			{
				l_bFlowScheduled[l_iScheduledFlowIndex] = true;
				l_iScheduledFlows++;
			}
		}
	}

	delete[] l_bFlowScheduled;
	delete[] l_bFlowScheduledSINR;
}

void MY_SCH_FAIR_PacketScheduler::FinalizeAllocation()
{
	auto pdcchMsg = new PdcchMapIdealControlMessage();
	auto amc = GetMacEntity()->GetAmcModule();
	auto flows = GetFlowsToSchedule();

	for (auto it = flows->begin(); it != flows->end(); it++)
	{
		auto flow = (*it);
		if (!flow->GetListOfAllocatedRBs()->empty())
		{
			//this flow has been scheduled
			std::vector<double> estimatedSinrValues;
			for (int rb = 0; rb < flow->GetListOfAllocatedRBs()->size(); rb++)

			{
				double sinr = amc->GetSinrFromCQI(
					flow->GetCqiFeedbacks().at(flow->GetListOfAllocatedRBs()->at(rb)));

				estimatedSinrValues.push_back(sinr);
			}

			//compute the effective sinr
			double effectiveSinr = GetEesmEffectiveSinr(estimatedSinrValues);

			//get the MCS for transmission
			int mcs = amc->GetMCSFromCQI(amc->GetCQIFromSinr(effectiveSinr));

			//define the amount of bytes to transmit
			//int transportBlockSize = amc->GetTBSizeFromMCS (mcs);
			int transportBlockSize = amc->GetTBSizeFromMCS(mcs, flow->GetListOfAllocatedRBs()->size());
			double bitsToTransmit = transportBlockSize;
			flow->UpdateAllocatedBits(bitsToTransmit);

			//create PDCCH messages
			for (int rb = 0; rb < flow->GetListOfAllocatedRBs()->size(); rb++)
			{
				pdcchMsg->AddNewRecord(PdcchMapIdealControlMessage::DOWNLINK,
					flow->GetListOfAllocatedRBs()->at(rb),
					flow->GetBearer()->GetDestination(),
					mcs);
			}
		}
	}

	if (!pdcchMsg->GetMessage()->empty())
	{
		GetMacEntity()->GetDevice()->GetPhy()->SendIdealControlMessage(pdcchMsg);
	}

	delete pdcchMsg;
}

double MY_SCH_FAIR_PacketScheduler::ComputeSchedulingMetric(RadioBearer* bearer, 
	double spectralEfficiency, int subChannel)
{
	return (spectralEfficiency * 180000.) / bearer->GetAverageTransmissionRate();
}

void MY_SCH_FAIR_PacketScheduler::SelectFlowsToScheduleFair()
{
	ClearFlowsToSchedule();

	auto rrc = GetMacEntity()->GetDevice()->GetProtocolStack()->GetRrcEntity();
	const auto bearers = rrc->GetRadioBearerContainer();

	for (auto bearer : *bearers)
	{
		const auto userNetworkNodeId = bearer->GetDestination()->GetIDNetworkNode();

		if(!CanBeScheduleInCurrentTTI(*bearer, userNetworkNodeId))
		{
			continue;
		}

		const auto priority = WasScheduledInPreviousTTI(userNetworkNodeId) ? LOW : HIGH;
		const auto dataToTransmit = GetSizeOfDataToTransmit(*bearer);

		auto enb = dynamic_cast<ENodeB*>(GetMacEntity()->GetDevice());
		const auto ueRecord = enb->GetUserEquipmentRecord(userNetworkNodeId);

		const auto cqiFeedback = ueRecord->GetCQI();
		const auto spectralEfficiency = CalculateSpectralEfficiency(cqiFeedback);

		UpdateCQIFeedbackMatrix(userNetworkNodeId, cqiFeedback);
		InsertFlowToSchedule(bearer, dataToTransmit, spectralEfficiency, 
			cqiFeedback, userNetworkNodeId, priority);

		m_UserIdsScheduledInPrevTTI.push_back(userNetworkNodeId);
	}
}

int MY_SCH_FAIR_PacketScheduler::GetSizeOfDataToTransmit(RadioBearer& bearer)
{
	int dataToTransmit;

	if (bearer.GetApplication()->GetApplicationType() == Application::APPLICATION_TYPE_INFINITE_BUFFER)
	{
		dataToTransmit = 100000000;
	}
	else
	{
		dataToTransmit = bearer.GetQueueSize();
	}

	return dataToTransmit;
}

std::vector<double> MY_SCH_FAIR_PacketScheduler::CalculateSpectralEfficiency(const std::vector<int>& cqiFeedback)
{
	std::vector<double> spectralEfficiency;

	for (int cqiFb : cqiFeedback)
	{
		double sEff = GetMacEntity()->GetAmcModule()->GetEfficiencyFromCQI(cqiFb);
		spectralEfficiency.push_back(sEff);
	}

	return spectralEfficiency;
}

bool MY_SCH_FAIR_PacketScheduler::CanBeScheduleInCurrentTTI(RadioBearer& bearer, int userNetworkNodeId)
{
	return bearer.HasPackets() && bearer.GetDestination()->GetNodeState() == NetworkNode::STATE_ACTIVE;
}

bool MY_SCH_FAIR_PacketScheduler::WasScheduledInPreviousTTI(int userNetworkNodeId)
{
	return std::find(m_UserIdsScheduledInPrevTTI.begin(), m_UserIdsScheduledInPrevTTI.end(), 
		userNetworkNodeId) != m_UserIdsScheduledInPrevTTI.end();
}

void MY_SCH_FAIR_PacketScheduler::UpdateCQIFeedbackMatrix(int destinationNetworkNodeId, std::vector<int> cqiFeedback)
{
	if (m_CQIFeedbackMatrix.find(destinationNetworkNodeId) != m_CQIFeedbackMatrix.end())
	{
		m_CQIFeedbackMatrix[destinationNetworkNodeId] = cqiFeedback;
	} 
	else
	{
		m_CQIFeedbackMatrix.insert(make_pair(destinationNetworkNodeId, cqiFeedback));
	}
}