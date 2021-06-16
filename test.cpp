/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kilee <kilee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/11 14:10:31 by kilee             #+#    #+#             */
/*   Updated: 2021/06/16 16:41:42 by kilee            ###   ########.fr       */
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
	int arr[] = {3, 1, 2, 3, 4, 9};
	int arr2[] = {5, 9, 7, 8, 4, 9};

	std::list<int> list2(arr, &arr[6]);
	std::list<int> list(arr2, &arr2[6]);
	// ft::vector<int> list(arr, arr + 5);
	// list.sort();
	// list2.sort();
	list.merge(list2);
	// // std::cout << list2.size()<< std::endl;
	for(std::list<int>::iterator itr = list.begin(); itr != list.end(); ++itr)
		std::cout << *itr << std::endl;
	std::cout << std::endl;
	for(std::list<int>::iterator itr = list2.begin(); itr != list2.end(); ++itr)
		std::cout << *itr << std::endl;
}