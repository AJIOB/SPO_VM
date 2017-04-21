#pragma once
#include <fstream>
#include "VA_FSHeadMetadata.h"
#include "VA_FSClusterMetadata.h"
#include "VA_FSClusterHeadMetadata.h"

class VA_FileSystem
{
	std::string cl_wayToFileOnDisk;
	std::fstream cl_f;

	VA_FSHeadMetadata cl_beginMetadata;
	VA_FSClusterMetadata cl_clusterMetadata;
	LittleSize cl_zeroClusterStartPos;

	static BigSize calculateNumOfBlocks(const VA_File& f);

	BigSize calculatePosByBlockIndex(const BigSize& num) const;
	void setPosToRead(const BigSize& clusterNum);
	void setPosToWrite(const BigSize& clusterNum);

	VA_FSClusterHeadMetadata readBlockHead(const BigSize& num);
	void writeBlockHead(const BigSize& num, const VA_FSClusterHeadMetadata& meta);

	void firstClusterMetadataProcessing();

	bool read(VA_File& file, const BlockPtr& startingPos);
	bool write(const VA_File& file, const BlockPtr& startingPos);
	void writeClusterMetadata();

	bool readFromFS(const std::string& way, VA_File& file);
	bool writeToFS(const std::string& way, const VA_File& file);
	bool moveInFS(const std::string& sourceWay, const std::string& destinationWay);
	bool deleteFromFS(const std::string& way);

	static bool readFromExternal(const std::string& way, VA_File& file);
	static bool writeToExternal(const std::string& way, const VA_File& file);

	void resetBeginMetadata();
	void readBeginMetadata();
	void writeBeginMetadata();

public:
	VA_FileSystem(const std::string& wayToFile);

	void format();
	bool move(const std::string& startWay, const std::string& destinationWay);
	bool copy(const std::string& startWay, const std::string& destinationWay);
	bool deleteF(const std::string& way);
};
