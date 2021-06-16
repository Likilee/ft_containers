/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kilee <kilee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/11 14:10:31 by kilee             #+#    #+#             */
/*   Updated: 2021/06/16 14:29:33 by kilee            ###   ########.fr       */
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
	unsigned long long arr[] = {2232131312313, 1, 2, 3, 4};
	unsigned long long a = (unsigned long long)&arr[0];
	unsigned long long b = (unsigned long long)&arr[4];
	std::vector<int> vec2(arr, &arr[5]);
	ft::vector<int> vec(arr, &arr[5]);
	// ft::vector<int> vec(arr, arr + 5);

	// // std::cout << vec2.size()<< std::endl;
	for(int i = 0; i < 5; ++i)
		std::cout << vec2[i] << std::endl;
	std::cout << std::endl;
	for(int i = 0; i < 5; ++i)
		std::cout << vec[i] << std::endl;
}