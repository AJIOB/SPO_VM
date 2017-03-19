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

#include "PersonController.h"

namespace
{
	using namespace VA::constants;
}

#ifdef _WIN32

PersonController::PersonController(std::string name) : person(name)
{
	//check machine (chek opening flags)
	EVENT[0] = OpenEvent(EVENT_ALL_ACCESS, NULL, isMachineFree);
	if (EVENT[0] == NULL)
	{
		throw NoRunningMachineException();
	}

	EVENT[1] = OpenEvent(EVENT_ALL_ACCESS, NULL, fromUser);
	if (EVENT[1] == NULL)
	{
		CloseHandle(EVENT[0]);
		throw NoRunningMachineException();
	}

	EVENT[2] = OpenEvent(EVENT_ALL_ACCESS, NULL, fromMachine);
	if (EVENT[2] == NULL)
	{
		CloseHandle(EVENT[0]);
		CloseHandle(EVENT[1]);
		throw NoRunningMachineException();
	}
	EVENT[3] = OpenEvent(EVENT_ALL_ACCESS, NULL, disconnectUser);
	if (EVENT[3] == NULL)
	{
		CloseHandle(EVENT[0]);
		CloseHandle(EVENT[1]);
		CloseHandle(EVENT[2]);
		throw NoRunningMachineException();
	}
}

PersonController::~PersonController()
{
	if (!SetEvent(EVENT[3]))
	{
		std::cout << "Ошибка! Не удалось провзаимодействовать с автоматом"; //error. Event is not pulsed
	}

	for (int i = 0; i < 4; i ++)
	{
		CloseHandle(EVENT[i]);
	}
}

void PersonController::run()
{
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
			throw CannotWorkWithMachineException();
		}

		//wait flag3
		WaitForSingleObject(EVENT[2],INFINITE);

		person.getResponce();
		//raise flag2

		if (!SetEvent(EVENT[1]))
		{
			throw CannotWorkWithMachineException();
		}
	}
	while (true);
}

#elif (defined(__linux__) || defined(__unix__))

namespace
{
	bool signalIsHere[] = {false, false, false};
}

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

int setSigActionPerson(int sig, void (*handleFun) (int, siginfo_t*, void*))
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

pid_t PersonController::getServerPID()
{
	std::fstream f;
	f.open(serverPIDfilename, std::ios::in);

	if (!f)
	{
		throw NoRunningMachineException();
	}

	int buffer;

//стали на чтение
	f.seekg(0);
	f >> buffer;
	if (!f)
	{
		f.close();
		throw NoRunningMachineException();
	}
	f.close();

	return buffer;
}

PersonController::PersonController()
{
	setSigActionPerson(SIGF0, hdlF0Person);
	setSigActionPerson(SIGF1, hdlF1Person);

	pid_t serverPID = getServerPID();

	if (serverPID == 0)
	{
		throw NoRunningMachineException();
	}
}

void PersonController::run()
{
	std::cout << "Ждем совей очереди..." << std::endl;

	kill(serverPID, SIGF0);

	while (!signalIsHere[0]) {}

	signalIsHere[0] = false;

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
}

PersonController::~PersonController()
{
	kill(serverPID, SIGF2);
}

#endif
