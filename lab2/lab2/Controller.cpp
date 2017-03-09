#ifdef _WIN32

#include <windows.h>

#elif (defined(__linux__) || defined(__unix__))

#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>

#endif

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

#ifdef _WIN32
	//todo Windows
#elif (defined(__linux__) || defined(__unix__))
	//todo linux
#else
#error Bad operation system. Please, recompile me to Linux, Unix or Windows
#endif

void WorkAsPerson()
{
	//TODO
	//check machine (chek opening flags)

	Person person;

	//start loop

	person.runConsole();
	//wait 1
	person.sendRequest();
	//raise flag2
	//wait flag3
	person.getResponce();
	//raise flag2
	//loop
	
}

void WorkAsCoffeeMachine()
{
	//TODO
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