/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kihoonlee <kihoonlee@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/11 14:10:31 by kilee             #+#    #+#             */
/*   Updated: 2021/06/12 18:29:47 by kihoonlee        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vector>
#include <iostream>
#include "vector.hpp"

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
	std::vector<int> stdint;

	stdint.push_back(0);
	stdint.push_back(1);
	stdint.push_back(2);
	stdint.push_back(3);
	std::vector<int>::iterator itr = stdint.begin();
	std::cout << itr.base() << std::endl;
	std::cout << stdint.erase(itr, stdint.end()).base() << std::endl;


}