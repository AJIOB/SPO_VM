#include "VA_FSCluster.h"

VA_FSCluster::VA_FSCluster(): cl_data(nullptr)
{
}

VA_FSCluster::~VA_FSCluster()
{
	if (cl_data)
	{
		delete [] cl_data;
	}
}
