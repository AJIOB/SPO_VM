#ifndef PERSON_CLASS
#define PERSON_CLASS

#include <iostream>
#include "view/StreamInput.h"

class Person
{
public:
	Person();
	~Person();

private:
	unsigned long long inputDrinkIndex() const;
	void runMenu() const;

	unsigned long long inputMoney() const;
};

#endif


