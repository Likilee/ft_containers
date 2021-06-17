/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kilee <kilee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/11 14:10:31 by kilee             #+#    #+#             */
/*   Updated: 2021/06/17 15:09:46 by kilee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vector>
#include <list>
#include <map>
#include <iostream>
#include "vector.hpp"
#include "list.hpp"
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

int 		main()
{
	// ft::list<int> lst;
	// if (lst.begin() == lst.end())
	// 	std::cout << "true" << std::endl;
	// for(int i = 0; i < 10; ++i)
	// {
	// 	lst.push_back(i * 5);
	// }
	// for(int i = 0; i < 5; ++i)
	// 	lst.pop_back();

	// ft::list<int>::iterator itr = lst.begin();
	// for(int i = 0; i < 15; ++i)
	// {
	// 	std::cout << *itr++ << std::endl;
	// 	// std::cout << "size: " << lst.size() << std::endl;
	// }

	ft::list<int> list;
	ft::list<int> list2;


	list.push_back(1);
	list.push_back(2);
	list.push_back(3);

	list2.push_back(1);
	list2.push_back(4);
	list2.push_back(5);
	list2.push_back(8);

	ft::list<int>::iterator itr = list2.begin();
	++itr;
	// list.splice(list.begin(), list2, itr);
	list.sort();
	list2.sort();
	list.merge(list2);
	// list.reverse();
	// std::cout << *itr << std::endl << std::endl;
	// ft::list<int>::iterator itr4 = list2.begin();
	// std::cout << *itr4 << std::endl << std::endl;
	// ft::list<int>::iterator itr5 = itr4;
	// ++itr4;
	// if (itr5 == itr4)
	// 	std::cout << "FUCK" << std::endl;
	// std::cout << *itr4 << std::endl << std::endl;

	for(ft::list<int>::iterator itr3 = list.begin(); itr3 != list.end(); ++itr3)
		std::cout << *itr3 << std::endl;
	std::cout << std::endl;
	// for(std::list<int>::iterator itr2 = list2.begin(); itr2 != list2.end(); ++itr2)
	// 	std::cout << *itr2 << std::endl;
}