#ifndef SIMULATIONMETRICSMODEL_H
#define SIMULATIONMETRICSMODEL_H

#include "core/Core.h"
#include "device/ENodeB.h"
#include "OutputModel.h"

class LTE_SIM_API SimulationMetricsModel
{
public:
	SimulationMetricsModel(int usersNumber, ENodeB::DLSchedulerType scheduler);
	SimulationMetricsModel(int usersNumber, ENodeB::DLSchedulerType scheduler, float delay, float throughput, float fairness);

	void SetDelay(float delay);
	void SetThroughput(float throughput);
	void SetFairness(float fairness);

	int GetUsersNumber() const;
	ENodeB::DLSchedulerType GetSchedulerType() const;
	std::string GetSchedulerTypeStr() const;
	float GetDelay() const;
	float GetThroughput() const;
	float GetThroughputMbps() const;
	float GetFairness() const;

	std::string ToString(OutputStrFormat format = STDOUT) const;
	static std::string GetCSVHeader();

private:
	int m_UsersNumber;
	ENodeB::DLSchedulerType m_Scheduler;
	float m_Delay{};
	float m_Throughput{};
	float m_Fairness{};

	static const char m_CsvSeparator = ',';
};

#endif