#include <iostream>
#include <LTE-Sim.h>
#include "utility/seed.h"
#include "utility/CellPosition.h"
#include "utility/frequency-reuse-helper.h"
#include "utility/RandomVariable.h"
#include "utility/PacketHelper.h"

class MySchFair : public Simulation
{
public:
	MySchFair()
	{
		//Config
		int nbCells = 1;
		double radius = 1;
		int nbUE = 50;
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

		//Define Application Container
		std::vector<VoIP> VoIPApplication(nbVoIP*nbCells*nbUE);
		std::vector<TraceBased> VideoApplication(nbVideo*nbCells*nbUE);
		std::vector<InfiniteBuffer> BEApplication(nbBE*nbCells*nbUE);
		std::vector<CBR> CBRApplication(nbCBR*nbCells*nbUE);

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
				// create application
				VoIPApplication[voipApplication].SetSource(gw);
				VoIPApplication[voipApplication].SetDestination(ue);
				VoIPApplication[voipApplication].SetApplicationID(applicationID);
				VoIPApplication[voipApplication].SetStartTime(start_time);
				VoIPApplication[voipApplication].SetStopTime(duration_time);

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

					VoIPApplication[voipApplication].SetQoSParameters(qos);
				}
				else if (downlink_scheduler_type == ENodeB::DLScheduler_TYPE_EXP)
				{
					QoSForEXP *qos = new QoSForEXP();
					qos->SetMaxDelay(maxDelay);
					VoIPApplication[voipApplication].SetQoSParameters(qos);
				}
				else if (downlink_scheduler_type == ENodeB::DLScheduler_TYPE_MLWDF)
				{
					QoSForM_LWDF *qos = new QoSForM_LWDF();
					qos->SetMaxDelay(maxDelay);
					VoIPApplication[voipApplication].SetQoSParameters(qos);
				}
				else
				{
					QoSParameters *qos = new QoSParameters();
					qos->SetMaxDelay(maxDelay);
					VoIPApplication[voipApplication].SetQoSParameters(qos);
				}


				//create classifier parameters
				ClassifierParameters *cp = new ClassifierParameters(gw->GetIDNetworkNode(),
					ue->GetIDNetworkNode(),
					0,
					destinationPort,
					TransportProtocol::TRANSPORT_PROTOCOL_TYPE_UDP);
				VoIPApplication[voipApplication].SetClassifierParameters(cp);

				std::cout << "CREATED VOIP APPLICATION, ID " << applicationID << std::endl;

				//update counter
				destinationPort++;
				applicationID++;
				voipApplication++;
			}

			// *** be application
			for (int j = 0; j < nbBE; j++)
			{
				// create application
				BEApplication[beApplication].SetSource(gw);
				BEApplication[beApplication].SetDestination(ue);
				BEApplication[beApplication].SetApplicationID(applicationID);
				BEApplication[beApplication].SetStartTime(start_time);
				BEApplication[beApplication].SetStopTime(duration_time);


				// create qos parameters
				QoSParameters *qosParameters = new QoSParameters();
				BEApplication[beApplication].SetQoSParameters(qosParameters);


				//create classifier parameters
				ClassifierParameters *cp = new ClassifierParameters(gw->GetIDNetworkNode(),
					ue->GetIDNetworkNode(),
					0,
					destinationPort,
					TransportProtocol::TRANSPORT_PROTOCOL_TYPE_UDP);
				BEApplication[beApplication].SetClassifierParameters(cp);

				std::cout << "CREATED BE APPLICATION, ID " << applicationID << std::endl;

				//update counter
				destinationPort++;
				applicationID++;
				beApplication++;
			}

			// *** cbr application
			for (int j = 0; j < nbCBR; j++)
			{
				// create application
				CBRApplication[cbrApplication].SetSource(gw);
				CBRApplication[cbrApplication].SetDestination(ue);
				CBRApplication[cbrApplication].SetApplicationID(applicationID);
				CBRApplication[cbrApplication].SetStartTime(start_time);
				CBRApplication[cbrApplication].SetStopTime(duration_time);
				CBRApplication[cbrApplication].SetInterval(0.04);
				CBRApplication[cbrApplication].SetSize(5);

				// create qos parameters
				QoSParameters *qosParameters = new QoSParameters();
				qosParameters->SetMaxDelay(maxDelay);

				CBRApplication[cbrApplication].SetQoSParameters(qosParameters);


				//create classifier parameters
				ClassifierParameters *cp = new ClassifierParameters(gw->GetIDNetworkNode(),
					ue->GetIDNetworkNode(),
					0,
					destinationPort,
					TransportProtocol::TRANSPORT_PROTOCOL_TYPE_UDP);
				CBRApplication[cbrApplication].SetClassifierParameters(cp);

				std::cout << "CREATED CBR APPLICATION, ID " << applicationID << std::endl;

				//update counter
				destinationPort++;
				applicationID++;
				cbrApplication++;
			}

			idUE++;
		}

		for (auto voIpApp : VoIPApplication) AddApplication(std::make_unique<VoIP>(voIpApp));
		for (auto beApp : BEApplication) AddApplication(std::make_unique<InfiniteBuffer>(beApp));
		for (auto cbrApp : CBRApplication) AddApplication(std::make_unique<CBR>(cbrApp));

		m_CSVOutputBuilder = new CSVOutputBuilder("MY_SCH_FAIR.csv");

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

		m_CSVOutputBuilder->Add(std::move(output));
	}

	void OnStop() override
	{
		m_CSVOutputBuilder->Close();
	}

private:
	CSVOutputBuilder* m_CSVOutputBuilder;
};

Simulation* CreateSimulation()
{
	return new MySchFair();
}