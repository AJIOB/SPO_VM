#pragma once
#include <vector>

struct VA_FSClusterMetadata
{
	std::vector<bool> cl_data;
	
	bool fromString(const std::string& metaString);
	std::string toString() const;
};
