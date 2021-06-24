#include <iostream>
#include <string>
#include <vector>
#include "vector.hpp"

#ifndef LEAK_TEST
# define LEAK_TEST 1
#endif

#ifndef TEST_NS
# define TEST_NS ft
#endif

# define TESTED_TYPE std::string

template <typename T>
void	printSize(TEST_NS::vector<T> const &vct, bool print_content = 1)
{
	std::cout << "size: " << vct.size() << std::endl;
	//std::cout << "capacity: " << vct.capacity() << std::endl;
	std::cout << "max_size: " << vct.max_size() << std::endl;
	if (print_content)
	{
		typename TEST_NS::vector<T>::const_iterator it = vct.begin();
		typename TEST_NS::vector<T>::const_iterator ite = vct.end();
		std::cout << std::endl << "Content is:" << std::endl;
		for (; it != ite; ++it)
			std::cout << "- " << *it << std::endl;
	}
	std::cout << "###############################################" << std::endl;
}

void	checkErase(TEST_NS::vector<TESTED_TYPE> const &vct,
					TEST_NS::vector<TESTED_TYPE>::const_iterator const &it)
{
	static int i = 0;
	std::cout << "[" << i++ << "] " << "erase: " << it - vct.begin() << std::endl;
	printSize(vct);
}

int		main()
{
	std::cout << "===================== basic test =====================" << std::endl;

	TEST_NS::vector<int> v;
	// for (int i=0; i<100; i++)
	// 	v.push_back(i);
	v.insert(v.begin(), 5);
	v.insert(v.begin(), 4);
	v.insert(v.begin(), 3);
	v.insert(v.begin(), 2);
	v.insert(v.begin(), 1);
	v.push_back(55);

	TEST_NS::vector<int>::iterator iter = v.begin();
	iter++;
	iter++;
	std::cout << *iter << std::endl;
	v.insert(iter, 77);

	std::cout << "size : " << v.size() << std::endl;

	for (TEST_NS::vector<int>::iterator iter = v.begin(); iter != v.end(); iter++)
		std::cout << *iter << " ";
	std::cout << std::endl;


	std::cout << "===================== basic test end =================" << std::endl;

	std::cout << "===================== insert test ====================" << std::endl;

	TEST_NS::vector<int> vec_insert1 (3,100);
 	TEST_NS::vector<int>::iterator it_insert1;

	for (TEST_NS::vector<int>::iterator iter = vec_insert1.begin(); iter != vec_insert1.end(); iter++)
		std::cout << *iter << " ";
	std::cout << std::endl;

	it_insert1 = vec_insert1.begin();
	it_insert1 = vec_insert1.insert ( it_insert1 , 200 );

	for (TEST_NS::vector<int>::iterator iter = vec_insert1.begin(); iter != vec_insert1.end(); iter++)
		std::cout << *iter << " ";
	std::cout << std::endl;

	vec_insert1.insert (it_insert1,2,300);

  	// "it" no longer valid, get a new one:
	it_insert1 = vec_insert1.begin();

	// std::vector<int> vec_insert2 (2,400);
	// vec_insert1.insert (it_insert1+2,vec_insert2.begin(),vec_insert2.end());

	// int myarray [] = { 501,502,503 };
	// vec_insert1.insert (vec_insert1.begin(), myarray, myarray+3);

	std::cout << "vec_insert1 contains:";
	for (it_insert1=vec_insert1.begin(); it_insert1 < vec_insert1.end(); it_insert1++)
		std::cout << ' ' << *it_insert1;
	std::cout << '\n';

	std::cout << "===================== insert test end ================" << std::endl;


	std::cout << "===================== clear test =====================" << std::endl;

	std::vector<int> vec_clear1;
	vec_clear1.push_back (100);
	vec_clear1.push_back (200);
	vec_clear1.push_back (300);

	std::cout << "vec_clear1 contains:";
	for (unsigned i=0; i<vec_clear1.size(); i++)
		std::cout << ' ' << vec_clear1[i];
	std::cout << '\n';

	vec_clear1.clear();
	vec_clear1.push_back (1101);
	vec_clear1.push_back (2202);

	std::cout << "vec_clear1 contains:";
	for (unsigned i=0; i<vec_clear1.size(); i++)
		std::cout << ' ' << vec_clear1[i];
	std::cout << '\n';

	std::cout << "===================== clear test end =================" << std::endl;


	std::cout << "===================== assign test ====================" << std::endl;

	TEST_NS::vector<int> vec_assign_first;
	TEST_NS::vector<int> vec_assign_second;
	TEST_NS::vector<int> vec_assign_third;

	vec_assign_first.assign (7,100);             // 7 ints with a value of 100

	TEST_NS::vector<int>::iterator it;
	it=vec_assign_first.begin()+1;

	vec_assign_second.assign (it,vec_assign_first.end()-1); // the 5 central values of vec_assign_first

	int myints_assign[] = {1776,7,4};
	vec_assign_third.assign (myints_assign,myints_assign+3);   // assigning from array.

	std::cout << "Size of vec_assign_first: " << int (vec_assign_first.size()) << '\n';
	std::cout << "Size of vec_assign_second: " << int (vec_assign_second.size()) << '\n';
	std::cout << "Size of vec_assign_third: " << int (vec_assign_third.size()) << '\n';

	std::cout << "===================== assign test end ================" << std::endl;

	std::cout << "===================== pop_back test ==================" << std::endl;

	TEST_NS::vector<int> vec_pop_back;
	int sum (0);
	vec_pop_back.push_back (100);
	vec_pop_back.push_back (200);
	vec_pop_back.push_back (300);

	while (!vec_pop_back.empty())
	{
		sum+=vec_pop_back.back();
		vec_pop_back.pop_back();
	}

	std::cout << "The elements of vec_pop_back add up to " << sum << '\n';

	std::cout << "===================== pop_back test end =============" << std::endl;

	std::cout << "===================== operator[] test =============" << std::endl;

  	TEST_NS::vector<int> vec_operator1 (10);   // 10 zero-initialized elements

	TEST_NS::vector<int>::size_type size_operator1 = vec_operator1.size();

	// assign some values:
	for (unsigned i=0; i<size_operator1; i++) vec_operator1[i]=i;

	// reverse vector using operator[]:
	for (unsigned i=0; i<size_operator1/2; i++)
	{
		int temp;
		temp = vec_operator1[size_operator1-1-i];
		vec_operator1[size_operator1-1-i]=vec_operator1[i];
		vec_operator1[i]=temp;
	}

	std::cout << "vec_operator1 contains:";
	for (unsigned i=0; i<size_operator1; i++)
		std::cout << ' ' << vec_operator1[i];
	std::cout << '\n';

	std::cout << "===================== operator[] test end =========" << std::endl;


	std::cout << "===================== front test ==================" << std::endl;

	TEST_NS::vector<int> vec_front1;
	//std::vector<int> vec_front2;

	vec_front1.push_back(78);
	vec_front1.push_back(16);

	//std::cout << vec_front1.at(5) << std::endl;

	//std::cout << vec_front2.front() << std::endl;
	// now front equals 78, and back 16

	vec_front1.front() -= vec_front1.back();

	std::cout << "vec_front1.front() is now " << vec_front1.front() << '\n';


	std::cout << "===================== front test end ==============" << std::endl;

	std::cout << "===================== back test ==================" << std::endl;
	TEST_NS::vector<int> vec_back1;

	vec_back1.push_back(10);

	while (vec_back1.back() != 0)
	{
		vec_back1.push_back ( vec_back1.back() -1 );
	}

	std::cout << "vec_back1 contains:";
	for (unsigned i=0; i<vec_back1.size() ; i++)
		std::cout << ' ' << vec_back1[i];
	std::cout << '\n';
	std::cout << "===================== back test end ==============" << std::endl;


	std::cout << "===================== erase test ==================" << std::endl;

	TEST_NS::vector<int> vec_erase1;

	// set some values (from 1 to 10)
	for (int i=1; i<=10; i++) vec_erase1.push_back(i);

	// erase the 6th element
	vec_erase1.erase (vec_erase1.begin()+5);

	// erase the first 3 elements:
	vec_erase1.erase (vec_erase1.begin(),vec_erase1.begin()+3);

	std::cout << "vec_erase1 contains:";
	for (unsigned i=0; i<vec_erase1.size(); ++i)
		std::cout << ' ' << vec_erase1[i];
	std::cout << '\n';

	std::cout << "===================== erase test end ==============" << std::endl;

	std::cout << "===================== swap test ===================" << std::endl;

	TEST_NS::vector<int> foo (3,100);	 // three ints with a value of 100
	TEST_NS::vector<int> bar (5,200);	 // five ints with a value of 200

	foo.swap(bar);

	std::cout << "foo contains:";
	for (unsigned i=0; i<foo.size(); i++)
		std::cout << ' ' << foo[i];
	std::cout << '\n';

	std::cout << "bar contains:";
	for (unsigned i=0; i<bar.size(); i++)
		std::cout << ' ' << bar[i];
	std::cout << '\n';

	std::cout << "===================== swap test end ===============" << std::endl;

	std::cout << "===================== resize test ===================" << std::endl;

	TEST_NS::vector<int> vec_resize1;

	// set some initial content:
	for (int i=1;i<10;i++) vec_resize1.push_back(i);

	std::cout << vec_resize1.size() << std::endl;

	vec_resize1.resize(5);
	std::cout << vec_resize1.size() << std::endl;

	vec_resize1.resize(8,100);
	vec_resize1.resize(12);

	std::cout << "vec_resize1 contains:";
	for (int i=0;i<(int)vec_resize1.size();i++)
		std::cout << ' ' << vec_resize1[i];
	std::cout << '\n';

	std::cout << "===================== resize test end ===============" << std::endl;

	std::cout << "===================== resize test end ===============" << std::endl;

	std::cout << "===================== copy constructor test ====================" << std::endl;

	// TEST_NS::vector<int> vec_co(5);
	// vec_co.push_back(55);
	// vec_co.push_back(55);
	// vec_co.push_back(55);
	// vec_co.push_back(55);
	// vec_co.push_back(55);

	// TEST_NS::vector<int> vec_co_copy(vec_co);

	// for (TEST_NS::vector<int>::iterator iter = vec_co_copy.begin(); iter != vec_co_copy.end(); iter++)
	// 	std::cout << *iter << " ";
	// std::cout << std::endl;

	// TEST_NS::vector<int> vec_co_oper = vec_co;

	// for (TEST_NS::vector<int>::iterator iter = vec_co_oper.begin(); iter != vec_co_oper.end(); iter++)
	// 	std::cout << *iter << " ";
	// std::cout << std::endl;


	// TEST_NS::vector<TESTED_TYPE> vec_copy(5);
	// TEST_NS::vector<TESTED_TYPE>::iterator iter_copy = vec_copy.begin(), iter_copy_end = vec_copy.end();

	// std::cout << "len: " << (iter_copy_end - iter_copy) << std::endl;
	// for (; iter_copy != iter_copy_end; ++iter_copy)
	// 	*iter_copy = (iter_copy_end - iter_copy);

	// iter_copy = vec_copy.begin();
	// TEST_NS::vector<TESTED_TYPE> vec_copy_range(iter_copy, --(--iter_copy_end));
	// for (int i = 0; iter_copy != iter_copy_end; ++iter_copy)
	// 	*iter_copy = ++i * 5;

	// iter_copy = vec_copy.begin();
	// TEST_NS::vector<TESTED_TYPE> vec_copy_copy(vec_copy);
	// for (int i = 0; iter_copy != iter_copy_end; ++iter_copy)
	// 	*iter_copy = ++i * 7;
	// vec_copy_copy.push_back(42);
	// vec_copy_copy.push_back(21);

	// std::cout << "\t-- PART ONE --" << std::endl;
	// printSize(vec_copy);
	// printSize(vec_copy_range);
	// printSize(vec_copy_copy);

	// std::cout << "========================" << std::endl;
	// vec_copy = vec_copy_copy;
	// vec_copy_copy = vec_copy_range;
	// vec_copy_range.clear();

	// std::cout << "\t-- PART TWO --" << std::endl;
	// printSize(vec_copy);
	// printSize(vec_copy_range);
	// printSize(vec_copy_copy);


	std::cout << "===================== copy constructor test end =================" << std::endl;

	std::cout << "===================== erase test ====================" << std::endl;
	TEST_NS::vector<TESTED_TYPE> vec_erase(10);

	for (unsigned long int i = 0; i < vec_erase.size(); ++i)
		vec_erase[i] = std::string((vec_erase.size() - i), i + 65);
	printSize(vec_erase);

	checkErase(vec_erase, vec_erase.erase(vec_erase.begin() + 2));

	checkErase(vec_erase, vec_erase.erase(vec_erase.begin()));
	checkErase(vec_erase, vec_erase.erase(vec_erase.end() - 1));

	checkErase(vec_erase, vec_erase.erase(vec_erase.begin(), vec_erase.begin() + 3));
	checkErase(vec_erase, vec_erase.erase(vec_erase.end() - 3, vec_erase.end() - 1));

	vec_erase.push_back("Hello");
	vec_erase.push_back("Hi there");
	printSize(vec_erase);
	checkErase(vec_erase, vec_erase.erase(vec_erase.end() - 3, vec_erase.end()));

	vec_erase.push_back("ONE");
	vec_erase.push_back("TWO");
	vec_erase.push_back("THREE");
	vec_erase.push_back("FOUR");
	printSize(vec_erase);
	checkErase(vec_erase, vec_erase.erase(vec_erase.begin(), vec_erase.end()));

	std::cout << "===================== erase test end ================" << std::endl;


	std::cout << "===================== expand arr test ===============" << std::endl;

	TEST_NS::vector<int> vec_expand;
	vec_expand.push_back(1);

	for (int i=0; i<100; i++)
		vec_expand.push_back(i);

	for (TEST_NS::vector<int>::iterator iter_expand = vec_expand.begin(); iter_expand != vec_expand.end(); iter_expand++)
		std::cout << *iter_expand << " ";
	std::cout << std::endl;

	std::cout << "===================== expand arr test end ===========" << std::endl;



	if (LEAK_TEST != 0)
		system("leaks vector | grep leaked 1>&2 ");
	return 0;
}