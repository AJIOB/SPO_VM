#include <iostream>
#include <fstream>
#include <string>

#include "CoffeMachine.h"


namespace
{
    const std::string fName = "info.db"
}

CoffeMachine::CoffeMachine(int argc, char* argv[])
{
    init();
    if(argc>2 || argc<=0)
    {
        std::cout<<("��������� ������, �������� ����������");
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
            case 0: std::cout<<("������� �� �������") << std::endl; break;
            case 1: std::cout<<("������������ �������") << std::endl; break;
            case 2: std::cout<<("��������, ������� ������� ��� � �������") << std::endl; break;
        }
    }
    else if (argv[0] == std::string("s"))
    {
        this->showAvailable();
    }
    else if (argv[0] == std::string("m"))
    {
        this->buy(atoi(argv[1]));
    }
    else
    {
        std::cout<<("������") << std::endl;
    }
}

CoffeMachine::~CoffeMachine()
{
    ofstream f(fName);
    
    if (!f)
    {
        std::cout<<("������ �������� �����") << std::endl;
        return;
    }
    
    f << money << std::endl;
    
    for (Drink d: drinks)
    {
        std::string name = ;
        f << d.getName() << " " << d.getPrice() << " " << d.getAmount() << std::endl;   
    }
}

void CoffeMachine::addMoney(int money)
{
    this->money +=money;
}

int CoffeMachine::buy(int drinkID)
{
    
}

void CoffeMachine::showAvailable(int drinkID)
{
    
}

void CoffeMachine::moneyBack(int money)
{
    
}
void init()
{
    ifstream f(fName);
    
    if (!f)
    {
        std::cout<<("������ �������� �����") << std::endl;
        return;
    }
    
    f >> money;
    
    if (!f)
    {
        std::cout<<("������ ������ �� �����") << std::endl;
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
            std::cout<<("������ ������ �� �����") << std::endl;
            return;
        }
            
        int count;
        f >>count;
        if (!f)
        {
            std::cout<<("������ ������ �� �����") << std::endl;
            return;
        }
        
        drinks.push_back(Drink(name, count, cost));
        
    } while (true);
}
