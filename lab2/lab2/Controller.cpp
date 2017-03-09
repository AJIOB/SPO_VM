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
			std::cout << "Извините, такого варианта не существует. Выходим..." << std::endl;
			break;
		}
	}
}

void WorkAsPerson()
{
	//TODO
	//check machine (chek opening flags)
	//start loop
	//console
	//wait 1
	//input to file
	//raise flag2
	//wait flag3
	//resut to console
	//raise flag2
	//loop
	
	Person person;
}

void WorkAsCoffeeMachine()
{
	//TODO
	//vector<string>
	//check existing
	//create events
	CoffeMachine machine;
	//loop start
	//raise flag1
	// wait	flag2
	machine.proceed();
	//raise flag3
	//wait flag2
	//write to file
	//loop
}