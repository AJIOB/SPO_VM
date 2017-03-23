#ifndef PERSON_CONTROLLER
#define PERSON_CONTROLLER

#include <iostream>
#include <list>

#include "Person.h"
#include "Structs.h"
#include "exceptions/AllExceptions.h"

class PersonController
{
#ifdef _WIN32
	HANDLE EVENT[4];
	HANDLE listMutex;

	std::list<Command>* commands;
#elif (defined(__linux__) || defined(__unix__))
	pid_t serverPID;
	//int shmPersonNameID;
	//pthread_mutex_t* RWlistMutex;

    pthread_cond_t * pcond;
    pthread_condattr_t attrcond;

    pid_t getServerPID();
    void sendName();
    void removeName();
#endif

	Person person;

public:
	PersonController(std::string name);
	~PersonController();

	void run();
};

#endif
