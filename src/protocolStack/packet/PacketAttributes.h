#ifndef PACKETATTRIBUTES_H_
#define PACKETATTRIBUTES_H_

#include "core/Core.h"
#include "flows/application/Application.h"

/*
 * Generalized packet information for output purpose
 */
class LTE_SIM_API PacketAttributes
{
public:
	PacketAttributes(int applicationId, int bearerId, int size, 
		int srcId, int destId, double createdTime);

	void SetDelay(double delay);

	int GetApplicationId() const;
	int GetBearerId() const;
	int GetSize() const;
	int GetSourceId() const;
	int GetDestinationId() const;
	double GetCreatedTime() const;
	double GetDelay() const;
private:
	int m_ApplicationId;
	int m_BearerId;
	int m_Size;
	int m_SourceId;
	int m_DestinationId;
	double m_CreatedTime;
	double m_Delay;
};

#endif /* PACKETATTRIBUTES_H_ */