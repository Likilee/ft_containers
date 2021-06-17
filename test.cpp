/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kilee <kilee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/11 14:10:31 by kilee             #+#    #+#             */
/*   Updated: 2021/06/17 10:51:17 by kilee            ###   ########.fr       */
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
	// ft::list<double> lst;
	// if (lst.begin() == lst.end())
	// 	std::cout << "true" << std::endl;
	// for(int i = 0; i < 10; ++i)
	// {
	// 	lst.push_back(i * 5);
	// }
	// for(int i = 0; i < 5; ++i)
	// 	lst.pop_back();

	// ft::list<double>::iterator itr = lst.begin();
	// for(int i = 0; i < 15; ++i)
	// {
	// 	std::cout << *itr++ << std::endl;
	// 	// std::cout << "size: " << lst.size() << std::endl;
	// }
	int arr[] = {3, 1, 2, 3, 4, 12};
	int arr2[] = {5, 9, 7, 8, 4, 10,7,3,4};

	ft::list<int> list(arr, &arr[6]);
	ft::list<int> list2(arr2, &arr2[6]);

	ft::list<int>::iterator itr = list2.begin();
	++itr;
	// list.splice(list.begin(), list2, itr);
	list.sort();
	list2.sort();
	list.merge(list2);
	list.reverse();
	std::cout << *itr << std::endl << std::endl;

	for(ft::list<int>::iterator itr3 = list.begin(); itr3 != list.end(); ++itr3)
		std::cout << *itr3 << std::endl;
	std::cout << std::endl;
	// for(std::list<int>::iterator itr2 = list2.begin(); itr2 != list2.end(); ++itr2)
	// 	std::cout << *itr2 << std::endl;
}