#ifdef _WIN32

#include <windows.h>

#elif (defined(__linux__) || defined(__unix__))

#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>

#else
#error Bad operation system. Please, recompile me to Linux, Unix or Windows
#endif


#ifdef _WIN32
namespace
{
	const LPCTSTR isMachineFree = TEXT("isMachineFree");
	const LPCTSTR fromUser = TEXT("fromUser");
	const LPCTSTR fromMachine = TEXT("fromMachine");
}
#elif (defined(__linux__) || defined(__unix__))
//todo linux
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

void WorkAsPerson()
{
	HANDLE EVENT[3];

	//check machine (chek opening flags)
	EVENT[0] = OpenEvent(EVENT_ALL_ACCESS, NULL, isMachineFree);
	if (EVENT[0] == NULL)
	{
		std::cout << "Ошибка! Автомат не запущен"; //error. Machine is not started
		CloseHandle(EVENT[0]);
		return;
	}

	EVENT[1] = OpenEvent(EVENT_ALL_ACCESS, NULL, fromUser);
	if (EVENT[1] == NULL)
	{
		std::cout << "Ошибка! Автомат не запущен"; //error. Machine is not started
		CloseHandle(EVENT[0]);
		return;
	}

	EVENT[2] = OpenEvent(EVENT_ALL_ACCESS, NULL, fromMachine);
	if (EVENT[2] == NULL)
	{
		std::cout << "Ошибка! Автомат не запущен"; //error. Machine is not started
		CloseHandle(EVENT[0]);
		return;
	}
	Person person;

	//start loop
	do
	{
		if (!person.runConsole())
		{
			break;
		}
		//wait 1
		WaitForSingleObject(EVENT[0],INFINITE);

		person.sendRequest();
		//raise flag2
		if (!SetEvent(EVENT[1]))
		{
			std::cout << "Ошибка! Не уделось провзаимодействовать с автоматом"; //error. Event is not pulsed
			break;
		}

		//wait flag3
		WaitForSingleObject(EVENT[2],INFINITE);

		person.getResponce();
		//raise flag2
		if (!SetEvent(EVENT[1]))
		{
			std::cout << "Ошибка! Не уделось провзаимодействовать с автоматом"; //error. Event is not pulsed
			break;
		}
	}
	while (true);

	for (int i = 0; i < 3; i ++)
	{
		CloseHandle(EVENT[i]);
	}
}

void WorkAsCoffeeMachine() //TVS
{
	HANDLE EVENT[3];

	//check existing
	EVENT[0] = OpenEvent(NULL, NULL, isMachineFree);
	if (EVENT[0])
	{
		std::cout << "Ошибка! Автомат уже запущен."; //error. Machine already started
		CloseHandle(EVENT[0]);
		return;
	}

	EVENT[1] = OpenEvent(NULL, NULL, fromUser);
	if (EVENT[1])
	{
		std::cout << "Ошибка! Автомат уже запущен."; //error. Machine already started
		CloseHandle(EVENT[1]);
		return;
	}

	EVENT[2] = OpenEvent(NULL, NULL, fromMachine);
	if (EVENT[2])
	{
		std::cout << "Ошибка! Автомат уже запущен."; //error. Machine already started
		CloseHandle(EVENT[2]);
		return;
	}

	//create events
	EVENT[0] = CreateEvent(NULL, false, false, isMachineFree);
	EVENT[1] = CreateEvent(NULL, false, false, fromUser);
	EVENT[2] = CreateEvent(NULL, false, false, fromMachine);


	CoffeMachine machine;
	do
	{
		//raise flag1
		if (!SetEvent(EVENT[0]))
		{
			std::cout << "Ошибка! Не уделось провзаимодействовать с пользователем."; //error. Event is not pulsed
			return;
		}

		// wait	flag2
		WaitForSingleObject(EVENT[1],INFINITE);

		machine.proceed();

		//raise flag3
		if (!SetEvent(EVENT[2]))
		{
			std::cout << "Ошибка! Не уделось провзаимодействовать с пользователем"; //error. Event is not pulsed
			return;
		}

		//wait flag2
		WaitForSingleObject(EVENT[1],INFINITE);

		machine.writeToFile();
	}
	while (true);

	for (int i = 0; i < 3; i ++)
	{
		CloseHandle(EVENT[i]);
	}
}

#elif (defined(__linux__) || defined(__unix__))
void WorkAsPerson()
{
	//todo linux
}

void WorkAsCoffeeMachine()
{
	
}

#endif
