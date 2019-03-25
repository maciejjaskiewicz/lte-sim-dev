#include "Simulation.h"

#include "core/eventScheduler/make-event.h"

Simulation* Simulation::s_Instance = nullptr;

Simulation::Simulation() : m_Application(nullptr), 
	m_CurrentTimeStamp(0), m_LastUID(-1)
{
	s_Instance = this;
	m_Calendar = std::make_unique<Calendar>();
}

Simulation::~Simulation() = default;

void Simulation::Run(std::unique_ptr<Application> application)
{
	m_Application = std::move(application);
	m_Running = true;

	while(m_Running && !m_Calendar->IsEmpty())
	{
		const auto nextEvent = m_Calendar->GetEvent();

		m_CurrentTimeStamp = nextEvent->GetTimeStamp();
		nextEvent->RunEvent();

		m_Calendar->RemoveEvent();
	}
}

void Simulation::Stop()
{
	// TODO: Logging
	m_Running = false;
}

void Simulation::ScheduleStop(double time)
{
	// TODO: Logging
	m_Calendar->Schedule(time, MakeEvent(&Simulation::Stop, this));
}

double Simulation::Now() const
{
	return m_CurrentTimeStamp;
}

int Simulation::GenerateNewUID()
{
	if(m_LastUID == -1)
	{
		m_LastUID = 0;
		return m_LastUID;
	}

	m_LastUID++;
	return m_LastUID;
}

Application& Simulation::GetApplication() const
{
	return *m_Application;
}

Calendar& Simulation::GetCalendar() const
{
	return *m_Calendar;
}

Simulation& Simulation::Get()
{
	return *s_Instance;
}
