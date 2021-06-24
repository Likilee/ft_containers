
#include <string>
#include <iostream>
#include <stdlib.h>
#include <map>
#include "map.hpp"
#include <list>

#ifndef LEAK_TEST
# define LEAK_TEST 1
#endif

#ifndef TEST_NS
# define TEST_NS ft
#endif

#ifndef TEST_TK
# define TEST_TK char
#endif

#ifndef TEST_TV
# define TEST_TV int
#endif

#define T1 int
#define T2 std::string
typedef TEST_NS::map<T1, T2>::value_type T3;

static int iter = 0;


template <typename T>
std::string	printPair(const T &iterator, bool nl = true, std::ostream &o = std::cout)
{
	o << "key: " << iterator->first << " | value: " << iterator->second;
	if (nl)
		o << std::endl;
	return ("");
}

void	printSize(TEST_NS::map<T1, T2> const &mp, bool print_content = 1)
{
	std::cout << "size: " << mp.size() << std::endl;
	//std::cout << "max_size: " << mp.max_size() << std::endl;
	if (print_content)
	{
		TEST_NS::map<T1, T2>::const_iterator it = mp.begin(), ite = mp.end();
		std::cout << std::endl << "Content is:" << std::endl;
		for (; it != ite; ++it)
			std::cout << "- " << printPair(it, false) << std::endl;
	}
	std::cout << "###############################################" << std::endl;
}


template <typename MAP>
void	ft_erase(MAP &mp, const T1 param)
{
	std::cout << "\t-- [" << iter++ << "] --" << std::endl;
	mp.erase(param);
	printSize(mp);
}


TEST_TV			main()
{
	std::cout << "==================== insert test ===========================" << std::endl;

	TEST_NS::map<TEST_TK,TEST_TV> map_insert1;

	// first insert function version (single parameter):
	map_insert1.insert ( TEST_NS::pair<TEST_TK,TEST_TV>('a',100) );
	map_insert1.insert ( TEST_NS::pair<TEST_TK,TEST_TV>('z',200) );

	TEST_NS::pair<TEST_NS::map<TEST_TK,TEST_TV>::iterator,bool> ret_insert1;
	ret_insert1 = map_insert1.insert ( TEST_NS::pair<TEST_TK,TEST_TV>('z',500) );
	if (ret_insert1.second==false) {
		std::cout << "element 'z' already existed";
		std::cout << " with a value of " << ret_insert1.first->second << '\n';
	}

	// second insert function version (with hTEST_TV position):
	TEST_NS::map<TEST_TK,TEST_TV>::iterator it = map_insert1.begin();
	map_insert1.insert (it, TEST_NS::pair<TEST_TK,TEST_TV>('b',300));	// max efficiency inserting
	map_insert1.insert (it, TEST_NS::pair<TEST_TK,TEST_TV>('c',400));	// no max efficiency inserting

	// third insert function version (range insertion):
	TEST_NS::map<TEST_TK,TEST_TV> map_insert2;
	map_insert2.insert(map_insert1.begin(),map_insert1.find('c'));

	// showing contents:
	std::cout << "map_insert1 contains:\n";
	for (it=map_insert1.begin(); it!=map_insert1.end(); ++it)
		std::cout << it->first << " => " << it->second << '\n';

	std::cout << "map_insert2 contains:\n";
	for (it=map_insert2.begin(); it!=map_insert2.end(); ++it)
		std::cout << it->first << " => " << it->second << '\n';

	std::cout << "==================== insert test end ===========================" << std::endl;


	std::cout << "==================== erase test start =======================" << std::endl;
	TEST_NS::map<TEST_TK,TEST_TV> map_erase1;
	TEST_NS::map<TEST_TK,TEST_TV>::iterator iter_erase1;

	// insert some values:
	map_erase1['a']=10;
	map_erase1['b']=20;
	map_erase1['c']=30;
	map_erase1['d']=40;
	map_erase1['e']=50;
	map_erase1['f']=60;

	iter_erase1=map_erase1.find('b');
	map_erase1.erase (iter_erase1);									 // erasing by iter_erase1erator

	std::cout << "size : " << map_erase1.size() << std::endl;

	map_erase1.erase ('c');									// erasing by key
	std::cout << "size : " << map_erase1.size() << std::endl;


	iter_erase1=map_erase1.find ('e');
	map_erase1.erase ( iter_erase1, map_erase1.end() );		// erasing by range
	std::cout << "size : " << map_erase1.size() << std::endl;

	// show content:
	for (iter_erase1=map_erase1.begin(); iter_erase1!=map_erase1.end(); ++iter_erase1)
		std::cout << iter_erase1->first << " => " << iter_erase1->second << '\n';

	std::cout << "==================== erase test end ===========================" << std::endl;


	std::cout << "==================== swap test start ==========================" << std::endl;

	TEST_NS::map<TEST_TK,TEST_TV> map_swap1,map_swap2;

	map_swap1['x']=100;
	map_swap1['y']=200;

	map_swap2['a']=11;
	map_swap2['b']=22;
	map_swap2['c']=33;

	map_swap1.swap(map_swap2);

	std::cout << "map_swap1 contains:\n";
	for (TEST_NS::map<TEST_TK,TEST_TV>::iterator iter_swap = map_swap1.begin(); iter_swap != map_swap1.end(); ++iter_swap)
		std::cout << iter_swap->first << " => " << iter_swap->second << '\n';

	std::cout << "map_swap2 contains:\n";
	for (TEST_NS::map<TEST_TK,TEST_TV>::iterator iter_swap = map_swap2.begin(); iter_swap != map_swap2.end(); ++iter_swap)
		std::cout << iter_swap->first << " => " << iter_swap->second << '\n';

	std::cout << "==================== swap test end ===========================" << std::endl;

	std::cout << "==================== clear test start ===========================" << std::endl;
	TEST_NS::map<TEST_TK,TEST_TV> map_clear1;

	map_clear1['x']=100;
	map_clear1['y']=200;
	map_clear1['z']=300;

	std::cout << "map_clear1 contains:\n";
	for (TEST_NS::map<TEST_TK,TEST_TV>::iterator iter_clear1=map_clear1.begin(); iter_clear1!=map_clear1.end(); ++iter_clear1)
		std::cout << iter_clear1->first << " => " << iter_clear1->second << '\n';

	map_clear1.clear();
	map_clear1['a']=1101;
	map_clear1['b']=2202;

	std::cout << "map_clear1 contains:\n";
	for (TEST_NS::map<TEST_TK,TEST_TV>::iterator iter_clear1=map_clear1.begin(); iter_clear1!=map_clear1.end(); ++iter_clear1)
		std::cout << iter_clear1->first << " => " << iter_clear1->second << '\n';

	std::cout << "==================== clear test end =============================" << std::endl;

	std::cout << "==================== key_comp test start ===========================" << std::endl;

	TEST_NS::map<TEST_TK,TEST_TV> map_key_comp1;

	TEST_NS::map<TEST_TK,TEST_TV>::key_compare mycomp = map_key_comp1.key_comp();

	map_key_comp1['a']=100;
	map_key_comp1['b']=200;
	map_key_comp1['c']=300;

	std::cout << "map_key_comp1 contains:\n";

	TEST_TK highest = map_key_comp1.rbegin()->first;		 // key value of last element

	TEST_NS::map<TEST_TK,TEST_TV>::iterator iter_kc1 = map_key_comp1.begin();
	do {
		std::cout << iter_kc1->first << " => " << iter_kc1->second << '\n';
	} while ( mycomp((*iter_kc1++).first, highest) );

	std::cout << '\n';

	std::cout << "==================== key_comp test end =============================" << std::endl;

	std::cout << "==================== value_comp test start =============================" << std::endl;

	TEST_NS::map<TEST_TK,TEST_TV> map_valuecomp;

	map_valuecomp['x']=1001;
	map_valuecomp['y']=2002;
	map_valuecomp['z']=3003;

	std::cout << "map_valuecomp contains:\n";

	TEST_NS::pair<TEST_TK,TEST_TV> highest_vc = *map_valuecomp.rbegin();					// last element

	TEST_NS::map<TEST_TK,TEST_TV>::iterator iter_valuecomp = map_valuecomp.begin();
	do {
		std::cout << iter_valuecomp->first << " => " << iter_valuecomp->second << '\n';
	} while ( map_valuecomp.value_comp()(*iter_valuecomp++, highest_vc) );

	std::cout << "==================== value_comp test end =============================" << std::endl;

	std::cout << "==================== count test start =============================" << std::endl;

	TEST_NS::map<TEST_TK,TEST_TV> map_count;
	TEST_TK c;

	map_count ['a']=101;
	map_count ['c']=202;
	map_count ['f']=303;

	for (c='a'; c<'h'; c++)
	{
		std::cout << c;
		if (map_count.count(c)>0)
			std::cout << " is an element of map_count.\n";
		else
			std::cout << " is not an element of map_count.\n";
	}


	std::cout << "==================== count test end =============================" << std::endl;

	std::cout << "==================== bound test start =============================" << std::endl;

	TEST_NS::map<TEST_TK, TEST_TV> map_lb1;
	TEST_NS::map<TEST_TK, TEST_TV>::iterator itlow,itup;


	map_lb1['a']=20;
	map_lb1['b']=40;
	map_lb1['c']=60;
	map_lb1['d']=80;
	map_lb1['e']=100;

	itlow=map_lb1.lower_bound ('b');	// itlow points to b
	std::cout << itlow->first << std::endl;

	// if (itlow != map_lb1.end())
	// 	std::cout << itlow->first << " | " << itlow->second << std::endl;
	// else
	// 	std::cout << "can not find" << std::endl;
	itup=map_lb1.upper_bound ('d');	 // itup points to e (not d!)

	std::cout << itup->first << std::endl;

	map_lb1.erase(itlow,itup);				// erases [itlow,itup)

	//print content:
	for (TEST_NS::map<TEST_TK, TEST_TV>::iterator it=map_lb1.begin(); it!=map_lb1.end(); ++it)
		std::cout << it->first << " => " << it->second << '\n';


	std::cout << "==================== bound test end =============================" << std::endl;

	std::cout << "==================== equal_range test start =============================" << std::endl;

	TEST_NS::map<TEST_TK, TEST_TV> map_equalrange;

	map_equalrange['a']=10;
	map_equalrange['b']=20;
	map_equalrange['c']=30;

	TEST_NS::pair<TEST_NS::map<TEST_TK, TEST_TV>::iterator,TEST_NS::map<TEST_TK, TEST_TV>::iterator> ret;
	ret = map_equalrange.equal_range('b');

	std::cout << "lower bound points to: ";
	std::cout << ret.first->first << " => " << ret.first->second << '\n';

	std::cout << "upper bound points to: ";
	std::cout << ret.second->first << " => " << ret.second->second << '\n';


	std::cout << "==================== equal_range test end =============================" << std::endl;

	// std::list<T3> lst;
	// unsigned int lst_size = 7;
	// for (unsigned int i = 0; i < lst_size; ++i)
	// 	lst.push_back(T3(lst_size - i, i));

	// TEST_NS::map<T1, T2> mp(lst.begin(), lst.end());
	// TEST_NS::map<T1, T2>::iterator ibegin = mp.begin(), iend = mp.end();

	// TEST_NS::map<T1, T2> mp_range(ibegin, --(--iend));
	// for (int i = 0; ibegin != iend; ++ibegin)
	// 	ibegin->second = ++i * 5;

	// ibegin = mp.begin(); iend = --(--mp.end());
	// TEST_NS::map<T1, T2> mp_copy(mp);
	// for (int i = 0; ibegin != iend; ++ibegin)
	// 	ibegin->second = ++i * 7;

	// std::cout << "\t-- PART ONE --" << std::endl;
	// printSize(mp);
	// printSize(mp_range);
	// printSize(mp_copy);

	// mp = mp_copy;
	// mp_copy = mp_range;
	// mp_range.clear();

	// std::cout << "\t-- PART TWO --" << std::endl;
	// printSize(mp);
	// printSize(mp_range);
	// printSize(mp_copy);

	std::cout << "==================== erase test start =============================" << std::endl;

	TEST_NS::map<TEST_TK, TEST_TV> map_erase2;

	map_erase2['a'] = 5;
	map_erase2['b'] = 15;
	map_erase2['e'] = 25;
	map_erase2['z'] = 35;

	map_erase2.erase(map_erase2.begin(), map_erase2.end());

	std::cout << map_erase2.size() << std::endl;

	for (TEST_NS::map<TEST_TK, TEST_TV>::iterator iter = map_erase2.begin(); iter != map_erase2.end(); iter++)
		std::cout << iter->first << " | " << iter->second << std::endl;

	std::cout << "==================== erase test end =============================" << std::endl;

	std::cout << "==================== input test start =============================" << std::endl;

	TEST_NS::map<int, std::string> map_input;
	map_input[0] = "AAAAAA";
	map_input[1] = "BBBBB";
	map_input[2] = "CCCC";
	map_input[3] = "DDD";
	map_input[4] = "EE";
	map_input[5] = "F";

	map_input[10] = "Hi there";
	map_input[10] = "Hi there";
	for(TEST_NS::map<int, std::string>::iterator iter = map_input.begin(); iter != map_input.end(); iter++)
		std::cout << iter->first << " | " << iter->second << std::endl;

	std::cout << "==================== input test end =============================" << std::endl;


	std::cout << "==================== tricky erase test start =============================" << std::endl;


	TEST_NS::map<T1, T2> mp;

	mp[42] = "lol";

	mp[50] = "mdr";
	mp[25] = "funny";

	mp[46] = "bunny";
	mp[21] = "fizz";
	mp[30] = "buzz";
	mp[55] = "fuzzy";

	mp[18] = "bee";
	mp[23] = "coconut";
	mp[28] = "diary";
	mp[35] = "fiesta";
	mp[44] = "hello";
	mp[48] = "world";
	mp[53] = "this is a test";
	mp[80] = "hey";

	mp[12] = "no";
	mp[20] = "idea";
	mp[22] = "123";
	mp[24] = "345";
	mp[27] = "27";
	mp[29] = "29";
	mp[33] = "33";
	mp[38] = "38";

	mp[43] = "1";
	mp[45] = "2";
	mp[47] = "3";
	mp[49] = "4";
	mp[51] = "5";
	mp[54] = "6";
	mp[60] = "7";
	mp[90] = "8";

	printSize(mp);

	/* A classic btree should give this:
	 *                                      42
	 *                     /                                            \
	 *                    25                                            50
	 *           /                 \                         /                       \
	 *          21                 30                       46                       55
	 *      /       \           /      \                /       \             /           \
	 *     18       23        28        35            44         48         53             80
	 *   /   \    /    \    /    \     /   \        /   \       /   \     /    \         /     \
	 *  12   20  22    24  27    29  33    38     43    45    47    49   51    54       60      90
	 *
	 * */

	ft_erase(mp, 25); // right != NULL; left != NULL
	ft_erase(mp, 55); // right != NULL; left != NULL

	/* After deleting 25 and 55, I would get:
	 *                                      42
	 *                     /                                            \
	 *                    24                                            50
	 *           /                 \                         /                      \
	 *          21                 30                       46                      54
	 *      /       \           /      \                /       \             /           \
	 *     18       23        28        35            44         48         53             80
	 *   /   \    /         /    \     /   \        /   \       /   \     /              /     \
	 *  12   20  22        27    29  33    38     43    45    47    49   51             60      90
	 *
	 * */

	ft_erase(mp, 24); // right != NULL; left != NULL
	ft_erase(mp, 54); // right != NULL; left != NULL

	/* After deleting 24 and 54, I would get:
	 *                                      42
	 *                     /                                            \
	 *                    23                                            50
	 *           /                 \                         /                      \
	 *          21                 30                       46                      53
	 *      /       \           /      \                /       \             /           \
	 *     18       22        28        35            44         48         51             80
	 *   /   \              /    \     /   \        /   \       /   \                    /     \
	 *  12   20            27    29  33    38     43    45    47    49                  60      90
	 *
	 * */

	std::cout << "ff here" << std::endl;
	ft_erase(mp, 22); // right == NULL; left == NULL
	ft_erase(mp, 51); // right == NULL; left == NULL


	ft_erase(mp, 21); // right == NULL; left != NULL
	ft_erase(mp, 53); // right != NULL; left == NULL

	/* After deleting 22, 51 and then 21, 53, I would get:
	 *                                      42
	 *                     /                                            \
	 *                    23                                            50
	 *           /                 \                         /                      \
	 *          20                 30                       46                      80
	 *      /                   /      \                /       \                /        \
	 *     18                 28        35            44         48             60         90
	 *   /                  /    \     /   \        /   \       /   \
	 *  12                 27    29  33    38     43    45    47    49
	 *
	 * */

	ft_erase(mp, 20); // right == NULL; left != NULL

	/* After deleting 20, I would get:
	 *                                      42
	 *                     /                                            \
	 *                    23                                            50
	 *           /                 \                         /                      \
	 *          18                 30                       46                      80
	 *      /                   /      \                /       \                /        \
	 *     12                 28        35            44         48             60         90
	 *                      /    \     /   \        /   \       /   \
	 *                     27    29  33    38     43    45    47    49
	 *
	 * */

	ft_erase(mp, 23); // right != NULL; left != NULL

	/* After deleting 23, I would get:
	 *                                      42
	 *                     /                                            \
	 *                    18                                            50
	 *           /                 \                         /                      \
	 *          12                 30                       46                      80
	 *                          /      \                /       \                /        \
	 *                        28        35            44         48             60         90
	 *                      /    \     /   \        /   \       /   \
	 *                     27    29  33    38     43    45    47    49
	 *
	 * */

	ft_erase(mp, 42); // right != NULL; left != NULL; parent == NULL

	/* After deleting 42, I would get:
	 *                                      38
	 *                     /                                            \
	 *                    18                                            50
	 *           /                 \                         /                      \
	 *          12                 30                       46                      80
	 *                          /      \                /       \                /        \
	 *                        28        35            44         48             60         90
	 *                      /    \     /            /   \       /   \
	 *                     27    29  33           43    45    47    49
	 *
	 * */

	ft_erase(mp, 38); // right != NULL; left != NULL; parent == NULL

	/* After deleting 38, I would get:
	 *                                      35
	 *                     /                                            \
	 *                    18                                            50
	 *           /                 \                         /                      \
	 *          12                 30                       46                      80
	 *                          /      \                /       \                /        \
	 *                        28        33            44         48             60         90
	 *                      /    \                  /   \       /   \
	 *                     27    29               43    45    47    49
	 *
	 * */

	ft_erase(mp, 35); // right != NULL; left != NULL; parent == NULL

	/* After deleting 35, I would get:
	 *                                      33
	 *                     /                                            \
	 *                    18                                            50
	 *           /                 \                         /                      \
	 *          12                 30                       46                      80
	 *                          /                       /       \                /        \
	 *                        28                      44         48             60         90
	 *                      /    \                  /   \       /   \
	 *                     27    29               43    45    47    49
	 *
	 * */

	ft_erase(mp, 33); // right != NULL; left != NULL; parent == NULL

	/* After deleting 33, I would get:
	 *                                      30
	 *                     /                                            \
	 *                    18                                            50
	 *           /                 \                         /                      \
	 *          12                 28                       46                      80
	 *                          /      \                /       \                /        \
	 *                        27       29             44         48             60         90
	 *                                              /   \       /   \
	 *                                            43    45    47    49
	 *
	 * */



	std::cout << "==================== tricky erase test end =============================" << std::endl;


	std::cout << "==================== const iter test start ==============================" << std::endl;

	TEST_NS::map<TEST_TK, TEST_TV> map_const;

	map_const['a'] = 1;
	map_const['b'] = 2;
	map_const['c'] = 3;
	map_const['d'] = 4;

	//TEST_NS::map<TEST_TK, TEST_TV>::const_iterator c_iter = map_const.begin();
	//c_iter->second = 11;



	std::cout << "==================== const iter test start ==============================" << std::endl;


	std::cout << "==================== tricky erase iterator start ==============================" << std::endl;


	TEST_NS::map<int, int> map_teis;

	map_teis[4] = 4;
	map_teis[3] = 3;
	map_teis[1] = 1;
	map_teis[7] = 7;

	for (TEST_NS::map<int, int>::iterator iter = map_teis.begin(); iter != map_teis.end(); iter++)
		std::cout << iter->first << " | " << iter->second << std::endl;

	std::cout << "after earse" << std::endl;
	TEST_NS::map<int, int>::iterator iter = map_teis.begin();
	std::cout << "this iter : " << iter ->first << " | " << iter->second << std::endl;

	iter++; // iter-> 3
	iter++; // iter -> 4
	iter++; // iter -> 7
	iter++; // iter -> end;

	map_teis.erase(4); // delete begin (4); (root node)

	std::cout << "--iter" << std::endl;
	iter--;
	std::cout << "this iter : " << iter ->first << " | " << iter->second << std::endl;

	for (TEST_NS::map<int, int>::iterator iter = map_teis.begin(); iter != map_teis.end(); iter++)
		std::cout << iter->first << " | " << iter->second << std::endl;

	std::cout << "==================== tricky erase iterator end ==============================" << std::endl;


	if (LEAK_TEST != 0)
		system("leaks map | grep leaked 1>&2 ");
}