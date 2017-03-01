#include "Person.h"

Person::Person()
{
	runMenu();
}

Person::~Person()
{
}

unsigned long long Person::inputDrinkIndex() const
{
	unsigned long long res = 0;
	std::cout << "Введите индекс напитка для покупки" << std::endl;
	Stream::Input(res);
	return res;
}

void Person::runMenu() const
{
	do
	{
		std::cout << "Выберите, пожалуйста, ваше действие:" << std::endl;
		std::cout << "1) Положить денег" << std::endl;
		std::cout << "2) Просмотреть список доступных напитков" << std::endl;
		std::cout << "3) Купить напиток" << std::endl;
		std::cout << "4) Вернуть деньги" << std::endl;
		std::cout << "0) Отойти от автомата" << std::endl;
		std::cout << "Пожалуйста, сделайте свой выбор" << std::endl;
	
		auto k = std::cin.get();
		Stream::Clear();

		bool isSelectGood = true;

		std::string params = "-m";

		switch (k)
		{
		case '0':
			return;
		case '1':
			params += " a " + std::to_string(inputMoney());
			
			break;
		case '2':
			params += " s";

			break;
		case '3':
			params += " b" + std::to_string(inputDrinkIndex());
			break;
		case '4':
			params += " m";
			break;
		default:
			std::cout << "Извините, такого варианта не существует. Пожалуйста, повторите выбор" << std::endl;
			isSelectGood = false;
		}

		//create process with parametres
		//TODO

	} while (true);
}

unsigned long long Person::inputMoney() const
{
	unsigned long long res = 0;
	std::cout << "Введите сумму, которую вы хотите положить в автомат. ВНИМАНИЕ! Автомат принимает только целые значению рубля" << std::endl;
	Stream::Input(res);
	return res;
}
