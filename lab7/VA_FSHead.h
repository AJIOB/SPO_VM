#pragma once
#include "types.h"

struct VA_FSHead
{
	LittleSize cl_clusterSize;
	BlockPtr cl_numClusters;
	BlockPtr cl_freeClustersPos;
	BlockPtr cl_fileWaysPos;

	VA_FSHead();

	void reset();
};
