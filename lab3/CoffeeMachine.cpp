#include "CoffeeMachine.h"

namespace
{
	const std::string fName = "info.db";

	using namespace VA::constants;
}

void CoffeeMachine::showMoney()
{
	out << "У вас " << money << " рублей, нищеброд" << std::endl;
}

CoffeeMachine::CoffeeMachine()
{
	std::ifstream f(fName);

	if (!f)
	{
		std::cout << ("Ошибка открытия файла") << std::endl;
		money = 0;
		return;
	}

	f >> this->money;

	if (!f)
	{
		std::cout << ("Ошибка чтения из файла") << std::endl;
		money = 0;
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
			std::cout << ("Ошибка чтения из файла") << std::endl;
			return;
		}

		int count;
		f >> count;
		if (!f)
		{
			std::cout << ("Ошибка чтения из файла") << std::endl;
			return;
		}

		drinks.push_back(Drink(name, count, cost));
	}
	while (true);
}

CoffeeMachine::~CoffeeMachine()
{
	saveCondition();
}

void CoffeeMachine::addMoney(int money)
{
	this->money += money;
	out << money << " рублей успешно зачислено" << std::endl;
}

int CoffeeMachine::buy(int drinkID)
{
	if (drinkID < 0 || drinkID >= drinks.size()) return 3; //bad index
	if (drinks[drinkID].getPrice() > money) return 1; //checking if enough money
	if (drinks[drinkID].getAmount() < 1) return 2; // if drink is available
	drinks[drinkID].deleteDrink();
	money -= drinks[drinkID].getPrice();
	return 0;
}

void CoffeeMachine::showAvailable()
{
	for (auto it = drinks.begin(); it != drinks.end(); ++it)
	{
		out << it->getName() << ". Индекс " << it - drinks.begin() << ". Цена " << it->getPrice() << ". Кол-во доступных " << it->getAmount() << std::endl;
	}
}

void CoffeeMachine::moneyBack()
{
	out << "Возьмите ваши: " << money << " рублей обратно, нищеброд" << std::endl;
	money = 0;
}

void CoffeeMachine::setCommand() const
{
	std::fstream f;
	f.open(transferFile, std::ios::out | std::ios::trunc);

	if (!f)
	{
		std::cout << ("Ошибка открытия файла") << std::endl;
		return;
	}

	f << out.str();
	f.close();
}

std::vector<std::string> CoffeeMachine::getCommand() const
{
	std::fstream f;
	f.open(transferFile, std::ios::in);

	if (!f)
	{
		std::cout << ("Ошибка открытия файла") << std::endl;
		return std::vector<std::string>();
	}

	f.seekg(0, std::ios::end);
	int size = static_cast<int>(f.tellg());
	char* line = new char[size + 1];

	//стали на чтение
	f.seekg(0);
	for (int i = 0; i < size; ++i)
	{
		line[i] = f.get();
	}
	f.close();

	//break to strings
	std::vector<std::string> res;
	res.push_back(std::string());

	for (int i = 0; i < size; ++i)
	{
		if (line[i] == ' ')
		{
			res.push_back(std::string());
			continue;
		}

		res.back().push_back(line[i]);
	}

	delete [] line;

	return res;
}

void CoffeeMachine::proceed()
{
	auto argv = getCommand();

	//clearing out;
	out.str("");

	//proceed operation
	if (argv[0] == std::string("a"))
	{
		this->addMoney(std::stoi(argv[1]));
	}
	else if (argv[0] == std::string("b"))
	{
		int result = this->buy(stoi(argv[1]));
		switch (result)
		{
		case 0: out << ("Спасибо за покупку") << std::endl;
			break;
		case 1: out << ("Недостаточно средств") << std::endl;
			break;
		case 2: out << ("Извините, данного напитка нет в наличии") << std::endl;
			break;
		case 3: out << ("Несуществующий ID напитка") << std::endl;
			break;
		default: out << ("Неизвестная ошибка") << std::endl;
			break;;
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
		out << ("Ошибка") << std::endl;
	}

	setCommand();
}

void CoffeeMachine::saveCondition()
{
	std::ofstream f(fName);

	if (!f)
	{
		std::cout << ("Ошибка открытия файла") << std::endl;
		return;
	}

	f << money << std::endl;

	for (auto it = drinks.begin(); it != drinks.end(); ++it)
	{
		f << it->getName() << " " << it->getPrice() << " " << it->getAmount() << std::endl;
	}

	f.close();
}
