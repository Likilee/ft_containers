/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kilee <kilee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/11 14:10:31 by kilee             #+#    #+#             */
/*   Updated: 2021/06/14 09:52:22 by kilee            ###   ########.fr       */
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
	std::map<int,int> stdmap;
	stdmap[3] = 3;
	stdmap[1] = 1;
	stdmap[2] = 2;

	std::vector<int> intvec;

	intvec.pop_back();
	intvec.pop_back();
	intvec.pop_back();
	intvec.pop_back();
	intvec.pop_back();
	// std::cout << std::iterator_traits<std::map<int,int>::iterator>::iterator_category << std::endl;




}