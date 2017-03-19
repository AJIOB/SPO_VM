#ifndef PERSON_CLASS
#define PERSON_CLASS

#include <iostream>
#include <sstream>
#include <fstream>

#include "view/StreamInput.h"
#include "Constants.h"

class Person
{
	std::stringstream query;
public:
	Person(std::string name);
	~Person();
	bool runConsole();
	void sendRequest() const;
	void getResponce() const;
	std::string getName() const;

private:
	std::string name; 

	unsigned long long inputDrinkIndex() const;

	unsigned long long inputMoney() const;
};

#endif
