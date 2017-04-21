#pragma once
#include <fstream>
#include "VA_FSHead.h"

class VA_FileSystem
{
	std::string cl_wayToFileOnDisk;
	std::fstream cl_f;

	VA_FSHead cl_beginMetadata;
	LittleSize cl_zeroClusterStartPos;

	bool readFromFS(const std::string& way, VA_File& file);
	bool writeToFS(const std::string& way, const VA_File& file);
	bool moveInFS(const std::string& sourceWay, const std::string& destinationWay);

	static bool readFromExternal(const std::string& way, VA_File& file);
	static bool writeToExternal(const std::string& way, const VA_File& file);

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
