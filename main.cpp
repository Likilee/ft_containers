#include "vector.hpp"
#include <iostream>
#include <vector>

#define TEST_NS ft

int main()
{
	TEST_NS::vector<int> v;
	TEST_NS::vector<int>::iterator retitr;
	// for (int i=0; i<100; i++)
	// 	v.push_back(i);
	retitr = v.insert(v.begin(), 5);

	std::cout << "Capacity: " << v.capacity() << std::endl;
	for (TEST_NS::vector<int>::iterator itr = v.begin(); itr != v.end(); ++itr)
		std::cout << *itr << std::endl;
	std::cout << "Retitr: " << *retitr << std::endl;
	std::cout << std::endl;

	retitr = v.insert(v.begin(), 4);
	std::cout << "Capacity: " << v.capacity() << std::endl;
	for (TEST_NS::vector<int>::iterator itr = v.begin(); itr != v.end(); ++itr)
		std::cout << *itr << std::endl;
	std::cout << "Retitr: " << *retitr << std::endl;
	std::cout << std::endl;

	retitr = v.insert(v.begin(), 3);
	std::cout << "Capacity: " << v.capacity() << std::endl;
	for (TEST_NS::vector<int>::iterator itr = v.begin(); itr != v.end(); ++itr)
		std::cout << *itr << std::endl;
	std::cout << "Retitr: " << *retitr << std::endl;
	std::cout << std::endl;

	retitr = v.insert(v.begin(), 2);
	std::cout << "Capacity: " << v.capacity() << std::endl;
	for (TEST_NS::vector<int>::iterator itr = v.begin(); itr != v.end(); ++itr)
		std::cout << *itr << std::endl;
	std::cout << "Retitr: " << *retitr << std::endl;
	std::cout << std::endl;

	retitr = v.insert(v.begin(), 1);
	std::cout << "Capacity: " << v.capacity() << std::endl;
	for (TEST_NS::vector<int>::iterator itr = v.begin(); itr != v.end(); ++itr)
		std::cout << *itr << std::endl;
	std::cout << "Retitr: " << *retitr << std::endl;
	std::cout << std::endl;
}
