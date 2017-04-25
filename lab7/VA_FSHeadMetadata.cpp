#include "VA_FSHeadMetadata.h"
#include "VA_FSCluster.h"

VA_FSHeadMetadata::VA_FSHeadMetadata()
{
	reset();
}

void VA_FSHeadMetadata::reset()
{
	//cl_clusterSize = 1 << 15; //2^15
	cl_clusterSize = VA_FSCluster::cl_maxClusterDataSize + sizeof VA_FSClusterHeadMetadata; //2^15
	cl_fileWaysPos = 0;
	cl_freeClustersPos = 0;
	cl_numClusters = 1 << 15; //2^15
}
