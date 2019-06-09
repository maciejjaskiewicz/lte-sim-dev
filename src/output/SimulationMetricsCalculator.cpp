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
		bearerMetric.UeTxId = outputModel.GetSourceId();
	}

	if (outputModel.GetTransmissionType() == RX)
	{
		m_ReceivedPackets++;
		m_ReceivedPacketsSize += outputModel.GetSize();
		m_DelaySum += outputModel.GetDelay();

		bearerMetric.ReceivedPackets++;
		bearerMetric.ReceivedPacketsSize += outputModel.GetSize();
		bearerMetric.DelaySum += outputModel.GetDelay();
		bearerMetric.UeRxId = outputModel.GetDestinationId();
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

std::unique_ptr<std::map<int, float>> SimulationMetricsCalculator::CalculateDelayPerUE()
{
	struct UeMetricEntry
	{
		int ReceivedPackets;
		float DelaySum;
	};

	std::map<int, UeMetricEntry> ueMetrics;

	for (const auto bearerMetric : m_BearerMetrics)
	{
		const auto ueId = bearerMetric.second.UeRxId;

		if(ueMetrics.find(ueId) != ueMetrics.end())
		{
			ueMetrics[ueId].ReceivedPackets += bearerMetric.second.ReceivedPackets;
			ueMetrics[ueId].DelaySum += bearerMetric.second.DelaySum;
		}
		else
		{
			UeMetricEntry metricEntry{};
			metricEntry.ReceivedPackets += bearerMetric.second.ReceivedPackets;
			metricEntry.DelaySum = bearerMetric.second.DelaySum;

			ueMetrics.insert(std::make_pair(ueId, metricEntry));
		}
	}

	auto result = std::make_unique<std::map<int, float>>();

	for(const auto ueMetric : ueMetrics)
	{
		auto delay = ueMetric.second.DelaySum / ueMetric.second.ReceivedPackets;
		result->insert(std::make_pair(ueMetric.first, delay));
	}

	return result;
}

std::unique_ptr<std::map<int, float>> SimulationMetricsCalculator::CalculateThroughputPerUE()
{
	std::map<int, int> ueReceivedPacketSizes;

	for (const auto bearerMetric : m_BearerMetrics)
	{
		const auto ueId = bearerMetric.second.UeRxId;

		if (ueReceivedPacketSizes.find(ueId) != ueReceivedPacketSizes.end())
		{
			ueReceivedPacketSizes[ueId] += bearerMetric.second.ReceivedPacketsSize;
		}
		else
		{
			ueReceivedPacketSizes.insert(std::make_pair(ueId, bearerMetric.second.ReceivedPacketsSize));
		}
	}

	auto result = std::make_unique<std::map<int, float>>();

	for (const auto ueMetric : ueReceivedPacketSizes)
	{
		auto throughput = (ueMetric.second * 8) / m_Time;
		result->insert(std::make_pair(ueMetric.first, throughput));
	}

	return result;
}

float SimulationMetricsCalculator::CalculateThroughput(MetricEntry metricEntry) const
{
	return (metricEntry.ReceivedPacketsSize * 8) / m_Time;
}
