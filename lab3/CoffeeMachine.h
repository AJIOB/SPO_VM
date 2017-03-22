#ifndef COFFE_CLASS
#define COFFE_CLASS

#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include "Drink.h"
#include "Constants.h"

class CoffeeMachine
{
	std::stringstream out;

	int money;
	std::vector<Drink> drinks;
	void setCommand() const;
	std::vector<std::string> getCommand() const;
	void addMoney(int money);
	int buy(int drinkID);
	void showAvailable();
	void moneyBack();
public:
	void showMoney();
	CoffeeMachine();
	~CoffeeMachine();
	void proceed();
	void saveCondition();
};

#endif
