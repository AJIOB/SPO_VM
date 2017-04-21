#pragma once
#include "types.h"

struct VA_FSClusterHead
{
	BlockPtr prev;
	BlockPtr next;
	LittleSize size;
};
