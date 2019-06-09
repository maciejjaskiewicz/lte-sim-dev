#ifndef SIMULATIONMETRICSCALCULATOR_H
#define SIMULATIONMETRICSCALCULATOR_H

#include "core/Core.h"
#include "Models/OutputModel.h"

#include <map>
#include <set>

class LTE_SIM_API SimulationMetricsCalculator
{
public:
	SimulationMetricsCalculator(int usersNumber, float time);
	void Add(const OutputModel& outputModel);

	float CalculateDelay() const;
	float CalculateThroughput() const;
	float CalculateFairness() const;

	std::unique_ptr<std::map<int, float>> CalculateDelayPerUE();
	std::unique_ptr<std::map<int, float>> CalculateThroughputPerUE();

private:
	int m_UsersNumber;
	float m_Time;

	double m_DelaySum{};
	int m_ReceivedPackets{};
	int m_TransmittedPackets{};
	int m_ReceivedPacketsSize{};

	struct MetricEntry
	{
		int UeTxId;
		int UeRxId;
		int TransmittedPackets;
		int ReceivedPackets;
		int ReceivedPacketsSize;
		double DelaySum;
	};

	std::map<int, MetricEntry> m_BearerMetrics;

	float CalculateThroughput(MetricEntry metricEntry) const;
};

#endif
