#ifndef ApplicationFactory_H_
#define ApplicationFactory_H_

#include "core/Core.h"
#include "application/Application.h"
#include "device/NetworkNode.h"

class LTE_SIM_API ApplicationFactory
{
public:
	static std::unique_ptr<Application> CreateApplication(
		Application::ApplicationType type,
		int applicationId,
		NetworkNode* src,
		NetworkNode* dst,
		int srcPort,
		int destPort,
		TransportProtocol::TransportProtocolType protocol,
		QoSParameters* qos,
		double startTime,
		double duration);	
	
};

#endif /* ApplicationFactory_H_ */
