#ifndef SIMULATION_H
#define SIMULATION_H

#include "core/Core.h"
#include "core/eventScheduler/calendar.h"
#include "flows/application/Application.h"
#include "protocolStack/packet/Packet.h"

class LTE_SIM_API Simulation
{
public:
	Simulation();
	virtual ~Simulation();

	void Run(std::unique_ptr<Application> application);
	void Stop();
	void ScheduleStop(double time);
	void virtual OnPacket(Packet& packet) {}

	double Now() const;
	int GenerateNewUID();

	Application& GetApplication() const;
	Calendar& GetCalendar() const;
	static Simulation& Get();

private:
	static Simulation* s_Instance;
	std::unique_ptr<Application> m_Application;
	std::unique_ptr<Calendar> m_Calendar;
	double m_CurrentTimeStamp;
	int m_LastUID;
	bool m_Running = false;
};

#endif /* SIMULATION_H */