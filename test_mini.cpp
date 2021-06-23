/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_mini.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kihoonlee <kihoonlee@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/11 14:10:31 by kilee             #+#    #+#             */
/*   Updated: 2021/06/23 14:13:56 by kihoonlee        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vector>
#include <list>
#include <map>
#include <iostream>
#include "vector.hpp"
#include "list.hpp"
#include "map.hpp"
#include <memory>

class Test {
	public :
		int value;

		Test() {
			value = 5;
		}
		Test(int value) {
			this->value = value;
		}
};

int	main()
{
	ft::map<int, std::string> students;//(vec.begin(), vec.end());
	students.insert(ft::pair<int, std::string>(8, "스키"));
	std::cout << students._tree.getRoot()->value->first << std::endl;
	students.insert(ft::pair<int, std::string>(2, "현스키"));
	std::cout << students._tree.getRoot()->value->first << std::endl;
	students.insert(ft::pair<int, std::string>(1, "이기훈"));
	std::cout << students._tree.getRoot()->value->first << std::endl;
	// students.erase(2);
	// std::cout << students._tree.getRoot()->value->first << std::endl;

	// students.insert(ft::pair<int, std::string>(5, "스키"));
	// students.insert(ft::pair<int, std::string>(2, "스키"));
	// students.insert(ft::pair<int, std::string>(2, "스키"));
	// students.insert(ft::pair<int, std::string>(2, "스키"));
	ft::map<int, std::string> students2;//(vec.begin(), vec.end());
	// students.insert(ft::pair<int, std::string>(3, "z스키"));
	// for (;itr != students.end(); ++itr)
	students2 = students;
	ft::map<int, std::string> students3(students2);
	for (ft::map<int, std::string>::iterator itr = students3.begin(); itr != students3.end(); ++itr)
		std::cout << itr->first << " " << itr->second << std::endl;
	std::cout << std::endl;
	ft::map<int, std::string>::iterator itr2 = students3.begin();
	// students3.erase(itr2);
	// std::cout << itr2->first << " " << itr2->second << std::endl;

	students3.erase(students3.begin(), students3.end());
	for (ft::map<int, std::string>::iterator itr = students3.begin(); itr != students3.end(); ++itr)
		std::cout << itr->first << " " << itr->second << std::endl;


	// --itr;
	// std::cout << itr->second << std::endl;
	// students.insert(std::pair<int, std::string>(1, "이기훈"));
	// students.insert(std::make_pair(2, "현숙이"));
	// itr = students.begin();
	// for(;itr != students.end(); ++itr)
	// 	std::cout << itr->second << std::endl;


}