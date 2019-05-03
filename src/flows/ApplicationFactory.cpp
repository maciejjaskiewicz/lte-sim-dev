#include "ApplicationFactory.h"

#include "application/TraceBased.h"
#include "application/VoIP.h"
#include "application/InfiniteBuffer.h"
#include "application/CBR.h"

std::unique_ptr<Application> ApplicationFactory::CreateApplication(
	Application::ApplicationType type,
	int applicationId,
	NetworkNode* src,
	NetworkNode* dst,
	int srcPort,
	int destPort,
	TransportProtocol::TransportProtocolType protocol,
	QoSParameters* qos,
	double startTime,
	double duration)
{
	std::unique_ptr<Application> app;

	switch (type)
	{
	case Application::APPLICATION_TYPE_CBR:
		app = std::make_unique<CBR>();
		break;
	case Application::APPLICATION_TYPE_INFINITE_BUFFER:
		app = std::make_unique<InfiniteBuffer>();
		break;
	case Application::APPLICATION_TYPE_VOIP:
		app = std::make_unique<VoIP>();
		break;
	case Application::APPLICATION_TYPE_TRACE_BASED:
		app = std::make_unique<TraceBased>();
		break;
	}

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


	app->SetQoSParameters(qos);

	app->SetStartTime(startTime);
	app->SetStopTime(startTime + duration);

	return app;
}