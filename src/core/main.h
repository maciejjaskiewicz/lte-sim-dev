#ifndef MAIN_H
#define MAIN_H

#ifndef LTE_SIM_CUSTOM_MAIN

#include "core/simulation/Simulation.h"

extern Simulation* CreateSimulation();

int main(int argc, char** argv)
{
	auto simulation = CreateSimulation();

	delete simulation;
	return 0;
}

#endif

#endif /* MAIN_H */