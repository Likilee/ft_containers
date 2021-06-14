#include "../iterator.hpp"
#include "../vector.hpp"
#include <vector>
#include <iostream>
#include <list>

int main(void)
{
	ft::vector<int>::iterator itr;
	std::list<int>::iterator itr2;

	// std::cout << ft::is_same<ft::random_access_iterator_tag, std::iterator_traits<std::vector<int>::iterator>::iterator_category>::value << std::endl;
// std::cout << ft::distance(itr, itr) << std::endl;
std::cout << ft::distance(itr2, itr2) << std::endl;
}