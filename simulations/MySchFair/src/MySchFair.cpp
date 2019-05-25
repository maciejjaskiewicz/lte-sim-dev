#define LTE_SIM_CUSTOM_MAIN

#include <iostream>
#include <LTE-Sim.h>
#include "utility/seed.h"
#include "utility/CellPosition.h"
#include "utility/frequency-reuse-helper.h"
#include "utility/RandomVariable.h"
#include "utility/PacketHelper.h"
#include "output/SimulationMetricsCalculator.h"
#include "output/Models/SimulationMetricsModel.h"

class MySchFair : public Simulation
{
public:
	MySchFair(int nbUE = 10)
	{
		//Config
		int nbCells = 1;
		double radius = 1;
		int nbVoIP = 1;
		int nbVideo = 1;
		int nbBE = 1;
		int nbCBR = 1;
		int speed = 3;
		double maxDelay = 0.1;
		//End Config

		double duration = 2;
		double flow_duration = 10;

		int cluster = 3;
		double bandwidth = 10;

		NetworkManager* networkManager = NetworkManager::Init();
		FrameManager *frameManager = FrameManager::Init();

		int commonSeed = GetCommonSeed(0);
		srand(commonSeed);

		auto downlink_scheduler_type = ENodeB::DLScheduler_MY_SCH_FAIR;
		auto frame_structure = FrameManager::FRAME_STRUCTURE_FDD;

		frameManager->SetFrameStructure(frame_structure);

		//create cells
		std::vector <Cell*> *cells = new std::vector <Cell*>;
		for (int i = 0; i < nbCells; i++)
		{
			CartesianCoordinates center =
				GetCartesianCoordinatesForCell(i, radius * 1000.);

			Cell *c = new Cell(i, radius, 0.035, center.GetCoordinateX(), center.GetCoordinateY());
			cells->push_back(c);
			networkManager->GetCellContainer()->push_back(c);

			std::cout << "Created Cell, id " << c->GetIdCell()
				<< ", position: " << c->GetCellCenterPosition()->GetCoordinateX()
				<< " " << c->GetCellCenterPosition()->GetCoordinateY() << std::endl;
		}

		std::vector <BandwidthManager*> spectrums = RunFrequencyReuseTechniques(nbCells, cluster, bandwidth);

		// Create a set of a couple of channels
		std::vector <LteChannel*> *dlChannels = new std::vector <LteChannel*>;
		std::vector <LteChannel*> *ulChannels = new std::vector <LteChannel*>;
		for (int i = 0; i < nbCells; i++)
		{
			LteChannel *dlCh = new LteChannel();
			dlCh->SetChannelId(i);
			dlChannels->push_back(dlCh);

			LteChannel *ulCh = new LteChannel();
			ulCh->SetChannelId(i);
			ulChannels->push_back(ulCh);
		}

		//create eNBs
		std::vector <ENodeB*> *eNBs = new std::vector <ENodeB*>;
		for (int i = 0; i < nbCells; i++)
		{
			ENodeB* enb = new ENodeB(i, cells->at(i));
			enb->GetPhy()->SetDlChannel(dlChannels->at(i));
			enb->GetPhy()->SetUlChannel(ulChannels->at(i));

			enb->SetDLScheduler(downlink_scheduler_type);

			enb->GetPhy()->SetBandwidthManager(spectrums.at(i));

			std::cout << "Created enb, id " << enb->GetIDNetworkNode()
				<< ", cell id " << enb->GetCell()->GetIdCell()
				<< ", position: " << enb->GetMobilityModel()->GetAbsolutePosition()->GetCoordinateX()
				<< " " << enb->GetMobilityModel()->GetAbsolutePosition()->GetCoordinateY()
				<< ", channels id " << enb->GetPhy()->GetDlChannel()->GetChannelId()
				<< enb->GetPhy()->GetUlChannel()->GetChannelId() << std::endl;

			spectrums.at(i)->Print();


			ulChannels->at(i)->AddDevice((NetworkNode*)enb);


			networkManager->GetENodeBContainer()->push_back(enb);
			eNBs->push_back(enb);
		}

		int voipApplication = 0;
		int cbrApplication = 0;
		int beApplication = 0;
		int destinationPort = 101;
		int applicationID = 0;

		//Create GW
		Gateway *gw = new Gateway();
		networkManager->GetGatewayContainer()->push_back(gw);

		//Create UEs
		int idUE = nbCells;
		for (int i = 0; i < nbUE; i++)
		{
			//ue's random position
			double posX = (double)rand() / RAND_MAX; posX = 0.95 *
				(((2 * radius * 1000)*posX) - (radius * 1000));
			double posY = (double)rand() / RAND_MAX; posY = 0.95 *
				(((2 * radius * 1000)*posY) - (radius * 1000));

			double speedDirection = GetRandomVariable(360.) * ((2.*3.14) / 360.);

			UserEquipment* ue = new UserEquipment(idUE,
				posX, posY, speed, speedDirection,
				cells->at(0),
				eNBs->at(0),
				0, //handover false!
				Mobility::RANDOM_DIRECTION);

			std::cout << "Created UE - id " << idUE << " position " << posX << " " << posY << " direction " << speedDirection << std::endl;

			ue->GetMobilityModel()->GetAbsolutePosition()->Print();
			ue->GetPhy()->SetDlChannel(eNBs->at(0)->GetPhy()->GetDlChannel());
			ue->GetPhy()->SetUlChannel(eNBs->at(0)->GetPhy()->GetUlChannel());

			FullbandCqiManager *cqiManager = new FullbandCqiManager();
			cqiManager->SetCqiReportingMode(CqiManager::PERIODIC);
			cqiManager->SetReportingInterval(1);
			cqiManager->SetDevice(ue);
			ue->SetCqiManager(cqiManager);

			WidebandCqiEesmErrorModel *errorModel = new WidebandCqiEesmErrorModel();
			ue->GetPhy()->SetErrorModel(errorModel);

			networkManager->GetUserEquipmentContainer()->push_back(ue);

			// register ue to the enb
			eNBs->at(0)->RegisterUserEquipment(ue);

			// define the channel realization
			MacroCellUrbanAreaChannelRealization* c_dl = new MacroCellUrbanAreaChannelRealization(eNBs->at(0), ue);
			eNBs->at(0)->GetPhy()->GetDlChannel()->GetPropagationLossModel()->AddChannelRealization(c_dl);
			MacroCellUrbanAreaChannelRealization* c_ul = new MacroCellUrbanAreaChannelRealization(ue, eNBs->at(0));
			eNBs->at(0)->GetPhy()->GetUlChannel()->GetPropagationLossModel()->AddChannelRealization(c_ul);


			// CREATE DOWNLINK APPLICATION FOR THIS UE
			double start_time = 0.1 + GetRandomVariable(5.);
			double duration_time = start_time + flow_duration;

			// *** voip application
			for (int j = 0; j < nbVoIP; j++)
			{
				auto voIPApp = ApplicationFactory::CreateApplication<VoIP>(
					applicationID,
					gw, ue,
					0, destinationPort,
					TransportProtocol::TRANSPORT_PROTOCOL_TYPE_UDP,
					start_time,
					duration_time
				);

				// create qos parameters
				if (downlink_scheduler_type == ENodeB::DLScheduler_TYPE_FLS)
				{
					QoSForFLS *qos = new QoSForFLS();
					qos->SetMaxDelay(maxDelay);
					if (maxDelay == 0.1)
					{
						std::cout << "Target Delay = 0.1 s, M = 9" << std::endl;
						qos->SetNbOfCoefficients(9);
					}
					else if (maxDelay == 0.08)
					{
						std::cout << "Target Delay = 0.08 s, M = 7" << std::endl;
						qos->SetNbOfCoefficients(7);
					}
					else if (maxDelay == 0.06)
					{
						std::cout << "Target Delay = 0.06 s, M = 5" << std::endl;
						qos->SetNbOfCoefficients(5);
					}
					else if (maxDelay == 0.04)
					{
						std::cout << "Target Delay = 0.04 s, M = 3" << std::endl;
						qos->SetNbOfCoefficients(3);
					}
					else
					{
						std::cout << "ERROR: target delay is not available" << std::endl;
						return;
					}

					voIPApp->SetQoSParameters(qos);
				}
				else if (downlink_scheduler_type == ENodeB::DLScheduler_TYPE_EXP)
				{
					QoSForEXP *qos = new QoSForEXP();
					qos->SetMaxDelay(maxDelay);
					voIPApp->SetQoSParameters(qos);
				}
				else if (downlink_scheduler_type == ENodeB::DLScheduler_TYPE_MLWDF)
				{
					QoSForM_LWDF *qos = new QoSForM_LWDF();
					qos->SetMaxDelay(maxDelay);
					voIPApp->SetQoSParameters(qos);
				}
				else
				{
					QoSParameters *qos = new QoSParameters();
					qos->SetMaxDelay(maxDelay);
					voIPApp->SetQoSParameters(qos);
				}

				//create classifier parameters
				ClassifierParameters *cp = new ClassifierParameters(gw->GetIDNetworkNode(),
					ue->GetIDNetworkNode(),
					0,
					destinationPort,
					TransportProtocol::TRANSPORT_PROTOCOL_TYPE_UDP);
				voIPApp->SetClassifierParameters(cp);

				AddApplication(std::move(voIPApp));
				std::cout << "CREATED VOIP APPLICATION, ID " << applicationID << std::endl;

				//update counter
				destinationPort++;
				applicationID++;
				voipApplication++;
			}

			// *** be application
			for (int j = 0; j < nbBE; j++)
			{
				auto beApp = ApplicationFactory::CreateApplication<InfiniteBuffer>(
					applicationID,
					gw, ue,
					0, destinationPort,
					TransportProtocol::TRANSPORT_PROTOCOL_TYPE_UDP,
					start_time,
					duration_time
				);

				// create qos parameters
				auto*qosParameters = new QoSParameters();
				beApp->SetQoSParameters(qosParameters);

				//create classifier parameters
				auto*cp = new ClassifierParameters(gw->GetIDNetworkNode(),
					ue->GetIDNetworkNode(),
					0,
					destinationPort,
					TransportProtocol::TRANSPORT_PROTOCOL_TYPE_UDP);
				beApp->SetClassifierParameters(cp);

				AddApplication(std::move(beApp));
				std::cout << "CREATED BE APPLICATION, ID " << applicationID << std::endl;

				//update counter
				destinationPort++;
				applicationID++;
				beApplication++;
			}

			// *** cbr application
			for (int j = 0; j < nbCBR; j++)
			{
				auto cbrApp = ApplicationFactory::CreateApplication<CBR>(
					applicationID,
					gw, ue,
					0, destinationPort,
					TransportProtocol::TRANSPORT_PROTOCOL_TYPE_UDP,
					start_time,
					duration_time
				);

				cbrApp->SetInterval(0.04);
				cbrApp->SetSize(5);

				// create qos parameters
				QoSParameters *qosParameters = new QoSParameters();
				qosParameters->SetMaxDelay(maxDelay);

				cbrApp->SetQoSParameters(qosParameters);


				//create classifier parameters
				ClassifierParameters *cp = new ClassifierParameters(gw->GetIDNetworkNode(),
					ue->GetIDNetworkNode(),
					0,
					destinationPort,
					TransportProtocol::TRANSPORT_PROTOCOL_TYPE_UDP);
				cbrApp->SetClassifierParameters(cp);

				AddApplication(std::move(cbrApp));
				std::cout << "CREATED CBR APPLICATION, ID " << applicationID << std::endl;

				//update counter
				destinationPort++;
				applicationID++;
				cbrApplication++;
			}

			idUE++;
		}

		m_CSVOutputBuilder = new CSVOutputBuilder("MY_SCH_FAIR.csv");
		m_MetricsCalculator = new SimulationMetricsCalculator(nbUE, duration);
		m_SimulationMetricsResult = new SimulationMetricsModel(nbUE, downlink_scheduler_type);

		ScheduleStop(duration);
		Run();
	}

	void OnTransmit(Packet& packet, PacketAttributes& packetAttr) override
	{
		auto app = GetApplication(packetAttr.GetApplicationId());
		auto destination = app->GetDestination();
		bool isIndoor = false;

		if (destination->GetNodeType() == NetworkNode::TYPE_UE)
		{
			auto ue = dynamic_cast<UserEquipment*>(destination);
			isIndoor = ue->IsIndoor();
		}

		auto output = OutputFactory::CreateTXOutputModel(
			packet.GetID(),
			app->GetApplicationType(),
			destination->GetNodeType(),
			packetAttr.GetBearerId(),
			packetAttr.GetSize(),
			packetAttr.GetSourceId(),
			packetAttr.GetDestinationId(),
			packetAttr.GetCreatedTime(),
			isIndoor
		);

		m_MetricsCalculator->Add(*output);
		m_CSVOutputBuilder->Add(std::move(output));
	}

	void OnReceive(Packet& packet, PacketAttributes& packetAttr) override
	{
		auto app = GetApplication(packetAttr.GetApplicationId());
		auto ue = dynamic_cast<UserEquipment*>(app->GetDestination());

		auto output = OutputFactory::CreateRXOutputModel(
			packet.GetID(),
			app->GetApplicationType(),
			app->GetApplicationID(),
			packet.GetPacketTags()->GetApplicationSize(),
			packet.GetSourceID(),
			packet.GetDestinationID(),
			CalculateDelay(packet),
			ue->IsIndoor()
		);

		m_MetricsCalculator->Add(*output);
		m_CSVOutputBuilder->Add(std::move(output));
	}

	void OnStop() override
	{
		m_CSVOutputBuilder->Close();

		const auto delay = m_MetricsCalculator->CalculateDelay();
		const auto throughput = m_MetricsCalculator->CalculateThroughput();
		const auto fairness = m_MetricsCalculator->CalculateFairness();

		m_SimulationMetricsResult->SetDelay(delay);
		m_SimulationMetricsResult->SetThroughput(throughput);
		m_SimulationMetricsResult->SetFairness(fairness);
	}

	const SimulationMetricsModel& GetSimulationResult() const
	{
		return *m_SimulationMetricsResult;
	}

private:
	CSVOutputBuilder* m_CSVOutputBuilder;
	SimulationMetricsCalculator* m_MetricsCalculator;
	SimulationMetricsModel* m_SimulationMetricsResult;
};

int main(int argc, char** argv)
{
	for(int i = 10; i <= 100; i += 10)
	{
		auto simulation = new MySchFair(i);
		auto result = simulation->GetSimulationResult();

		std::cout << result.ToString(STDOUT) << std::endl;

		delete simulation;

		//TODO: Refactor
		delete NetworkManager::Init();
		delete FrameManager::Init();
	}

	return 0;
}