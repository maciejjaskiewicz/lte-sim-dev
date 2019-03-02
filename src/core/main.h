#ifndef MAIN_H
#define MAIN_H

#include "core/simulation/Simulation.h"

extern Simulation* CreateSimulation();

int main(int argc, char** argv)
{
	auto simulation = CreateSimulation();

	delete simulation;
	return 0;
}

#endif /* MAIN_H */