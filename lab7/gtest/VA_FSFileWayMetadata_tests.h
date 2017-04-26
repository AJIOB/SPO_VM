#pragma once

#include <gtest/gtest.h>
#include "VA_FSFileWayMetadata.h"

namespace VA_FSFileWayMetadata_tests
{
#define Map std::map<std::string, BlockPtr>

	TEST(toString, all)
	{
		Map ways;
		ways.insert(std::make_pair<std::string, BlockPtr>("one", 12));
		ways.insert(std::make_pair<std::string, BlockPtr>("two", 1));
		ways.insert(std::make_pair<std::string, BlockPtr>("three", 27));

		VA_FSFileWayMetadata cm;
		cm.cl_ways = ways;

		EXPECT_NE(cm.cl_ways, Map());

		auto str = cm.toString();

		EXPECT_NE(str, std::string());

		cm.cl_ways = Map();

		EXPECT_EQ(cm.cl_ways, Map());

		EXPECT_TRUE(cm.fromString(str));

		EXPECT_EQ(cm.cl_ways, ways);
	}
#undef Map
}
