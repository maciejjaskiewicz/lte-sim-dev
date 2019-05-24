#ifndef OUTPUTMODEL_H
#define OUTPUTMODEL_H

#include "core/Core.h"
#include "flows/application/Application.h"

enum TransmissionType
{
	RX,
	TX
};

enum OutputStrFormat
{
	STDOUT,
	CSV
};

class LTE_SIM_API OutputModel
{
public:
	OutputModel(int id);

	int GetId() const;
	TransmissionType GetTransmissionType() const;
	Application::ApplicationType GetApplicationType() const;
	NetworkNode::NodeType GetNodeType() const;
	int GetBearerId() const;
	int GetSize() const;
	int GetSourceId() const;
	int GetDestinationId() const;
	double GetCreatedTime() const;
	double GetDelay() const;
	bool IsIndoor() const;

	static const char m_CsvSeparator = ',';
	static std::string GetCSVHeader();

	std::string ToString(OutputStrFormat format = STDOUT) const;

private:
	int m_Id;
	TransmissionType m_TransmissionType;
	Application::ApplicationType m_ApplicationType;
	NetworkNode::NodeType m_NodeType;
	int m_BearerId;
	int m_Size;
	int m_SourceId;
	int m_DestinationId;
	double m_CreatedTime;
	double m_Delay;
	bool m_IsIndoor;

	static std::string ApplicationTypeToString(Application::ApplicationType applicationType);
	static std::string TransmissionTypeToString(TransmissionType transmissionType);

	std::string BuildStdOutString() const;
	std::string BuildCsvString() const;

	friend class OutputFactory;
};

#endif
