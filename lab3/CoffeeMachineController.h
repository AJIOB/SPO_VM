#ifndef COFFEE_MACHINE_CONTROLLER
#define COFFEE_MACHINE_CONTROLLER

#include <iostream>
#include "CoffeeMachine.h"
#include "AllExceptions.h"
#include <list>
#include "Structs.h"

class CoffeeMachineController
{
#ifdef _WIN32

	HANDLE EVENT[4];
	HANDLE listMutex;
	HANDLE hFile;
	LPVOID fileBuf;
	HANDLE outputThread;
	static DWORD WINAPI threadOutputting( LPVOID lpParam);

#elif (defined(__linux__) || defined(__unix__))

	pid_t currPID;
	int shmPersonNameID;
	pthread_mutex_t* RWlistMutex;

	void writePID();

#endif

	CoffeeMachine machine;
	std::list<Command> commands;
	std::list<std::string> names;
	
public:
	CoffeeMachineController();
	~CoffeeMachineController();
	void run();
};

#endif
