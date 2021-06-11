#include <iostream>
#include <gtest/gtest.h>
#include <vector>
#include "vector.hpp"


//ConfigParser
TEST(back, simple)
{
	std::vector<int> stdint;
	ft::vector<int> myint;
}

TEST(Push_Back, simple)
{

}

TEST(Size, simple)
{
	std::vector<int> stdint;
	ft::vector<int> myint;
	ASSERT_EQ(stdint.size(), myint.size()); //size 0 test
	for (int i=0; i<10; i++)
	{
		stdint.push_back(i);
		myint.push_back(i);
	}
	ASSERT_EQ(stdint.size(), myint.size()); //size 10 test
}

int main(int argc, char **argv)
{
	testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}