#include <LTE-Sim.h>

#include <iostream>

class Simple : public Simulation
{
public:
	Simple()
	{
		Simulator *simulator = Simulator::Init();
		FrameManager *frameManager = FrameManager::Init();
		NetworkManager* networkManager = NetworkManager::Init();
		FlowsManager* flowsManager = FlowsManager::Init();

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
		Application* be = flowsManager->CreateApplication(applicationID,
			gw, ue,
			srcPort, dstPort, TransportProtocol::TRANSPORT_PROTOCOL_TYPE_UDP,
			Application::APPLICATION_TYPE_INFINITE_BUFFER,
			qos,
			startTime, stopTime);

		simulator->SetStop(0.13);
		simulator->Run();
	}

	void OnPacket(Packet& packet) override
	{
		std::cout << "Packet" << std::endl;
	}
};

Simulation* CreateSimulation()
{
	return new Simple();
}