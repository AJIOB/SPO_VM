#include "Drink.h"
#include <iostream>

Drink::Drink(std::string name_, int amountLeft_, int price_)
{
	name = name_;
	amountLeft = amountLeft_;
	price = price_;
}

void Drink::addDrink(int count)
{
	amountLeft += count;
}

void Drink::deleteDrink()
{
	amountLeft--;
}

void Drink::show()
{
	std::cout << name << "  Цена:  " << price << "  Остаток:  " << amountLeft << std::endl;
}

std::string Drink::getName()
{
	return name;
}

int Drink::getPrice()
{
	return price;
}

int Drink::getAmount()
{
	return amountLeft;
}
