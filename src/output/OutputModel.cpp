#include "OutputModel.h"

#include <sstream>

OutputModel::OutputModel(int id) : m_Id(id)
{ }

int OutputModel::GetId() const
{
	return m_Id;
}

TransmissionType OutputModel::GetTransmissionType() const
{
	return m_TransmissionType;
}

Application::ApplicationType OutputModel::GetApplicationType() const
{
	return m_ApplicationType;
}

NetworkNode::NodeType OutputModel::GetNodeType() const
{
	return m_NodeType;
}

int OutputModel::GetBearerId() const
{
	return m_BearerId;
}

int OutputModel::GetSize() const
{
	return m_Size;
}

int OutputModel::GetSourceId() const
{
	return m_SourceId;
}

int OutputModel::GetDestinationId() const
{
	return m_DestinationId;
}

double OutputModel::GetCreatedTime() const
{
	return m_CreatedTime;
}

double OutputModel::GetDelay() const
{
	return m_Delay;
}

bool OutputModel::IsIndoor() const
{
	return m_IsIndoor;
}

std::string OutputModel::GetCSVHeader()
{
	stringstream ss;

	ss << "TxType" << m_CsvSeparator;
	ss << "AppType" << m_CsvSeparator;
	ss << "Id" << m_CsvSeparator;
	ss << "Size" << m_CsvSeparator;
	ss << "SRC" << m_CsvSeparator;
	ss << "DST" << m_CsvSeparator;
	ss << "CreatedTime" << m_CsvSeparator;
	ss << "Delay" << m_CsvSeparator;
	ss << "IsIndoor";

	return ss.str();
}

std::string OutputModel::ToString(OutputStrFormat format) const
{
	switch (format)
	{
	case STDOUT: return BuildStdOutString();
	case CSV: return BuildCsvString();
	}

	return BuildStdOutString();
}

std::string OutputModel::ApplicationTypeToString(Application::ApplicationType applicationType)
{
	switch (applicationType)
	{
	case Application::APPLICATION_TYPE_VOIP: return "VOIP";
	case Application::APPLICATION_TYPE_TRACE_BASED: return "VIDEO";
	case Application::APPLICATION_TYPE_CBR: return "CBR";
	case Application::APPLICATION_TYPE_INFINITE_BUFFER: return "INF_BUF";
	default: return "UNDEFINED";
	}
}

std::string OutputModel::TransmissionTypeToString(TransmissionType transmissionType)
{
	switch (transmissionType)
	{
	case RX: return "RX";
	case TX: return "TX";
	default: return "UNDEFINED";
	}
}

std::string OutputModel::BuildStdOutString() const
{
	stringstream ss;

	ss << TransmissionTypeToString(m_TransmissionType) << " ";
	ss << ApplicationTypeToString(m_ApplicationType);
	ss << " ID " << m_Id;
	ss << " SIZE " << m_Size;
	ss << " SRC " << m_SourceId;
	ss << " DST " << m_DestinationId;

	if (m_TransmissionType == RX)
	{
		ss << " D " << m_Delay;
		ss << m_IsIndoor;
	}
	else
	{
		ss << " T " << m_CreatedTime;

		if (m_NodeType == NetworkNode::TYPE_UE)
		{
			ss << m_IsIndoor;
		}
	}

	return ss.str();
}

std::string OutputModel::BuildCsvString() const
{
	stringstream ss;

	ss << TransmissionTypeToString(m_TransmissionType) << m_CsvSeparator;
	ss << ApplicationTypeToString(m_ApplicationType) << m_CsvSeparator;
	ss << m_Id << m_CsvSeparator;
	ss << m_Size << m_CsvSeparator;
	ss << m_SourceId << m_CsvSeparator;
	ss << m_DestinationId << m_CsvSeparator;

	if(m_TransmissionType == TX) ss << m_CreatedTime << m_CsvSeparator;
	else ss << m_CsvSeparator;

	if (m_TransmissionType == RX) ss << m_Delay << m_CsvSeparator;
	else ss << m_CsvSeparator;

	ss << m_IsIndoor;

	return ss.str();
}
