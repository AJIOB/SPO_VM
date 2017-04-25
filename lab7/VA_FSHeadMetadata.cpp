#include "VA_FSHeadMetadata.h"

VA_FSHeadMetadata::VA_FSHeadMetadata()
{
	reset();
}

void VA_FSHeadMetadata::reset()
{
	cl_clusterSize = 1 << 15; //2^15
	cl_fileWaysPos = 0;
	cl_freeClustersPos = 0;
	cl_numClusters = 1 << 15; //2^15
}
