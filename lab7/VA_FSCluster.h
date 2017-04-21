#pragma once
#include "VA_FSClusterHead.h"

struct VA_FSCluster
{
	VA_FSClusterHead cl_head;
	char* cl_data;

	VA_FSCluster();
	~VA_FSCluster();
};
