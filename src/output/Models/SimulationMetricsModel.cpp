#include "SimulationMetricsModel.h"

#include <sstream>

SimulationMetricsModel::SimulationMetricsModel(int usersNumber, ENodeB::DLSchedulerType scheduler)
	: m_UsersNumber(usersNumber), m_Scheduler(scheduler)
{
}

SimulationMetricsModel::SimulationMetricsModel(int usersNumber, ENodeB::DLSchedulerType scheduler, float delay,
	float throughput, float fairness) : m_UsersNumber(usersNumber), m_Scheduler(scheduler), 
	m_Delay(delay), m_Throughput(throughput), m_Fairness(fairness)
{
}

void SimulationMetricsModel::SetDelay(float delay)
{
	m_Delay = delay;
}

void SimulationMetricsModel::SetThroughput(float throughput)
{
	m_Throughput = throughput;
}

void SimulationMetricsModel::SetFairness(float fairness)
{
	m_Fairness = fairness;
}

int SimulationMetricsModel::GetUsersNumber() const
{
	return m_UsersNumber;
}

ENodeB::DLSchedulerType SimulationMetricsModel::GetSchedulerType() const
{
	return m_Scheduler;
}

std::string SimulationMetricsModel::GetSchedulerTypeStr() const
{
	switch (m_Scheduler)
	{
	case ENodeB::DLScheduler_TYPE_MAXIMUM_THROUGHPUT: return "MAXIMUM_THROUGHPUT";
	case ENodeB::DLScheduler_TYPE_FLS: return "FLS";
	case ENodeB::DLScheduler_TYPE_MLWDF: return "MLWDF";
	case ENodeB::DLScheduler_TYPE_EXP: return "EXP";
	case ENodeB::DLScheduler_LOG_RULE: return "LOG_RULE";
	case ENodeB::DLScheduler_EXP_RULE: return "EXP_RULE";
	case ENodeB::DLScheduler_MY_SCH_FAIR: return "MY_SCH_FAIR";
	default: return "";
	}
}

float SimulationMetricsModel::GetDelay() const
{
	return m_Delay;
}

float SimulationMetricsModel::GetThroughput() const
{
	return m_Throughput;
}

float SimulationMetricsModel::GetThroughputMbps() const
{
	return m_Throughput / 1024 / 1024;
}

float SimulationMetricsModel::GetFairness() const
{
	return m_Fairness;
}

std::string SimulationMetricsModel::ToString(OutputStrFormat format) const
{
	stringstream ss;

	if(format == STDOUT)
	{
		ss << "Scheduler: " << GetSchedulerTypeStr() << ", ";
		ss << "Users: " << m_UsersNumber << ", ";
		ss << "Delay: " << m_Delay << ", ";
		ss << "Throughput: " << GetThroughputMbps() << ", ";
		ss << "Fairness:" << m_Fairness;
	}
	else
	{
		ss << GetSchedulerTypeStr() << m_CsvSeparator;
		ss << m_UsersNumber << m_CsvSeparator;
		ss << m_Delay << m_CsvSeparator;
		ss << GetThroughputMbps() << m_CsvSeparator;
		ss << m_Fairness;
	}

	return ss.str();
}

std::string SimulationMetricsModel::GetCSVHeader()
{
	stringstream ss;

	ss << "Scheduler" << m_CsvSeparator;
	ss << "Users" << m_CsvSeparator;
	ss << "Delay" << m_CsvSeparator;
	ss << "Throughput" << m_CsvSeparator;
	ss << "Fairness";

	return ss.str();
}
