#include "ThreadGenerator.h"

ThreadGenerator::ThreadGenerator(const double& showInterval, const double& createNewThreadInterval) :
	showInterval(showInterval), createNewThreadInterval(createNewThreadInterval), isStopGeneration(false)
{
}

void ThreadGenerator::generateNewThread()
{
	//todo: platform-dependent
}

bool ThreadGenerator::removeThread()
{
	//todo: platform-dependent
	return false;
}

void ThreadGenerator::runGeneration()
{
	//todo: platform-dependent
}

void ThreadGenerator::stopGeneration()
{
	isStopGeneration = true;
	//todo: platform-dependent
}
