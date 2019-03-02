#ifndef CORE_H
#define CORE_H

#include "load-parameters.h"

#ifdef LTE_SIM_PLATFORM_WINDOWS
	#ifdef LTE_SIM_BUILD_DLL 
		#define LTE_SIM_API __declspec(dllexport)
	#else
		#define LTE_SIM_API __declspec(dllimport)
	#endif
#else
	#error Unsupported platform!
#endif

#endif /* CORE_H */