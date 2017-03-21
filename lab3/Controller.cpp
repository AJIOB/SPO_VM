#include "Controller.h"

void SelectMode()
{
	std::cout << "Выберите, пожалуйста, режим работы:" << std::endl;
	std::cout << "1) Пользователь" << std::endl;
	std::cout << "2) Автомат" << std::endl;
	std::cout << "Пожалуйста, сделайте свой выбор" << std::endl;

	auto k = std::cin.get();
	Stream::Clear();

	switch (k)
	{
	case '1':
		{
			WorkAsPerson();
			break;
		}
	case '2':
		{
			WorkAsCoffeeMachine();
			break;
		}
	default:
		{
			throw VA_Exception("Извините, такого варианта не существует. Выходим...");
		}
	}
}

void WorkAsPerson()
{
	std::string name;
	std::cout<<"Введите ваше имя"<<std::endl;
	Stream::Input(name);

	PersonController controller(name);
	controller.run();
}

void WorkAsCoffeeMachine()
{
	CoffeeMachineController controller;
	controller.run();
}
