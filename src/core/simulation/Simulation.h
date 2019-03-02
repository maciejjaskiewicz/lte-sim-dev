#ifndef SIMULATION_H
#define SIMULATION_H

#include "core/Core.h"
#include "flows/application/Application.h"
#include "protocolStack/packet/Packet.h"

class LTE_SIM_API Simulation
{
public:
	Simulation();
	virtual ~Simulation();

	void Run(std::unique_ptr<Application> application);
	void virtual OnPacket(Packet& packet) {}

	Application& GetApplication();
	static Simulation& Get();

private:
	static Simulation* s_Instace;
	std::unique_ptr<Application> m_Application;
};

#endif /* SIMULATION_H */