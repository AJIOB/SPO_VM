#include <iostream>
#include <fstream>
#include <string>

#include "CoffeMachine.h"


namespace
{
    const std::string fName = "info.db";
	extern static const std::string transferFile;
}

void CoffeMachine::showMoney() const
{
	std::cout<<"� ��� "<< money<<" ������, ��������"<<std::endl;
}

CoffeMachine::CoffeMachine()
{
	std::ifstream f(fName);
    
    if (!f)
    {
        std::cout<<("������ �������� �����") << std::endl;
        return;
    }
    
    f >> this->money;
    
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

CoffeMachine::~CoffeMachine()
{
	
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
        std::cout<< it->getName() <<  ". ������ " << it - drinks.begin() << ". ���� " << it->getPrice() << ". ���-�� ��������� " << it->getAmount() << std::endl;   
    }
}

void CoffeMachine::moneyBack()
{
    std::cout<<"�������� ����: "<< money<<" ������ �������, ��������"<<std::endl;
	money=0;
}

std::string CoffeMachine::getCommand()
{

	//todo AJIOB
	std::ifstream f(transferFile);
    
    if (!f)
    {
        std::cout<<("������ �������� �����") << std::endl;
        return;
    }
    
	//f.tellg();
    //f.getline(line,sizeof(f)+1);
    
    if (!f)
    {
        std::cout<<("������ ������ �� �����") << std::endl;
        return;
    }
}

void CoffeMachine::setCommand()
{
	//todo AJIOB
}

void proceed()
{

	//TODo AJIOB
	//getCommand();
	
	//proceed operation
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
			case 3: std::cout<<("�������������� ID �������") << std::endl; break;
        default: std::cout<<("����������� ������") << std::endl; break;;
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
        std::cout<<("������") << std::endl;
    }
	
	
	//setCommand(//set to file);
	
	//return;
}