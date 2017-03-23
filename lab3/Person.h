#ifndef PERSON_CLASS
#define PERSON_CLASS

#include <iostream>
#include <sstream>
#include <fstream>

#include "view/StreamInput.h"
#include "exceptions/AllExceptions.h"
#include "Constants.h"

class Person
{
	std::stringstream query;
public:
	Person();
	~Person();
	void runConsole();
	void sendRequest() const;
	void getResponse() const;

private:
	unsigned long long inputDrinkIndex() const;

	unsigned long long inputMoney() const;
};

#endif
