#ifndef PERSON_CLASS
#define PERSON_CLASS

#include <iostream>
#include <string>
#include "view/StreamInput.h"

class Person
{
	std::string query;
public:
	Person();
	~Person();
	bool runConsole();
	void sendRequest();
	void getResponce();

private:
	unsigned long long inputDrinkIndex() const;

	unsigned long long inputMoney() const;
};

#endif


