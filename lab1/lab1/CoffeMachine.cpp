#include <iostream>
#include <fstream>
#include <string>

#include "CoffeMachine.h"


namespace
{
    const std::string fName = "info.db";
}

void CoffeMachine::showMoney() const
{
	std::cout<<"У вас "<< money<<" рублей, нищеброд"<<std::endl;
}

CoffeMachine::CoffeMachine(int argc, char* argv[])
{
    init();
	
    if(argc>2 || argc<=0)
    {
        std::cout<<("Произошла ошибка, неверная информация");
        return;
    }
    if (argv[0] == std::string("a"))
    {
        this->addMoney(atoi(argv[1]));
    }
    else if (argv[0] == std::string("b"))
    {
        int result = this->buy(atoi(argv[1]));
        switch (result)
        {
            case 0: std::cout<<("Спасибо за покупку") << std::endl; break;
            case 1: std::cout<<("Недостаточно средств") << std::endl; break;
            case 2: std::cout<<("Извините, данного напитка нет в наличии") << std::endl; break;
			case 3: std::cout<<("Несуществующий ID напитка") << std::endl; break;
        default: std::cout<<("Неизвестная ошибка") << std::endl; break;;
        }
    }
    else if (argv[0] == std::string("s"))
    {
        this->showAvailable();
    }
    else if (argv[0] == std::string("m"))
    {
        this->moneyBack();
    }
	else if (argv[0] == std::string("sm"))
    {
        this->showMoney();
    }

    else
    {
        std::cout<<("Ошибка") << std::endl;
    }
}

CoffeMachine::~CoffeMachine()
{
	std::ofstream f(fName);
    
    if (!f)
    {
        std::cout<<("Ошибка открытия файла") << std::endl;
        return;
    }
    
    f << money << std::endl;

    for (auto it = drinks.begin(); it != drinks.end(); ++it)
    {
        
        f << it->getName() << " " << it->getPrice() << " " << it->getAmount() << std::endl;   
    }
}

void CoffeMachine::addMoney(int money)
{
    this->money +=money;
}

int CoffeMachine::buy(int drinkID)
{
	if (drinkID < 0 || drinkID >= drinks.size()) return 3;		//bad index
	if(drinks[drinkID].getPrice()>money) return 1;			//checking if enough money
	if(drinks[drinkID].getAmount()<1) return 2;					// if drink is available
	drinks[drinkID].deleteDrink();
	money -= drinks[drinkID].getPrice();
	return 0;
}

void CoffeMachine::showAvailable()
{
    for (auto it = drinks.begin(); it != drinks.end(); ++it)
	{
        std::cout<< it->getName() <<  ". Индекс " << it - drinks.begin() << ". Цена " << it->getPrice() << ". Кол-во доступных " << it->getAmount() << std::endl;   
    }
}

void CoffeMachine::moneyBack()
{
    std::cout<<"Возьмите ваши: "<< money<<" рублей обратно, нищеброд"<<std::endl;
	money=0;
}

void CoffeMachine::init()
{
	std::ifstream f(fName);
    
    if (!f)
    {
        std::cout<<("Ошибка открытия файла") << std::endl;
        return;
    }
    
    f >> this->money;
    
    if (!f)
    {
        std::cout<<("Ошибка чтения из файла") << std::endl;
        return;
    }
    
    do
    {
        std::string name;
        f >> name;
        if (!f)
        {
            break;
        }
        
        int cost;
        f >> cost;
        if (!f)
        {
            std::cout<<("Ошибка чтения из файла") << std::endl;
            return;
        }
            
        int count;
        f >>count;
        if (!f)
        {
            std::cout<<("Ошибка чтения из файла") << std::endl;
            return;
        }
        
        drinks.push_back(Drink(name, count, cost));
        
    } while (true);
}