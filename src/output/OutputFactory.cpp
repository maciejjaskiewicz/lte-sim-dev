#include "OutputFactory.h"

std::unique_ptr<OutputModel> OutputFactory::CreateTXOutputModel(int id, Application::ApplicationType applicationType, 
	NetworkNode::NodeType nodeType, int bearerId, int size, int srcId, int destId, double createdTime, bool isIndoor)
{
	auto output = std::make_unique<OutputModel>(id);

	output->m_TransmissionType = TX;
	output->m_ApplicationType = applicationType;
	output->m_NodeType = nodeType;
	output->m_BearerId = bearerId;
	output->m_Size = size;
	output->m_SourceId = srcId;
	output->m_DestinationId = destId;
	output->m_CreatedTime = createdTime;
	output->m_IsIndoor = isIndoor;

	return output;
}

std::unique_ptr<OutputModel> OutputFactory::CreateRXOutputModel(int id, Application::ApplicationType applicationType,
	int bearerId, int size, int srcId, int destId, double delay, bool isIndoor)
{
	auto output = std::make_unique<OutputModel>(id);

	output->m_TransmissionType = RX;
	output->m_ApplicationType = applicationType;
	output->m_BearerId = bearerId;
	output->m_Size = size;
	output->m_SourceId = srcId;
	output->m_DestinationId = destId;
	output->m_Delay = delay;
	output->m_IsIndoor = isIndoor;

	return output;
}
