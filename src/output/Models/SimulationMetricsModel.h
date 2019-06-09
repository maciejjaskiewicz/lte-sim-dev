#ifndef SIMULATIONMETRICSMODEL_H
#define SIMULATIONMETRICSMODEL_H

#include "core/Core.h"
#include "device/ENodeB.h"
#include "OutputModel.h"
#include <map>

class LTE_SIM_API SimulationMetricsModel
{
public:
	SimulationMetricsModel(int usersNumber, ENodeB::DLSchedulerType scheduler);
	SimulationMetricsModel(int usersNumber, ENodeB::DLSchedulerType scheduler, float delay, float throughput, float fairness);

	void SetDelay(float delay);
	void SetThroughput(float throughput);
	void SetFairness(float fairness);
	void SetDelayPerUE(std::unique_ptr<map<int, float>> delayPerUE);
	void SetThroughputPerUE(std::unique_ptr<map<int, float>> throughputPerUE);

	int GetUsersNumber() const;
	ENodeB::DLSchedulerType GetSchedulerType() const;
	std::string GetSchedulerTypeStr() const;
	float GetDelay() const;
	float GetThroughput() const;
	float GetThroughputMbps() const;
	float GetFairness() const;
	map<int, float>& GetDelayPerUe();
	map<int, float>& GetThroughputPerUe();

	std::string ToString(OutputStrFormat format = STDOUT);
	static std::string GetCSVHeader();

private:
	int m_UsersNumber;
	ENodeB::DLSchedulerType m_Scheduler;
	float m_Delay{};
	float m_Throughput{};
	float m_Fairness{};
	std::map<int, float> m_DelayPerUE;
	std::map<int, float> m_ThroughputPerUE;

	static const char m_CsvSeparator = ',';

	static float ToMbps(float value);
	std::string GetGeneralMetricsSTD() const;
	std::string GetUeMetricsSTD();
	std::string GetGeneralMetricsCSV() const;
	std::string GetUeMetricsCSV();
};

#endif