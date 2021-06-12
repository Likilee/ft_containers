/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kihoonlee <kihoonlee@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/11 14:10:31 by kilee             #+#    #+#             */
/*   Updated: 2021/06/12 22:47:33 by kihoonlee        ###   ########.fr       */
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
sizeof(int);
sizeof(void);
sizeof(char);
	// std::cout << std::iterator_traits<std::map<int,int>::iterator>::iterator_category << std::endl;
	std::vector<int> stdtest(stdmap.begin(), stdmap.end());
	std::cout << *stdtest.begin() << std::endl;


}