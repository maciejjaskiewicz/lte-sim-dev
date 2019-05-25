#include "Simulation.h"

#include "core/eventScheduler/make-event.h"

Simulation* Simulation::s_Instance = nullptr;

Simulation::Simulation() : m_CurrentTimeStamp(0), m_LastUID(-1)
{
	s_Instance = this;
	m_Calendar = std::make_unique<Calendar>();
}

Simulation::~Simulation()
{
	m_Calendar.reset();

	m_Applications.clear();
	s_Instance = nullptr;
}

void Simulation::Run()
{
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
	OnStop();
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

void Simulation::AddApplication(std::unique_ptr<Application> application)
{
	m_Applications.push_back(std::move(application));
	auto& app = m_Applications.back();

	// TODO:
	/*GetCalendar().Schedule(
		app->GetStartTime(),
		&Application::Start, 
		application.get()
	);

	GetCalendar().Schedule(
		app->GetStopTime() + 0.1,
		&Application::Stop, 
		application.get()
	);*/
}

Application* Simulation::GetApplication(const int applicationId) const
{
	for(auto& app : m_Applications)
	{
		if (app->GetApplicationID() == applicationId)
			return app.get();
	}

	return nullptr;
}

Calendar& Simulation::GetCalendar() const
{
	return *m_Calendar;
}

Simulation& Simulation::Get()
{
	return *s_Instance;
}
