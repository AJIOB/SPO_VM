#ifndef PERSON_CLASS
#define PERSON_CLASS

#include <iostream>
#include <sstream>

#include "view/StreamInput.h"
#include "Controller.h"

class Person
{
	std::stringstream query;
public:
	Person();
	~Person();
	bool runConsole();
	void sendRequest() const;
	void getResponce() const;

private:
	unsigned long long inputDrinkIndex() const;

	unsigned long long inputMoney() const;
};

#endif


