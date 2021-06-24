#include <iostream>
#include <gtest/gtest.h>
#include <vector>
#include "vector.hpp"


//CONSTRUCTOR
TEST(Vector, push_test)
{
	ft::vector<int> myint;
	std::vector<int> stdint;
	for (int i = 0; i < 100; ++i)
	{
		myint.push_back(i);
		stdint.push_back(i);
		ASSERT_EQ(myint.at(i), stdint.at(i));
		ASSERT_EQ(myint[i], stdint[i]);
		ASSERT_EQ(myint.front(), stdint.front());
		ASSERT_EQ(myint.back(), stdint.back());
		ASSERT_EQ(myint.size(), stdint.size());
		ASSERT_EQ(myint.capacity(), stdint.capacity());
		ASSERT_EQ(myint.empty(), stdint.empty());
	}
}

TEST(Vector, pop_back)
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