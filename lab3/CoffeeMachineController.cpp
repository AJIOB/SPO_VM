#ifdef _WIN32

#include <windows.h>
#include <algorithm>

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

#include "CoffeeMachineController.h"

namespace
{
	using namespace VA::constants;
}

#ifdef _WIN32

CoffeeMachineController::CoffeeMachineController()
{
	hFile = CreateFileMapping(INVALID_HANDLE_VALUE,NULL,PAGE_READWRITE,0,BUF_SIZE,shmPersonName);
	fileBuf = MapViewOfFile(hFile,FILE_MAP_ALL_ACCESS,0,0,BUF_SIZE);
	if (fileBuf == NULL)
	{
		std::cout<<"Ошибка работы с общей памятью";
		return ;
	}

	CopyMemory(fileBuf,&commands,sizeof(&commands));
	listMutex = CreateMutex(NULL,FALSE,mutex);

	outputThread = CreateThread(NULL,0,CoffeeMachineController::threadOutputting,this,0,NULL);   // returns the thread identifier 

	//check existing
	EVENT[0] = OpenEvent(EVENT_ALL_ACCESS, NULL, isMachineFree);
	if (EVENT[0] != NULL)
	{
		CloseHandle(EVENT[0]);
		throw MachineAlreadyRunningException();
	}

	EVENT[1] = OpenEvent(EVENT_ALL_ACCESS, NULL, fromUser);
	if (EVENT[1] != NULL)
	{
		CloseHandle(EVENT[1]);
		throw MachineAlreadyRunningException();
	}

	EVENT[2] = OpenEvent(EVENT_ALL_ACCESS, NULL, fromMachine);
	if (EVENT[2] != NULL)
	{
		CloseHandle(EVENT[2]);
		throw MachineAlreadyRunningException();
	}
	EVENT[3] = OpenEvent(EVENT_ALL_ACCESS, NULL, disconnectUser);
	if (EVENT[3] != NULL)
	{
		CloseHandle(EVENT[3]);
		throw MachineAlreadyRunningException();
	}

	//create events
	EVENT[0] = CreateEvent(NULL, false, false, isMachineFree);
	EVENT[1] = CreateEvent(NULL, false, false, fromUser);
	EVENT[2] = CreateEvent(NULL, false, false, fromMachine);
	EVENT[3] = CreateEvent(NULL, false, false, disconnectUser);
}

CoffeeMachineController::~CoffeeMachineController()
{
	for (int i = 0; i < 3; i ++)
	{
		CloseHandle(EVENT[i]);
	}
	UnmapViewOfFile(fileBuf);
	CloseHandle(hFile);
	CloseHandle(outputThread);
}

void CoffeeMachineController::run()
{
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
			machine.saveCondition();

			//raise flag3
			if (!SetEvent(EVENT[2]))
			{
				throw WorkWithPersonException();
			}

			WaitForSingleObject(EVENT[1],INFINITE);

			break;
		case WAIT_OBJECT_0 + 1:
			//raise flag1
			if (!SetEvent(EVENT[0]))
			{
				throw WorkWithPersonException();
			}
			break;
		default:
			std::cout << "Ошибка! Что-то пошло не так. Вы не должны видеть это.";
		}
	}
	while (true);
}

DWORD WINAPI CoffeeMachineController::threadOutputting( LPVOID lpParam)
{	
	CoffeeMachineController* p = reinterpret_cast<CoffeeMachineController*>(lpParam);
	WaitForSingleObject(p->listMutex, INFINITE);
		
	while(!p->commands.empty())
		{
			if(p->commands.front().isAdd)
			{
				p->names.push_back(p->commands.front().name);
			}
			else
			{
				auto res = std::find(p->names.begin(), p->names.end(), p->commands.front().name);
				if (res != p->names.end())
				{
					p->names.erase(res);
				}
			}
			p->commands.pop_front();
		}
		ReleaseMutex(p->listMutex);

		if(!(p->names.empty()))
		{
			WaitForSingleObject(p->listMutex, INFINITE);
			for(auto i = p->names.begin(); i != p->names.end(); i++)
			{
				std::cout<<*i << " ";
			}
	
			ReleaseMutex(p->listMutex);
		}
	return 0;
}

#elif (defined(__linux__) || defined(__unix__))

namespace
{
	std::queue<pid_t> PIDq;
	bool signalIsHere[] = {false, false, false};
    bool isMachineClose = false;
    std::list<Command> commands;
}

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

//предыдущий пользователь закончил работу
void hdlSENDNAME(int sig, siginfo_t* sigptr, void*)
{
    Command c;
    //todo: get command (temporary from file)

    std::fstream f;
    f.open(testFileName, std::ios::in);

    if (!f)
    {
        std::cout << ("Ошибка открытия файла") << std::endl;
        return;
    }

    //стали на чтение
    f.seekg(0);
    f >> c.isAdd;
    while (f)
    {
        c.name.push_back(f.get());
    }
    f.close();
    c.name.pop_back(); //лишний символ
    //end get command

    commands.push_back(c);

    //закончили читать
    kill(sigptr->si_pid, SIGSENDNAME);
}

//нужно выключить сервер
void hdlINTMachine(int sig, siginfo_t *sigptr, void *)
{
    isMachineClose = true;
}

int setSigAction(int sig, void (*handleFun) (int, siginfo_t*, void*))
{
	struct sigaction act;
	memset(&act, 0, sizeof(act));	//clear all struct
	act.sa_sigaction = handleFun;
	act.sa_flags = SA_SIGINFO;
	sigset_t set;
	sigemptyset(&set);
	sigaddset(&set, sig);
	act.sa_mask = set;
	return sigaction(sig, &act, NULL);
}


void CoffeeMachineController::writePID()
{
    std::fstream f;
    f.open(serverPIDfilename, std::ios::out | std::ios::trunc);

    if (!f)
    {
        std::cout << "Ошибка открытия файла" << std::endl;
        return;
    }

    f << (int)getpid();
    f.close();
}

void* OutputThread(void* ptr)
{
    CoffeeMachineController* cmController = reinterpret_cast<CoffeeMachineController*> (ptr);

    while (true) {
        if (isMachineClose)
        {
            break;
        }

        //do operations
        while (!commands.empty()) {
            Command c = commands.front();
            commands.pop_front();
            if (c.isAdd) {
                cmController->names.push_back(c.name);
            } else {
                auto res = std::find(cmController->names.begin(), cmController->names.end(), c.name);
                if (res == cmController->names.end()) {
                    std::cout << std::endl << "User try to remove name that not exist" << std::endl;
                }
            }
        }

        //show all elements
        std::for_each(cmController->names.begin(), cmController->names.end(),
            [](const std::string& s) {
                std::cout << s << " ";
            }
        );
    }

    pthread_exit(NULL);
}

//-------------------CoffeeMachineController-------------------------------

CoffeeMachineController::CoffeeMachineController()
{
	setSigAction(SIGF0, hdlF0Machine);
	setSigAction(SIGF1, hdlF1Machine);
	setSigAction(SIGF2, hdlF2Machine);
    setSigAction(SIGINT, hdlINTMachine);
    setSigAction(SIGSENDNAME, hdlSENDNAME);

	writePID();

	currPID = 0;
/*
	shmPersonNameID = shm_open(shmPersonName, O_RDWR | O_CREAT | O_EXCL, S_IRUSR | S_IWUSR);
	if (shmPersonNameID < 0)
	{
		throw CreateSharedMemoryException();
	}

	if (ftruncate(shmPersonNameID, sizeof(&commands) + sizeof(RWlistMutex)) != 0)
	{
		throw ReallocSharedMemoryException();
	}

	void* address = mmap(NULL, sizeof(&commands) + sizeof(RWlistMutex), PROT_READ, MAP_SHARED, shmPersonNameID, 0);
	if (address == MAP_FAILED)
	{
		throw MapSharedMemoryException();
	}

	//write adress to shm
	memcpy(address, &commands, sizeof(&commands));
*/

    createRWMutex();
    //pthread_create(&outputThread, NULL, OutputThread, this);

	//memcpy(((char *)address) + sizeof(&commands), RWlistMutex, sizeof(RWlistMutex));
}

CoffeeMachineController::~CoffeeMachineController()
{
	if (unlink(serverPIDfilename) != 0)
	{
		std::cout << "Ошибка удаления PID автомата" << std::endl;
	}

	if (pthread_mutex_destroy(RWlistMutex) != 0)
	{
		std::cout << "Ошибка удаления mutex-а" << std::endl;
	}

    if (pthread_mutexattr_destroy(&attrmutex) != 0)
    {
        std::cout << "Ошибка удаления атрибута mutex-а" << std::endl;
    }

	delete RWlistMutex;

    //pthread_join(outputThread, NULL);   //maybe we must delete it

/*
	if (munmap(NULL, sizeof(&commands)) != 0)
	{
		std::cout << "Ошибка удаления разбиения shared memory" << std::endl;
	}

	if (shm_unlink(shmPersonName) != 0)
	{
		std::cout << "Ошибка отключения от shared memory" << std::endl;
	}*/
}

void CoffeeMachineController::run()
{
	bool isWorkWithUserNow = false;

	while (true)
	{
        if (isMachineClose)
        {
            break;
        }
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
//TODO: test only
        //do operations
        while (!commands.empty()) {
            Command c = commands.front();
            commands.pop_front();
            if (c.isAdd) {
                this->names.push_back(c.name);
            } else {
                auto res = std::find(this->names.begin(), this->names.end(), c.name);
                if (res == this->names.end()) {
                    std::cout << std::endl << "User try to remove name that not exist" << std::endl;
                }
            }
        }

        //show all elements
        std::for_each(this->names.begin(), this->names.end(),
                      [](const std::string& s) {
                          std::cout << s << " ";
                      }
        );
	}
}

void CoffeeMachineController::createRWMutex()
{
    //mutex attribute (make mutex global)
    pthread_mutexattr_init(&attrmutex);
    pthread_mutexattr_setpshared(&attrmutex, PTHREAD_PROCESS_SHARED);

    //make mutex
    RWlistMutex = new pthread_mutex_t();
    if (pthread_mutex_init(RWlistMutex, &attrmutex) != 0)
    {
        throw InitMutexException();
    }
}

#endif
