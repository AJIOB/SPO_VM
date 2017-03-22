#ifndef PERSON_CONTROLLER
#define PERSON_CONTROLLER

#include <iostream>
#include "Person.h"
#include "AllExceptions.h"
#include <list>
#include "Structs.h"

class PersonController
{
#ifdef _WIN32
	HANDLE EVENT[4];
	HANDLE listMutex;
#elif (defined(__linux__) || defined(__unix__))
	pid_t serverPID;
	//int shmPersonNameID;
	//pthread_mutex_t* RWlistMutex;

    pthread_cond_t * pcond;
    pthread_condattr_t attrcond;

    pid_t getServerPID();
    void sendName();
#endif

	Person person;

public:
	PersonController(std::string name);
	~PersonController();
	//std::list<Command> *commands;

	void run();
};

#endif
