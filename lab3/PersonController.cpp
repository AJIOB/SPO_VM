#ifdef _WIN32

#include <windows.h>

#elif (defined(__linux__) || defined(__unix__))

#include <queue>
#include <cstring>
#include <signal.h>
#include <sys/types.h>
#include <unistd.h>

#include "AJIOBlib.h"

#else
#error Bad operation system. Please, recompile me to Linux, Unix or Windows
#endif

#include "PersonController.h"

namespace
{
	using namespace VA::constants;
}

#ifdef _WIN32

PersonController::PersonController()
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
		person.runConsole();

		person.sendRequest();
		//raise flag2
		if (!SetEvent(EVENT[1]))
		{
			throw WorkWithMachineException();
		}

		//wait flag3
		WaitForSingleObject(EVENT[2],INFINITE);

		person.getResponse();
		//raise flag2

		if (!SetEvent(EVENT[1]))
		{
			throw WorkWithMachineException();
		}
	}
	while (true);
}

#elif (defined(__linux__) || defined(__unix__))

namespace
{
    bool signalIsHere[] = {false, false};
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

pid_t PersonController::getServerPID()
{
    std::fstream f;
    f.open(serverPIDfilename, std::ios::in);

    if (!f)
    {
        return 0;
    }

    int buffer;

//стали на чтение
    f.seekg(0);
    f >> buffer;
    if (!f)
    {
        f.close();
        return 0;
    }
    f.close();

    return buffer;
}

PersonController::PersonController() {
    setSigAction(SIGF0, hdlF0Person);
    setSigAction(SIGF1, hdlF1Person);

    serverPID = getServerPID();

    if (serverPID == 0)
    {
        throw NoRunningMachineException();
    }
}

void PersonController::run() {
    std::cout << "Ждем совей очереди..." << std::endl;

    kill(serverPID, SIGF0);

    while (!signalIsHere[0]) {}

    signalIsHere[0] = false;

    while (true)
    {
		//may throw exception
        person.runConsole();

        person.sendRequest();

        kill(serverPID, SIGF1);

        while (!signalIsHere[1]) {}

        signalIsHere[1] = false;

        person.getResponse();
    }
}

PersonController::~PersonController()
{
    kill(serverPID, SIGF2);
}

#endif
