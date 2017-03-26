#include "ThreadManager.h"

ThreadManager::ThreadManager(const double& showInterval, const double& createNewThreadInterval) :
	showInterval(showInterval), createNewThreadInterval(createNewThreadInterval), isStopGeneration(false), isStopPrinting(false)
{
}

int ThreadManager::getNumOfThreads() const
{
	return flags.size();
}

#ifdef _WIN32

ThreadManager::~ThreadManager()
{
	//todo: platform-dependent
}

void ThreadManager::generateNewThread()
{
	//todo: platform-dependent
}

bool ThreadManager::removeThread(int index)
{
	//todo: platform-dependent
	return false;
}

void ThreadManager::runGeneration()
{
	//todo: platform-dependent
}

void ThreadManager::stopGeneration()
{
	isStopGeneration = true;
	//todo: platform-dependent
}

void ThreadManager::runPrinting()
{
	//todo: platform-dependent
}

void ThreadManager::stopPrinting()
{
	//todo: platform-dependent
}

bool ThreadManager::removeThread()
{
	//todo: add critical section

	bool res = removeThread(rand() % flags.size());

	return res;
}

#else

ThreadManager::~ThreadManager()
{
	//todo: platform-dependent
}

void ThreadManager::generateNewThread()
{
	//todo: platform-dependent
}

void ThreadManager::runPrinting()
{
	//todo: platform-dependent
}

void ThreadManager::stopPrinting()
{
	//todo: platform-dependent
}

void ThreadManager::runGeneration()
{
	//todo: platform-dependent
}

void ThreadManager::stopGeneration()
{
	isStopGeneration = true;
	//todo: platform-dependent
}

bool ThreadManager::removeThread(int index)
{
	//todo: platform-dependent
	return false;
}

#endif

