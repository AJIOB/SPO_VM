#include "VA_FileSystem.h"
#include "VA_FSClusterMetadata.h"
#include "VA_FSCluster.h"

void VA_FileSystem::resetBeginMetadata()
{
	cl_beginMetadata.reset();
}

void VA_FileSystem::readBeginMetadata()
{
	cl_f.seekg(0);
	cl_f.read(reinterpret_cast<char*>(&cl_beginMetadata), sizeof cl_beginMetadata);
}

void VA_FileSystem::writeBeginMetadata()
{
	cl_f.seekp(0);
	cl_f.write(reinterpret_cast<char*>(&cl_beginMetadata), sizeof cl_beginMetadata);
}

VA_FileSystem::VA_FileSystem(const std::string& wayToFile)
	: cl_wayToFileOnDisk(wayToFile, std::ios::in | std::ios::out | std::ios::binary), cl_f(cl_wayToFileOnDisk), cl_zeroClusterStartPos(sizeof cl_beginMetadata)
{
	readBeginMetadata();
}

void VA_FileSystem::format()
{
	resetBeginMetadata();

	cl_clusterMetadata = VA_FSClusterMetadata();
	cl_clusterMetadata.cl_data = std::vector<bool>(cl_beginMetadata.cl_numClusters, true);
	
	//todo: write add Metadata (fileWays & ClusterMetadata)
	firstClusterMetadataProcessing();

	//todo:

	//cl_beginMetadata.cl_freeClustersPos =
	writeClusterMetadata();

	writeBeginMetadata();
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

BigSize VA_FileSystem::calculateNumOfBlocks(const VA_File& f)
{
	return (f.size() + VA_FSCluster::cl_maxClusterSize - 1) / VA_FSCluster::cl_maxClusterSize;
}

BigSize VA_FileSystem::calculatePosByBlockIndex(const BigSize& num) const
{
	return sizeof VA_FSHeadMetadata + cl_beginMetadata.cl_clusterSize * num;
}

void VA_FileSystem::setPosToRead(const BigSize& clusterNum)
{
	cl_f.seekg(calculatePosByBlockIndex(clusterNum));
}

void VA_FileSystem::setPosToWrite(const BigSize& clusterNum)
{
	cl_f.seekp(calculatePosByBlockIndex(clusterNum));
}

VA_FSClusterHeadMetadata VA_FileSystem::readBlockHead(const BigSize& num)
{
	setPosToRead(num);
	VA_FSClusterHeadMetadata res;
	cl_f.read(reinterpret_cast<char*>(&res), sizeof res);
	return res;
}

void VA_FileSystem::writeBlockHead(const BigSize& num, const VA_FSClusterHeadMetadata& meta)
{
	setPosToWrite(num);
	cl_f.write(reinterpret_cast<const char*>(&meta), sizeof meta);
}

void VA_FileSystem::firstClusterMetadataProcessing()
{
	//first clusterMetadata lock
	auto clusterMetaSize = calculateNumOfBlocks(cl_clusterMetadata.toString());
	std::vector<BlockPtr> clusterMetaBlocks;
	for (BigSize i = 0; i < clusterMetaSize; ++i)
	{
		clusterMetaBlocks.push_back(cl_clusterMetadata.lockBlock());
	}

	for (auto it = clusterMetaBlocks.begin(); it != clusterMetaBlocks.end(); ++it)
	{
		auto meta = readBlockHead(*it);
		if (it == clusterMetaBlocks.begin())
		{
			meta.prev = *it;			
		}
		else
		{
			meta.prev = *(it - 1);
		}
		
		if (it == clusterMetaBlocks.end())
		{
			meta.next = *it;
			meta.size = static_cast<LittleSize> (cl_clusterMetadata.toString().size() - clusterMetaSize * cl_beginMetadata.cl_clusterSize);
		}
		else
		{
			meta.prev = *(it + 1);
			meta.size = VA_FSCluster::cl_maxClusterSize;
		}
		writeBlockHead(*it, meta);
	}
}

bool VA_FileSystem::read(VA_File& file, const BlockPtr& startingPos)
{
	//todo
	return false;
}

bool VA_FileSystem::write(const VA_File& file, const BlockPtr& startingPos)
{
	//todo
	return 0;
}

void VA_FileSystem::writeClusterMetadata()
{
	//todo
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

bool VA_FileSystem::deleteFromFS(const std::string& way)
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
