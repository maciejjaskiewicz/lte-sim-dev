#include "PacketAttributes.h"

PacketAttributes::PacketAttributes(int applicationId, int bearerId, int size, int srcId, int destId,
	double createdTime) : m_ApplicationId(applicationId), m_BearerId(bearerId), 
	m_Size(size), m_SourceId(srcId), m_DestinationId(destId), m_CreatedTime(createdTime),
	m_Delay(-1)
{ }

void PacketAttributes::SetDelay(double delay)
{
	m_Delay = delay;
}

int PacketAttributes::GetApplicationId() const
{
	return m_ApplicationId;
}

int PacketAttributes::GetBearerId() const
{
	return m_BearerId;
}

int PacketAttributes::GetSize() const
{
	return m_Size;
}

int PacketAttributes::GetSourceId() const
{
	return m_SourceId;
}

int PacketAttributes::GetDestinationId() const
{
	return m_DestinationId;
}

double PacketAttributes::GetCreatedTime() const
{
	return m_CreatedTime;
}

double PacketAttributes::GetDelay() const
{
	return m_Delay;
}

