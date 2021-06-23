/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_mini.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kihoonlee <kihoonlee@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/11 14:10:31 by kilee             #+#    #+#             */
/*   Updated: 2021/06/23 17:23:19 by kihoonlee        ###   ########.fr       */
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
	std::cout << students.getTree().getRoot()->value->first << std::endl;
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

	int COUNT = 50;
	int SIZE = 50;
	srand(clock());
	ft::map<int, std::string> test;
	//Insert test
	std::cout << "*====== INSERT TEST ======*" << std::endl;

	for (int i = 0; i < COUNT; ++i)
		test.insert(ft::pair<int, std::string>(rand() % SIZE, "학생"));
	test._tree.print();
	std::cout << std::endl; //end Insert test

	std::cout << "*====== COPY TEST ======*" << std::endl;
	ft::map<int, std::string> test2(test);
	test2._tree.print();
	std::cout << std::endl; //end Insert test

	std::cout << "*====== BOUND TEST ======*" << std::endl;

	std::cout << "Lower3 : " << test.lower_bound(5)->first << std::endl;
	std::cout << "Upper3 : " << test.upper_bound(5)->first << std::endl;
	std::cout << std::endl; //end Insert test

	std::cout << "*====== FIND TEST ======*" << std::endl;

	// std::cout << "Found : " << test2.find(24)->first <<std::endl;
	// std::cout << "Not found : " << (test2.find(101).get_ptr() == test2.end().get_ptr()) << std::endl;	//not found;

	std::cout << std::endl; //end Insert test
	//Erase test
	std::cout << "*====== ERASE TEST ======*" << std::endl;
	for (int i = 0; i < COUNT; ++i)
	{
		test.erase(rand() % SIZE);
		test._tree.check_traversal();
	}
	test._tree.print();
	std::cout << std::endl; //end Erase test

	//Clear test
	std::cout << "*====== CLEAR TEST ======*" << std::endl;

	std::cout << std::endl; //end Clear test

	//Insert after clear test
	// std::cout << "*====== INSERT AFTER CLEAR TEST ======*" << std::endl;
	// test.insert(1004);
	// test.print();

}