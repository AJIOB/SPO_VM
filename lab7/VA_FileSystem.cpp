#include "VA_FileSystem.h"

bool VA_FileSystem::moveFrom(const std::string& startWay, const std::string& destinationWay)
{
	//todo
	return false;
}

bool VA_FileSystem::moveTo(const std::string& startWay, const std::string& destinationWay)
{
	//todo
	return false;
}

bool VA_FileSystem::moveIn(const std::string& startWay, const std::string& destinationWay)
{
	//todo
	return false;
}

void VA_FileSystem::resetMetadata()
{
	cl_head.reset();
}

void VA_FileSystem::readMetadata()
{
	cl_f.seekg(0);
	cl_f.read(reinterpret_cast<char*>(&cl_head), sizeof cl_head);
}

void VA_FileSystem::writeMetadata()
{
	cl_f.seekp(0);
	cl_f.write(reinterpret_cast<char*>(&cl_head), sizeof cl_head);
}

VA_FileSystem::VA_FileSystem(const std::string& wayToFile)
	: cl_wayToFileOnDisk(wayToFile), cl_f(cl_wayToFileOnDisk), cl_zeroClusterStartPos(sizeof cl_head)
{
	readMetadata();
}

void VA_FileSystem::format()
{
	resetMetadata();
	writeMetadata();
}

bool VA_FileSystem::move(const std::string& startWay, const std::string& destinationWay)
{
	//todo
	return false;
}

bool VA_FileSystem::copy(const std::string& startWay, const std::string& destinationWay)
{
	//todo
	return false;
}

bool VA_FileSystem::deleteF(const std::string& way)
{
	//todo
	return false;
}
