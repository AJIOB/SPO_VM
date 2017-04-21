#include "VA_FileSystem.h"
#include "VA_FSClusterMetadata.h"

void VA_FileSystem::resetMetadata()
{
	cl_beginMetadata.reset();
}

void VA_FileSystem::readMetadata()
{
	cl_f.seekg(0);
	cl_f.read(reinterpret_cast<char*>(&cl_beginMetadata), sizeof cl_beginMetadata);
}

void VA_FileSystem::writeMetadata()
{
	cl_f.seekp(0);
	cl_f.write(reinterpret_cast<char*>(&cl_beginMetadata), sizeof cl_beginMetadata);
}

VA_FileSystem::VA_FileSystem(const std::string& wayToFile)
	: cl_wayToFileOnDisk(wayToFile), cl_f(cl_wayToFileOnDisk), cl_zeroClusterStartPos(sizeof cl_beginMetadata)
{
	readMetadata();
}

void VA_FileSystem::format()
{
	resetMetadata();

	cl_beginMetadata.cl_freeClustersPos = 0;
	VA_FSClusterMetadata clusterMetadata;
	clusterMetadata.cl_data = std::vector<bool>(cl_beginMetadata.cl_numClusters, true);
	
	//todo: write add Metadata (fileWays & ClusterMetadata)

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

bool VA_FileSystem::readFromFS(const std::string& way, VA_File& file)
{
	//todo
	return false;
}

bool VA_FileSystem::writeToFS(const std::string& way, const VA_File& file)
{
	//todo
	return false;
}

bool VA_FileSystem::moveInFS(const std::string& sourceWay, const std::string& destinationWay)
{
	//todo
	return false;
}

bool VA_FileSystem::readFromExternal(const std::string& way, VA_File& file)
{
	std::fstream f(way, std::ios::in | std::ios::binary);
	if (!f)
	{
		return false;
	}

	while (f)
	{
		file.push_back(f.get());
	}

	file.pop_back();
	f.close();
	return true;
}

bool VA_FileSystem::writeToExternal(const std::string& way, const VA_File& file)
{
	std::fstream f(way, std::ios::out | std::ios::trunc | std::ios::binary);
	if (!f)
	{
		return false;
	}

	f.write(file.c_str(), file.size());

	f.close();
	return true;
}
