﻿#ifdef _WIN32

#include <windows.h>
#define BUF_SIZE 256
#elif (defined(__linux__) || defined(__unix__))

#include <queue>
#include <cstring>
#include <signal.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/stat.h>        /* For mode constants */
#include <fcntl.h>           /* For O_* constants */
#include <pthread.h>		//for mutex

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
	newCommand[0] = OpenEvent(EVENT_ALL_ACCESS, NULL, addNewCommand);
	if (newCommand[0] == NULL)
	{
		CloseHandle(EVENT[0]);
		CloseHandle(EVENT[1]);
		CloseHandle(EVENT[2]);
		CloseHandle(EVENT[3]);
		throw NoRunningMachineException();
	}
	newCommand[1] = OpenEvent(EVENT_ALL_ACCESS, NULL, acceptNewCommand);
	if (newCommand[1] == NULL)
	{
		CloseHandle(EVENT[0]);
		CloseHandle(EVENT[1]);
		CloseHandle(EVENT[2]);
		CloseHandle(EVENT[3]);
		CloseHandle(newCommand[0]);
		throw NoRunningMachineException();
	}

	//открытие мютекса
	listMutex = OpenMutex(MUTEX_ALL_ACCESS,FALSE,mutex);

	//открытие shared memory
	hFile = OpenFileMapping(FILE_MAP_ALL_ACCESS,FALSE, shmPersonName);

	if (hFile == NULL)
	{
		std::cout << "Ошибка при работе с общей памятью";
		return;
	}

	// извлечение очереди из shared memory
	fileBuf = MapViewOfFile(hFile,FILE_MAP_ALL_ACCESS,0,0,BUF_SIZE);
	if(fileBuf == NULL)
	{
		std::cout << "Ошибка при работе с общей памятью";
		CloseHandle(hFile);
		return;
	}

	WaitForSingleObject(listMutex, INFINITE);
		command[0]='a';
		strcpy(command+1,person.getName().c_str());
		CopyMemory(fileBuf,&command,sizeof(command));
		if (!SetEvent(newCommand[0]))
		{
			std::cout << "Ошибка! Не удалось провзаимодействовать с автоматом  newCommand[0]"; //error. Event is not pulsed
		}
		WaitForSingleObject(newCommand[1],INFINITE);
	ReleaseMutex(listMutex);
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


	WaitForSingleObject(listMutex, INFINITE);
	
		command[0]='d';
		strcpy(command+1,person.getName().c_str());
		CopyMemory(fileBuf,&command,sizeof(command));
		if (!SetEvent(newCommand[0]))
		{
			std::cout << "Ошибка! Не удалось провзаимодействовать с автоматом  newCommand[0]"; //error. Event is not pulsed
		}
		WaitForSingleObject(newCommand[1],INFINITE);
	
	ReleaseMutex(listMutex);

	for (int i = 0; i < 2; i ++)
	{
		CloseHandle(newCommand[i]);
	}
}

void PersonController::run()
{
	std::cout << "Ждем совей очереди..." << std::endl;
	
	
	WaitForSingleObject(listMutex, INFINITE);

	ReleaseMutex(listMutex);

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

		person.getResponce();
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
    bool nameIsRead = false;
    bool isPersonClose = false;
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

void hdlSENDNAMEPerson(int sig, siginfo_t* sigptr, void*)
{
    nameIsRead = true;
}

//нужно выключить сервер
void hdlINTPerson(int sig, siginfo_t *sigptr, void *)
{
    isPersonClose = true;
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

PersonController::PersonController(std::string name) : person(name)
{
	setSigAction(SIGF0, hdlF0Person);
	setSigAction(SIGF1, hdlF1Person);
    setSigAction(SIGSENDNAME, hdlSENDNAMEPerson);
    setSigAction(SIGINT, hdlINTPerson);

    serverPID = getServerPID();

	if (serverPID == 0)
	{
		throw NoRunningMachineException();
	}
/*
	shmPersonNameID = shm_open(shmPersonName, O_RDONLY, S_IRUSR);
	if (shmPersonNameID < 0)
	{
		throw CreateSharedMemoryException();
	}

	void* address = mmap(NULL, sizeof(commands), PROT_READ, MAP_SHARED, shmPersonNameID, 0);
	if (address == MAP_FAILED)
	{
		throw MapSharedMemoryException();
	}

	//read shm adress
	memcpy(commands, address, sizeof(commands));

	memcpy(RWlistMutex, (char *)address + sizeof(commands), sizeof(RWlistMutex));*/

	//Initialise attribute to condition.
    pthread_condattr_init(&attrcond);
    pthread_condattr_setpshared(&attrcond, PTHREAD_PROCESS_SHARED);

    pcond = new pthread_cond_t();

	//Initialise condition.
    pthread_cond_init(pcond, &attrcond);
}

void PersonController::run() {
    std::cout << "Ждем совей очереди..." << std::endl;

    sendName(true);

	kill(serverPID, SIGF0);
    kill(serverPID, SIGF0);

    while (!signalIsHere[0] && !isPersonClose) {}

    if (isPersonClose)
    {
    	return;
    }

    signalIsHere[0] = false;

    while (true)
    {
    	if (isPersonClose)
    	{
    		break;
    	}

		//may throw exception
        person.runConsole();

        person.sendRequest();

        kill(serverPID, SIGF1);

        while (!signalIsHere[1]) {}

        signalIsHere[1] = false;

        person.getResponce();
    }
}

PersonController::~PersonController()
{/*
	if (munmap(NULL, sizeof(&commands)) != 0)
	{
		std::cout << "Ошибка удаления разбиения shared memory" << std::endl;
	}

	if (shm_unlink(shmPersonName) != 0)
	{
		std::cout << "Ошибка отключения от shared memory" << std::endl;
	}*/

// Clean up mutex
    pthread_cond_destroy(pcond);
    pthread_condattr_destroy(&attrcond);

	kill(serverPID, SIGF2);

	sendName(false);
}

void PersonController::sendName(bool isAdd)
{
//todo: mutex

    std::fstream f;
    f.open(testFileName, std::ios::out | std::ios::trunc);

    if (!f)
    {
        std::cout << ("Ошибка открытия файла") << std::endl;
        return;
    }

    f << isAdd << person.getName();
    f.close();

    kill(serverPID, SIGSENDNAME);

    while(!nameIsRead){}	//todo: wait signal

    nameIsRead = false;

//end mutex
}

#endif
