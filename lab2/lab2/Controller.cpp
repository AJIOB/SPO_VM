#ifdef _WIN32

#include <windows.h>

#elif (defined(__linux__) || defined(__unix__))

#include <queue>
#include <cstring>
#include <signal.h>
#include <sys/types.h>
#include <unistd.h>

#else
#error Bad operation system. Please, recompile me to Linux, Unix or Windows
#endif


#include "Controller.h"

#ifdef _WIN32
namespace
{
	const LPCTSTR isMachineFree = TEXT("isMachineFree");
	const LPCTSTR fromUser = TEXT("fromUser");
	const LPCTSTR fromMachine = TEXT("fromMachine");
	const LPCTSTR disconnectUser = TEXT("disconnectUser");
}
#elif (defined(__linux__) || defined(__unix__))
namespace
{
	const char ServerPIDfilename[] = "serverPID.db";
	const int SIGF0 = 10;
	const int SIGF1 = 11;
	const int SIGF2 = 12;

	std::queue<pid_t> PIDq;
	bool signalIsHere[] = {false, false, false};
}
#endif


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
	HANDLE EVENT[4];

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
		CloseHandle(EVENT[1]);
		return;
	}

	EVENT[2] = OpenEvent(EVENT_ALL_ACCESS, NULL, fromMachine);
	if (EVENT[2] == NULL)
	{
		std::cout << "Ошибка! Автомат не запущен"; //error. Machine is not started
		CloseHandle(EVENT[2]);
		return;
	}
	EVENT[3] = OpenEvent(EVENT_ALL_ACCESS, NULL, disconnectUser);
	if (EVENT[3] == NULL)
	{
		std::cout << "Ошибка! Автомат не запущен"; //error. Machine is not started
		CloseHandle(EVENT[3]);
		return;
	}

	Person person;
	std::cout << "Ждем совей очереди..." << std::endl;

	//wait 1
	WaitForSingleObject(EVENT[0],INFINITE);

	//start loop
	do
	{
		if (!person.runConsole())
		{
			break;
		}
		
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

	if (!SetEvent(EVENT[3]))
	{
		std::cout << "Ошибка! Не уделось провзаимодействовать с автоматом"; //error. Event is not pulsed
	}

	for (int i = 0; i < 4; i ++)
	{
		CloseHandle(EVENT[i]);
	}
}

void WorkAsCoffeeMachine() //TVS
{
	HANDLE EVENT[4];

	//check existing
	EVENT[0] = OpenEvent(EVENT_ALL_ACCESS, NULL, isMachineFree);
	if (EVENT[0] != NULL)
	{
		std::cout << "Ошибка! Автомат уже запущен. Для выхода введите любой символ"; //error. Machine already started
		CloseHandle(EVENT[0]);
		std::cin.get();
		return;
	}

	EVENT[1] = OpenEvent(EVENT_ALL_ACCESS, NULL, fromUser);
	if (EVENT[1] != NULL)
	{
		std::cout << "Ошибка! Автомат уже запущен. Для выхода введите любой символ"; //error. Machine already started
		CloseHandle(EVENT[1]);
		std::cin.get();
		return;
	}

	EVENT[2] = OpenEvent(EVENT_ALL_ACCESS, NULL, fromMachine);
	if (EVENT[2] != NULL)
	{
		std::cout << "Ошибка! Автомат уже запущен. Для выхода введите любой символ"; //error. Machine already started
		CloseHandle(EVENT[2]);
		std::cin.get();
		return;
	}
	EVENT[3] = OpenEvent(EVENT_ALL_ACCESS, NULL, disconnectUser);
	if (EVENT[3] != NULL)
	{
		std::cout << "Ошибка! Автомат уже запущен. Для выхода введите любой символ"; //error. Machine already started
		CloseHandle(EVENT[3]);
		std::cin.get();
		return;
	}

	//create events
	EVENT[0] = CreateEvent(NULL, false, false, isMachineFree);
	EVENT[1] = CreateEvent(NULL, false, false, fromUser);
	EVENT[2] = CreateEvent(NULL, false, false, fromMachine);
	EVENT[3] = CreateEvent(NULL, false, false, disconnectUser);


	CoffeMachine machine;

	//raise flag1
	if (!SetEvent(EVENT[0]))
	{
		std::cout << "Ошибка! Не уделось провзаимодействовать с пользователем."; //error. Event is not pulsed
		return;
	}

	HANDLE E1[] = {EVENT[1], EVENT[3]};

	do
	{
		//wait flag2
		DWORD dw = WaitForMultipleObjects(2, E1, false, INFINITE);
		switch (dw)
		{
		case WAIT_FAILED:
			std::cout << "Ошибка! Не уделось провзаимодействовать с пользователем";
			break;
		case WAIT_OBJECT_0 + 0:
			machine.proceed();
			machine.writeToFile();

			//raise flag3
			if (!SetEvent(EVENT[2]))
			{
				std::cout << "Ошибка! Не уделось провзаимодействовать с пользователем"; //error. Event is not pulsed
				return;
			}

			WaitForSingleObject(EVENT[1],INFINITE);

			break;
		case WAIT_OBJECT_0 + 1:
			//raise flag1
			if (!SetEvent(EVENT[0]))
			{
				std::cout << "Ошибка! Не уделось провзаимодействовать с пользователем."; //error. Event is not pulsed
				return;
			}
			break;
		default: 
			std::cout << "Ошибка! Что-то пошло не так. Вы не должны видеть это.";
		}
	}
	while (true);

	for (int i = 0; i < 3; i ++)
	{
		CloseHandle(EVENT[i]);
	}
}

#elif (defined(__linux__) || defined(__unix__))

pid_t StartWorkingWithNewUser()
{
	if (PIDq.empty())
	{
		return 0;
	}

	pid_t currPID = PIDq.front();
	PIDq.pop();
	if (currPID == 0)
	{
		return 0;
	}

	kill(currPID, SIGF0);

	return currPID;
}

//save pid to queue
void hdlF0Machine(int sig, siginfo_t* sigptr, void*)
{
	if (!sigptr)
	{
		return;
	}

	PIDq.push(sigptr -> si_pid);

	signalIsHere[0] = true;
}

//нужно обработать результаты
void hdlF1Machine(int sig, siginfo_t* sigptr, void*)
{
	signalIsHere[1] = true;
}

//предыдущий пользователь закончил работу
void hdlF2Machine(int sig, siginfo_t* sigptr, void*)
{
	signalIsHere[2] = true;
}

int setSigAction(int sig, void (*handleFun) (int, siginfo_t*, void*))
{
	struct sigaction act;
	memset(&act, NULL, sizeof(act));	//clear all struct
	act.sa_sigaction = handleFun;
	act.sa_flags = SA_SIGINFO;
	sigset_t set;
	sigemptyset(&set);
	sigaddset(&set, sig);
	act.sa_mask = set;
	return sigaction(sig, &act, NULL);
}

void setSigsMachine()
{
	setSigAction(SIGF0, hdlF0Machine);
	setSigAction(SIGF1, hdlF1Machine);
	setSigAction(SIGF2, hdlF2Machine);
}

void WritePID(pid_t pid)
{
	std::fstream f;
	f.open(ServerPIDfilename, std::ios::out | std::ios::trunc);

	if (!f)
	{
		std::cout << ("Ошибка открытия файла") << std::endl;
		return;
	}

	f << (int)pid;
	f.close();
}

void WorkAsCoffeeMachine()
{
	setSigsMachine();

	WritePID(getpid());

	pid_t currPID = 0;
	bool isWorkWithUserNow;
	CoffeMachine machine;

	isWorkWithUserNow = false;

	currPID = 0;	

	while (true)
	{
		if (!isWorkWithUserNow)
		{
			currPID = StartWorkingWithNewUser();

			if (currPID != 0)
			{
				isWorkWithUserNow = true;
			}
		}

		if (signalIsHere[2])
		{
			signalIsHere[2] = false;
			isWorkWithUserNow = false;
			continue;
		}

		if (signalIsHere[1])
		{
			signalIsHere[1] = false;
			machine.proceed();
			machine.writeToFile();

			kill(currPID, SIGF1);

			continue;
		}
	}
}

//------------------Person--------------
//значит, можно начинать работу
void hdlF0Person(int sig, siginfo_t* sigptr, void*)
{
	signalIsHere[0] = true;
}

//можем читать результат
void hdlF1Person(int sig, siginfo_t* sigptr, void*)
{
	signalIsHere[1] = true;
}


void setSigsPerson()
{
	setSigAction(SIGF0, hdlF0Person);
	setSigAction(SIGF1, hdlF1Person);
}


pid_t getServerPID()
{
	std::fstream f;
	f.open(ServerPIDfilename, std::ios::in);

	if (!f)
	{
		std::cout << ("Ошибка взаимодействия с автоматом. Пожалуйста, сначала запустите автомат") << std::endl;
		return 0;
	}

	int buffer;

//стали на чтение
	f.seekg(0);
	f >> buffer;
	if (!f)
	{
		std::cout << ("Ошибка взаимодействия с автоматом. Пожалуйста, сначала запустите автомат") << std::endl;
		f.close();
		return 0;
	}
	f.close();

	return buffer;
}

void WorkAsPerson()
{
	setSigsPerson();

	pid_t serverPID = getServerPID();

	if (serverPID == 0)
	{
		return;
	}

	std::cout << "Ждем совей очереди..." << std::endl;

	kill(serverPID, SIGF0);

	while (!signalIsHere[0]) {}

	signalIsHere[0] = false;

	Person person;

	while (true)
	{
		if (!person.runConsole())
		{
			break;
		}

		person.sendRequest();
		
		kill(serverPID, SIGF1);

		while (!signalIsHere[1]) {}

		signalIsHere[1] = false;

		person.getResponce();
	}

	kill(serverPID, SIGF2);
}

#endif
