#ifndef PACKETHELPER_H
#define PACKETHELPER_H

#include "protocolStack/packet/Packet.h"
#include "core/simulation/Simulation.h"

inline double CalculateDelay(Packet& packet)
{
	double delay = (Simulation::Get().Now() * 10000 - packet.GetTimeStamp() * 10000) / 10000;
	if (delay < 0.000001) delay = 0.000001;

	return delay;
}

#endif