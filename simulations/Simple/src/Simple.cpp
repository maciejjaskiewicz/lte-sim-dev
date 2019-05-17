#include <iostream>
#include <LTE-Sim.h>

class Simple : public Simulation
{
public:
	Simple()
	{
		NetworkManager* networkManager = NetworkManager::Init();
		FrameManager *frameManager = FrameManager::Init();

		LteChannel *dlCh = new LteChannel();
		LteChannel *ulCh = new LteChannel();

		BandwidthManager* spectrum = new BandwidthManager(5, 5, 0, 0);

		int idCell = 0;
		int radius = 1; //km
		int minDistance = 0.0035; //km
		int posX = 0;
		int posY = 0;
		Cell* cell = networkManager->CreateCell(idCell, radius, minDistance, posX, posY);

		int idEnb = 1;
		ENodeB* enb = networkManager->CreateEnodeb(idEnb, cell, posX, posY, dlCh, ulCh, spectrum);
		enb->SetDLScheduler(ENodeB::DLScheduler_TYPE_PROPORTIONAL_FAIR);

		Gateway *gw = networkManager->CreateGateway();

		int idUe = 2;
		int posX_ue = 40; //m
		int posY_ue = 0;  //m
		int speed = 3;    //km/h
		double speeDirection = 0;
		UserEquipment* ue = networkManager->CreateUserEquipment(idUe, posX_ue, posY_ue, speed, speeDirection, cell, enb);

		QoSParameters *qos = new QoSParameters();
		int applicationID = 0;
		int srcPort = 0;
		int dstPort = 100;
		double startTime = 0.1; //s
		double stopTime = 0.12;  //s

		auto application = ApplicationFactory::CreateApplication(
			Application::APPLICATION_TYPE_INFINITE_BUFFER,
			applicationID,
			gw, ue,
			srcPort, dstPort,
			TransportProtocol::TRANSPORT_PROTOCOL_TYPE_UDP,
			qos,
			startTime, stopTime);

		AddApplication(std::move(application));

		ScheduleStop(0.13);
		Run();
	}

	void OnTransmit(Packet& packet, PacketAttributes& packetAttr) override
	{
		std::cout << "OnTransmit:";
		std::cout << "TX ";

		auto app = GetApplication(packetAttr.GetApplicationId());
		auto appType = ApplicationTypeToString(app->GetApplicationType());
		auto destination = app->GetDestination();

		std::cout << appType << " ID " << packet.GetID()
			<< " B " << packetAttr.GetBearerId()
			<< " SIZE " << packetAttr.GetSize()
			<< " SRC " << packetAttr.GetSourceId()
			<< " DST " << packetAttr.GetDestinationId()
			<< " T " << packetAttr.GetCreatedTime();

		if(destination->GetNodeType() == NetworkNode::TYPE_UE)
		{
			auto ue = dynamic_cast<UserEquipment*>(destination);
			std::cout << " " << ue->IsIndoor() << std::endl;
		}
	}

	void OnReceive(Packet& packet, PacketAttributes& packetAttr) override
	{
		std::cout << "OnReceive: ";
		std::cout << "RX ";

		auto app = GetApplication(packetAttr.GetApplicationId());

		auto appType = ApplicationTypeToString(app->GetApplicationType());
		auto delay = CalculateDelay(packet);
		auto ue = dynamic_cast<UserEquipment*>(app->GetDestination());

		std::cout << appType << " ID " << packet.GetID()
			<< " B " << app->GetApplicationID()
			<< " SIZE " << packet.GetPacketTags()->GetApplicationSize()
			<< " SRC " << packet.GetSourceID()
			<< " DST " << packet.GetDestinationID()
			<< " D " << delay
			<< " " << ue->IsIndoor() << std::endl;
		
	}
private:
	static std::string ApplicationTypeToString(Application::ApplicationType applicationType)
	{
		switch (applicationType)
		{
			case Application::APPLICATION_TYPE_VOIP: return "VOIP";
			case Application::APPLICATION_TYPE_TRACE_BASED: return "VIDEO";
			case Application::APPLICATION_TYPE_CBR: return "CBR";
			case Application::APPLICATION_TYPE_INFINITE_BUFFER: return "INF_BUF";
			default: return "UNDEFINED";
		}
	}

	double CalculateDelay(Packet& packet) const
	{
		double delay = (Now() * 10000 - packet.GetTimeStamp() * 10000) / 10000;
		if (delay < 0.000001) delay = 0.000001;

		return delay;
	}
};

Simulation* CreateSimulation()
{
	return new Simple();
}