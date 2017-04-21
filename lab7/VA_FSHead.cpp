#include "VA_FSHead.h"

VA_FSHead::VA_FSHead()
{
	reset();
}

void VA_FSHead::reset()
{
	cl_clusterSize = 1 << 15;				//2^15
	cl_fileWaysPos = 0;
	cl_freeClustersPos = 0;
	cl_numClusters = 1 << 15;				//2^15
}
