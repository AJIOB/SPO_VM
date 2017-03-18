#ifndef PERSON_CONTROLLER
#define PERSON_CONTROLLER

#include <iostream>
#include "Person.h"

class PersonController
{

#ifdef _WIN32
	HANDLE EVENT[4];
#elif 0
	pid_t getServerPID();
#endif

	Person person;

public:
	PersonController();
	~PersonController();

	void run();
};

#endif