#include "VA_FSCluster.h"

const LittleSize VA_FSCluster::cl_maxClusterDataSize = (1 << 16) - sizeof VA_FSClusterHeadMetadata;

VA_FSCluster::VA_FSCluster(): cl_data(new char[cl_maxClusterDataSize])
{
}

VA_FSCluster::~VA_FSCluster()
{
	if (cl_data)
	{
		delete [] cl_data;
	}
}
