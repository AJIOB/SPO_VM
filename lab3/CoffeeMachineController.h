#ifndef COFFEE_MACHINE_CONTROLLER
#define COFFEE_MACHINE_CONTROLLER

#include <iostream>
#include "CoffeeMachine.h"

class CoffeeMachineController
{
#ifdef _WIN32

	HANDLE EVENT[4];

#elif (defined(__linux__) || defined(__unix__))
	pid_t currPID;

	writePID();
#endif

	CoffeeMachine machine;

public:
	CoffeeMachineController();
	~CoffeeMachineController();

	void run();
};

#endif