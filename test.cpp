/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kilee <kilee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/11 14:10:31 by kilee             #+#    #+#             */
/*   Updated: 2021/06/11 17:46:42 by kilee            ###   ########.fr       */
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
	ft::vector<int> myint;

	myint.push_back(4);
	std::cout << myint[0] << std::endl;
}