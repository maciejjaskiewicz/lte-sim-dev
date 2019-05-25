#include "SimulationMetricsCalculator.h"

SimulationMetricsCalculator::SimulationMetricsCalculator(int usersNumber, float time)
	: m_UsersNumber(usersNumber), m_Time(time)
{ }

void SimulationMetricsCalculator::Add(const OutputModel& outputModel)
{
	bool newBearer = true;
	const auto bearerId = outputModel.GetBearerId();
	MetricEntry bearerMetric{};

	if (m_BearerMetrics.find(bearerId) != m_BearerMetrics.end())
	{
		bearerMetric = m_BearerMetrics[bearerId];
		newBearer = false;
	}

	if (outputModel.GetTransmissionType() == TX)
	{
		m_TransmittedPackets++;
		bearerMetric.TransmittedPackets++;
	}

	if (outputModel.GetTransmissionType() == RX)
	{
		m_ReceivedPackets++;
		m_ReceivedPacketsSize += outputModel.GetSize();
		m_DelaySum += outputModel.GetDelay();

		bearerMetric.ReceivedPackets++;
		bearerMetric.ReceivedPacketsSize += outputModel.GetSize();
		bearerMetric.m_DelaySum += outputModel.GetDelay();
	}

	if(newBearer)
	{
		m_BearerMetrics.insert(std::make_pair(bearerId, bearerMetric));
	}
	else
	{
		m_BearerMetrics[bearerId] = bearerMetric;
	}
}

float SimulationMetricsCalculator::CalculateDelay() const
{
	return m_DelaySum / m_ReceivedPackets;
}

float SimulationMetricsCalculator::CalculateThroughput() const
{
	return (m_ReceivedPacketsSize * 8) / m_Time;
}

float SimulationMetricsCalculator::CalculateFairness() const
{
	float throughputSum = 0;
	double throughputQuadSum = 0;

	for(const auto bearerMetric : m_BearerMetrics)
	{
		const float throughput = CalculateThroughput(bearerMetric.second);

		throughputSum += throughput;
		throughputQuadSum += pow(throughput, 2);
	}

	const double throughputTotalSumQuad = pow(throughputSum, 2);

	return throughputTotalSumQuad / (m_BearerMetrics.size() * throughputQuadSum);
}

float SimulationMetricsCalculator::CalculateThroughput(MetricEntry metricEntry) const
{
	return (metricEntry.ReceivedPacketsSize * 8) / m_Time;
}
