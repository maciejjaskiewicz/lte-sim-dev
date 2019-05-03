#ifndef SIMULATION_H
#define SIMULATION_H

#include "core/Core.h"
#include "core/eventScheduler/calendar.h"
#include "flows/application/Application.h"
#include "protocolStack/packet/Packet.h"

#include "vector"

class LTE_SIM_API Simulation
{
public:
	Simulation();
	virtual ~Simulation();

	void Run();
	void Stop();
	void ScheduleStop(double time);
	void virtual OnTransmit(Packet& packet, int applicationId) = 0;
	void virtual OnReceive(Packet& packet, int applicationId) = 0;

	double Now() const;
	int GenerateNewUID();

	void AddApplication(std::unique_ptr<Application> application);
	Application* GetApplication(int applicationId) const;
	Calendar& GetCalendar() const;
	static Simulation& Get();

private:
	static Simulation* s_Instance;
	std::vector<std::unique_ptr<Application>> m_Applications;
	std::unique_ptr<Calendar> m_Calendar;
	double m_CurrentTimeStamp;
	int m_LastUID;
	bool m_Running = false;
};

#endif /* SIMULATION_H */