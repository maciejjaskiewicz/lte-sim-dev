#ifndef ApplicationFactory_H_
#define ApplicationFactory_H_

#include "core/Core.h"
#include "application/Application.h"
#include "device/NetworkNode.h"

class LTE_SIM_API ApplicationFactory
{
public:
	template<class T>
	static std::unique_ptr<T> CreateApplication(
		int applicationId,
		NetworkNode* src,
		NetworkNode* dst,
		int srcPort,
		int destPort,
		TransportProtocol::TransportProtocolType protocol,
		double startTime,
		double duration)
	{
		auto app = std::make_unique<T>();

		LTE_SIM_ASSERT(app);

		app->SetApplicationID(applicationId);

		app->SetSource(src);
		app->SetDestination(dst);
		app->SetSourcePort(srcPort);
		app->SetDestinationPort(destPort);

		const auto cp = new ClassifierParameters(
			src->GetIDNetworkNode(),
			dst->GetIDNetworkNode(),
			srcPort,
			destPort,
			protocol);

		app->SetClassifierParameters(cp);

		app->SetStartTime(startTime);
		app->SetStopTime(startTime + duration);

		return app;
	}
	
};

#endif /* ApplicationFactory_H_ */
