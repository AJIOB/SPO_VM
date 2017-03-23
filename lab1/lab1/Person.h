#ifndef PERSON_CLASS
#define PERSON_CLASS

#include <iostream>
#include <string>
#include "view/StreamInput.h"

class Person
{
public:
	Person();
	~Person();

private:
	unsigned long long inputDrinkIndex() const;
	void RunChild(const std::string& params) const;
	void runMenu() const;

	unsigned long long inputMoney() const;
};

#endif


