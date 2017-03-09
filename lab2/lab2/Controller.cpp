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
	//todo Windows
#elif (defined(__linux__) || defined(__unix__))
	//todo linux
#endif

void WorkAsPerson()
{
	//TODO compille!!!!!!
	//TODO TVS: add two other events
	//TODO TVS: add event array declaration
	//TODO TVS: NULL write by CAPS LOCK
	//TODO TVS: WinAPI funcs starts with upper-case letter (always)
	//TODO TVS: add #ifdef block to WinAPI part
	
	//check machine (chek opening flags)
	if(!event[0]=OpenEvent(EVENT_ALL_ACCESS,null,isMachineFree))
	{
		std::cout<<"Ошибка! Автомат не запущен";		//error. Machine is not started
		CloseHandle(event[0]);
		return;
	}
	
	Person person;

	//start loop
	do
	{
		person.runConsole();
		//wait 1
		waitForSingleObject(event[0],INFINITE);
		
		person.sendRequest();
		//raise flag2
		if(!PulseEvent(event[1]))
		{
			std::cout<<"Ошибка! Не уделось провзаимодействовать с автоматом";		//error. Event is not pulsed
			return;
		}
		
		//wait flag3
		waitForSingleObject(event[2],INFINITE);
		
		person.getResponce();
		//raise flag2
		if(!PulseEvent(event[1]))
		{
			std::cout<<"Ошибка! Не уделось провзаимодействовать с автоматом";		//error. Event is not pulsed
			return;
		}
		
	}
	while(true);
}

void WorkAsCoffeeMachine() //TVS
{
#ifdef _WIN32
	//TODO  compile!!!!!
	//TODO TVS: HANDLE write in CAPS
	
	Handle* event[3];
	
	//check existing
	if(event[0]=OpenEvent(null,null,isMachineFree))
	{
		std::cout<<"Ошибка! Автомат уже запущен.";		//error. Machine already started
		CloseHandle(event[0]);
		return;
	}//TODO TVS: else after return is redundant
	else if(event[1]=OpenEvent(null,null,fromUser))
	{
		std::cout<<"Ошибка! Автомат уже запущен.";		//error. Machine already started
		CloseHandle(event[1]);
		return;
	}
	else if(event[2]=OpenEvent(null,null,fromMachine))
	{
		std::cout<<"Ошибка! Автомат уже запущен.";		//error. Machine already started
		CloseHandle(event[2]);
		return;
	}
	
	//create events
	event[0]=CreateEvent(null,false,false,isMachineFree);
	event[1]=CreateEvent(null,false,false,fromUser);
	event[2]=CreateEvent(null,false,false,fromMachine);
	
	
	CoffeMachine machine;
	do
	{
		//raise flag1
		if(!PulseEvent(event[0]))
		{
			std::cout<<"Ошибка! Не уделось провзаимодействовать с пользователем.";		//error. Event is not pulsed
			return;
		}
		
		// wait	flag2
		waitForSingleObject(event[1],INFINITE);
		
		machine.proceed();
		
		//raise flag3
		if(!PulseEvent(event[2]))
		{
			std::cout<<"Ошибка! Не уделось провзаимодействовать с пользователем";		//error. Event is not pulsed
			return;
		}
		
		//wait flag2
		waitForSingleObject(event[1],INFINITE);
		
		machine.writeToFile();
	}
	while(true);
	
	//TODO TVS: close handles
	
#elif (defined(__linux__) || defined(__unix__))
	//todo linux
#endif
	
}
