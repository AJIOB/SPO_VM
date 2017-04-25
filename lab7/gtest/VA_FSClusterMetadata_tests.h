#pragma once

#include <gtest/gtest.h>
#include "VA_FSClusterMetadata.h"

namespace VA_FSClusterMetadata_tests
{
	TEST(toString, 8bit)
	{
		std::vector<bool> vec;
		vec.push_back(true);
		vec.push_back(true);
		vec.push_back(false);
		vec.push_back(true);
		vec.push_back(false);
		vec.push_back(true);
		vec.push_back(false);
		vec.push_back(true);
		//10101011

		VA_FSClusterMetadata cm;
		cm.cl_data = vec;

		EXPECT_TRUE(cm.toString()[cm.toString().size() - 1] == (char)171);
		EXPECT_EQ(cm.toString().size(), 1 + sizeof cm.toString().size());
	}

	TEST(toString, 11bit)
	{
		std::vector<bool> vec;
		vec.push_back(true);
		vec.push_back(true);
		vec.push_back(false);
		vec.push_back(true);
		vec.push_back(false);
		vec.push_back(true);
		vec.push_back(false);
		vec.push_back(true);

		vec.push_back(true);
		vec.push_back(false);
		vec.push_back(true);
		//101 10101011

		VA_FSClusterMetadata cm;
		cm.cl_data = vec;
		auto str = cm.toString();
		EXPECT_TRUE(str[str.size() - 2] == (char)171);
		EXPECT_TRUE(str[str.size() - 1] % 8 == (char)5 || str[str.size() - 1] % 8 == (char)-3);
		EXPECT_EQ(str.size(), 2 + sizeof str.size());
	}

	TEST(fromString, 8bit)
	{
		std::vector<bool> vec;
		vec.push_back(true);
		vec.push_back(true);
		vec.push_back(false);
		vec.push_back(true);
		vec.push_back(false);
		vec.push_back(true);
		vec.push_back(false);
		vec.push_back(true);
		//10101011

		VA_FSClusterMetadata cm;
		std::string s;
		s.push_back(8);
		s.push_back(0);
		s.push_back(0);
		s.push_back(0);
		s.push_back(171);

		EXPECT_TRUE(cm.fromString(s));
		EXPECT_TRUE(cm.cl_data == vec);
	}

	TEST(fromString, 11bit)
	{
		std::vector<bool> vec;
		vec.push_back(true);
		vec.push_back(true);
		vec.push_back(false);
		vec.push_back(true);
		vec.push_back(false);
		vec.push_back(true);
		vec.push_back(false);
		vec.push_back(true);

		vec.push_back(true);
		vec.push_back(false);
		vec.push_back(true);
		//101 10101011

		VA_FSClusterMetadata cm;
		std::string s;
		s.push_back(11);
		s.push_back(0);
		s.push_back(0);
		s.push_back(0);
		s.push_back(171);
		s.push_back(37); //must be num % 8 = 5

		EXPECT_TRUE(cm.fromString(s));
		EXPECT_TRUE(cm.cl_data == vec);
	}
}
