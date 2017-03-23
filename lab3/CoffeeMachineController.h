#ifndef COFFEE_MACHINE_CONTROLLER
#define COFFEE_MACHINE_CONTROLLER

#include <iostream>
#include <list>
#include <algorithm>

#include "CoffeeMachine.h"
#include "exceptions/AllExceptions.h"
#include "Structs.h"

class CoffeeMachineController
{
#ifdef _WIN32

	HANDLE EVENT[4];
	HANDLE listMutex;
	HANDLE hFile;
	LPVOID fileBuf;
	HANDLE outputThread;
	static DWORD WINAPI threadOutputting(LPVOID lpParam);
	std::list<Command> commands;

#elif (defined(__linux__) || defined(__unix__))

	pid_t currPID;
	int shmPersonNameID;
    pthread_mutexattr_t attrmutex;
	pthread_mutex_t* RWlistMutex;

    pthread_t outputThread;

	void writePID();

    void createRWMutex();

    friend void* OutputThread(void*);
#endif

	CoffeeMachine machine;
	std::list<std::string> names;

public:
	CoffeeMachineController();
	~CoffeeMachineController();
	void run();
};

#endif
