/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kilee <kilee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/11 14:10:31 by kilee             #+#    #+#             */
/*   Updated: 2021/06/22 18:06:05 by kilee            ###   ########.fr       */
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
	ft::vector<int> vec;
	for (int i = 0; i < 10; ++i)
		vec.push_back(2 * i);
	ft::map<int, std::string> students;//(vec.begin(), vec.end());
	students.insert(ft::pair<int, std::string>(2, "현스키"));
	students.insert(ft::pair<int, std::string>(1, "이기훈"));
	students.insert(ft::pair<int, std::string>(5, "스키"));
	ft::map<int, std::string> students2;//(vec.begin(), vec.end());
	// students.insert(ft::pair<int, std::string>(3, "z스키"));
	// for (;itr != students.end(); ++itr)
	students2 = students;
	ft::map<int, std::string>::iterator itr = students2.begin();
		
		std::cout << itr->first << std::endl;
		--itr;
		std::cout << itr->first << std::endl;
		--itr;
		std::cout << itr->first << std::endl;
		--itr;
		std::cout << itr->first << std::endl;

	// --itr;
	// std::cout << itr->second << std::endl;
	// students.insert(std::pair<int, std::string>(1, "이기훈"));
	// students.insert(std::make_pair(2, "현숙이"));
	// itr = students.begin();
	// for(;itr != students.end(); ++itr)
	// 	std::cout << itr->second << std::endl;


}