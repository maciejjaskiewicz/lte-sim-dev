#ifndef MYSCHFAIRPACKETSCHEDULER_H_
#define MYSCHFAIRPACKETSCHEDULER_H_

#include "downlink-packet-scheduler.h"
#include <map>

class LTE_SIM_API MY_SCH_FAIR_PacketScheduler : public DownlinkPacketScheduler {
public:
	MY_SCH_FAIR_PacketScheduler();
	virtual ~MY_SCH_FAIR_PacketScheduler();

	void DoSchedule() override;
	void RBsAllocation() override;
	double ComputeSchedulingMetric(RadioBearer *bearer, double spectralEfficiency, int subChannel) override;
private:
	std::map<int, std::vector<int>> m_CQIFeedbackMatrix;
	std::vector<int> m_UserIdsScheduledInPrevTTI;

	void SelectFlowsToScheduleFair();
	void UpdateCQIFeedbackMatrix(int userNetworkNodeId, std::vector<int> cqiFeedback);
	static int GetSizeOfDataToTransmit(RadioBearer& bearer);
	std::vector<double> CalculateSpectralEfficiency(const std::vector<int>& cqiFeedback);
	static bool CanBeScheduleInCurrentTTI(RadioBearer& bearer, int userNetworkNodeId);
	bool WasScheduledInPreviousTTI(int userNetworkNodeId);
	void FinalizeAllocation();
};

#endif