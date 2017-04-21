#pragma once
#include <fstream>
#include "VA_FSHead.h"

class VA_FileSystem
{
	std::string cl_wayToFileOnDisk;
	std::fstream cl_f;

	VA_FSHead cl_head;
	LittleSize cl_zeroClusterStartPos;

	bool moveFrom(const std::string& startWay, const std::string& destinationWay);
	bool moveTo(const std::string& startWay, const std::string& destinationWay);
	bool moveIn(const std::string& startWay, const std::string& destinationWay);
	void resetMetadata();
	void readMetadata();
	void writeMetadata();

public:
	VA_FileSystem(const std::string& wayToFile);

	void format();
	bool move(const std::string& startWay, const std::string& destinationWay);
	bool copy(const std::string& startWay, const std::string& destinationWay);
	bool deleteF(const std::string& way);
};
