/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kilee <kilee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/11 14:10:31 by kilee             #+#    #+#             */
/*   Updated: 2021/06/14 16:19:09 by kilee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vector>
#include <map>
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
// 	std::map<int,int> stdmap;
// 	stdmap[3] = 3;
// 	stdmap[1] = 1;
// 	stdmap[2] = 2;

// 	std::vector<int> intvec;

// 	intvec.pop_back();
// 	intvec.pop_back();
// 	intvec.pop_back();
// 	intvec.pop_back();
// 	intvec.pop_back();
// 	// std::cout << std::iterator_traits<std::map<int,int>::iterator>::iterator_category << std::endl;

// 	std::vector<int>::iterator itr;
// 	std::vector<int>::const_iterator itr2;
// 	// std::vector<int>::reverse_iterator itr3;
// 	// std::vector<int>::const_reverse_iterator itr4;
// 	if (itr - itr2 == 0)
// 		std::cout << "done" << std::endl;

	ft::vector<int> vct2;

	vct2.insert(vct2.end(), 42);
	vct2.insert(vct2.begin(), 2, 21);

	for (ft::vector<int>::iterator iter = vct2.begin(); iter != vct2.end(); iter++)
		std::cout << *iter << ' ';
}