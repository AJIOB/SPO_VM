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
	static const LPCTSTR isMachineFree = TEXT("isMachineFree");
	static const LPCTSTR fromUser = TEXT("fromUser");
	static const LPCTSTR fromMachine = TEXT("fromMachine");
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

void WorkAsCoffeeMachine() //TVS
{
#ifdef _WIN32
	//TODO 
	
	Handle* event[3];
	
	//check existing
	if(event[0]=OpenEvent(null,null,isMachineFree))
	{
		std::cout<<"Îøèáêà! Àâòîìàò óæå çàïóùåí.";		//error. Machine already started
		CloseHandle(event[0]);
		return;
	}
	else if(event[1]=OpenEvent(null,null,fromUser))
	{
		std::cout<<"Îøèáêà! Àâòîìàò óæå çàïóùåí.";		//error. Machine already started
		CloseHandle(event[1]);
		return;
	}
	else if(event[2]=OpenEvent(null,null,fromMachine))
	{
		std::cout<<"Îøèáêà! Àâòîìàò óæå çàïóùåí.";		//error. Machine already started
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
		if(!pulseEvant(event[0]))
		{
			std::cout<<"Îøèáêà! Ñîáûòèå íå ñîçäàíî";		//error. Event is not pulsed
			return;
		}
		
		// wait	flag2
		waitForSingleObject(event[1],INFINITE);
		
		machine.proceed();
		
		//raise flag3
		if(!pulseEvant(event[2]))
		{
			std::cout<<"Îøèáêà! Ñîáûòèå íå ñîçäàíî";		//error. Event is not pulsed
			return;
		}
		
		//wait flag2
		waitForSingleObject(event[1],INFINITE);
		
		machine.writeToFile();
	}
	while(true);
	
#elif (defined(__linux__) || defined(__unix__))
	//todo linux
#endif
	
}
