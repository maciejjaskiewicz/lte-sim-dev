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

void SimulationMetricsModel::SetDelayPerUE(std::unique_ptr<map<int, float>> delayPerUE)
{
	m_DelayPerUE = *delayPerUE;
}

void SimulationMetricsModel::SetThroughputPerUE(std::unique_ptr<map<int, float>> throughputPerUE)
{
	m_ThroughputPerUE = *throughputPerUE;
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
	return ToMbps(m_Throughput);
}

float SimulationMetricsModel::GetFairness() const
{
	return m_Fairness;
}

map<int, float>& SimulationMetricsModel::GetDelayPerUe()
{
	return m_DelayPerUE;
}

map<int, float>& SimulationMetricsModel::GetThroughputPerUe()
{
	return m_ThroughputPerUE;
}

std::string SimulationMetricsModel::ToString(OutputStrFormat format)
{
	stringstream ss;

	if(format == STDOUT)
	{
		ss << GetGeneralMetricsSTD() << endl;
		ss << GetUeMetricsSTD();
	}
	else
	{
		ss << GetGeneralMetricsCSV() << endl;
		ss << GetUeMetricsCSV();
	}

	return ss.str();
}

float SimulationMetricsModel::ToMbps(float value)
{
	return value / 1024 / 1024;
}

std::string SimulationMetricsModel::GetGeneralMetricsSTD() const
{
	stringstream ss;

	ss << "Scheduler: " << GetSchedulerTypeStr() << ", ";
	ss << "ResultType: General, ";
	ss << "Users: " << m_UsersNumber << ", ";
	ss << "Delay: " << m_Delay << ", ";
	ss << "Throughput: " << GetThroughputMbps() << ", ";
	ss << "Fairness:" << m_Fairness;

	return ss.str();
}

std::string SimulationMetricsModel::GetUeMetricsSTD()
{
	stringstream ss;

	for(const auto ueMetric : m_DelayPerUE)
	{
		const auto ueId = ueMetric.first;

		ss << "Scheduler: " << GetSchedulerTypeStr() << ", ";
		ss << "ResultType: UE, ";
		ss << "UeId: " << ueId << ", ";
		ss << "Users: " << m_UsersNumber << ", ";
		ss << "Delay: " << m_DelayPerUE[ueId] << ", ";
		ss << "Throughput: " << ToMbps(m_ThroughputPerUE[ueId]) << ", ";
		ss << "Fairness:" << m_Fairness;
		ss << endl;
	}

	return ss.str();
}

std::string SimulationMetricsModel::GetGeneralMetricsCSV() const
{
	stringstream ss;

	ss << GetSchedulerTypeStr() << m_CsvSeparator;
	ss << "General" << m_CsvSeparator;
	ss << m_CsvSeparator; // UeId
	ss << m_UsersNumber << m_CsvSeparator;
	ss << m_Delay << m_CsvSeparator;
	ss << GetThroughputMbps() << m_CsvSeparator;
	ss << m_Fairness;

	return ss.str();
}

std::string SimulationMetricsModel::GetUeMetricsCSV()
{
	stringstream ss;

	for (const auto ueMetric : m_DelayPerUE)
	{
		const auto ueId = ueMetric.first;

		ss << GetSchedulerTypeStr() << m_CsvSeparator;
		ss << "UE" << m_CsvSeparator;
		ss << ueId << m_CsvSeparator;
		ss << m_UsersNumber << m_CsvSeparator;
		ss << m_DelayPerUE[ueId] << m_CsvSeparator;
		ss << ToMbps(m_ThroughputPerUE[ueId]) << m_CsvSeparator;
		ss << m_Fairness;
		ss << endl;
	}

	return ss.str();
}

std::string SimulationMetricsModel::GetCSVHeader()
{
	stringstream ss;

	ss << "Scheduler" << m_CsvSeparator;
	ss << "ResultType" << m_CsvSeparator;
	ss << "UeId" << m_CsvSeparator;
	ss << "Users" << m_CsvSeparator;
	ss << "Delay" << m_CsvSeparator;
	ss << "Throughput" << m_CsvSeparator;
	ss << "Fairness";

	return ss.str();
}
