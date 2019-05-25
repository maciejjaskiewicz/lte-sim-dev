#ifndef OUTPUTFACTORY_H
#define OUTPUTFACTORY_H

#include "Models/OutputModel.h"

class LTE_SIM_API OutputFactory
{
public:
	static std::unique_ptr<OutputModel> CreateTXOutputModel(int id, Application::ApplicationType applicationType,
		NetworkNode::NodeType nodeType, int bearerId, int size, int srcId, int destId, double createdTime, bool isIndoor);
	static std::unique_ptr<OutputModel> CreateRXOutputModel(int id, Application::ApplicationType applicationType,
		int bearerId, int size, int srcId, int destId, double delay, bool isIndoor);
};

#endif
