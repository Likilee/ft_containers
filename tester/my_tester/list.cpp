#include "list.hpp"
#include <list>
#include <vector>
#include <iterator>
#include <string>
#include <iostream>
#include <stdlib.h>

#ifndef TEST_NS
# define TEST_NS ft
#endif

#ifndef LEAK_TEST
# define LEAK_TEST 1
#endif

#define TESTED_TYPE int

class test
{
	public:
		int x;
		int y;
		test()
		{

		}
		test(int x, int y)
		{
			this->x = x;
			this->y = y;
		}
		~test()
		{
			//std::cout << "test class deleted :(" << std::endl;
		}
};


template <typename T>
void	printSize(TEST_NS::list<T> const &lst, bool print_content = 1)
{
	std::cout << "size: " << lst.size() << std::endl;
	std::cout << "max_size: " << lst.max_size() << std::endl;
	if (print_content)
	{
		typename TEST_NS::list<T>::const_iterator it = lst.begin(), ite = lst.end();
		std::cout << std::endl << "Content is:" << std::endl;
		for (; it != ite; ++it)
			std::cout << "- " << *it << std::endl;
	}
	std::cout << "###############################################" << std::endl;
}

void	checkErase(TEST_NS::list<TESTED_TYPE> const &lst,
					TEST_NS::list<TESTED_TYPE>::const_iterator const &it)
{
	static int i = 0;

	int j = 0;
	TEST_NS::list<TESTED_TYPE>::const_iterator ite = lst.begin();
	while (it != ite--)
		++j;

	std::cout << "[" << i++ << "] " << "erase: " << j << std::endl;
	printSize(lst);
}


bool single_digit (const int& value) { return (value<10); }

// a predicate implemented as a class:
struct is_odd {
  bool operator() (const int& value) { return (value%2)==1; }
};

bool same_integral_part (double first, double second)
{ return ( int(first)==int(second) ); }

// a binary predicate implemented as a class:
struct is_near {
  bool operator() (double first, double second)
  { return (fabs(first-second)<5.0); }
};

bool compare_nocase (const std::string& first, const std::string& second)
{
  unsigned int i=0;
  while ( (i<first.length()) && (i<second.length()) )
  {
    if (tolower(first[i])<tolower(second[i])) return true;
    else if (tolower(first[i])>tolower(second[i])) return false;
    ++i;
  }
  return ( first.length() < second.length() );
}

bool mycomparison (double first, double second)
{ return ( int(first)<int(second) ); }

int			main()
{
	std::cout << "=========================== push_back test ============================" << std::endl;


	TEST_NS::list<int> list_push_back1;

	list_push_back1.push_back(1);
	list_push_back1.push_back(2);
	list_push_back1.push_back(3);
	list_push_back1.push_back(4);
	list_push_back1.push_back(5);

	for (TEST_NS::list<int>::iterator iter = list_push_back1.begin(); iter != list_push_back1.end(); iter++)
		std::cout << *iter << " ";
	std::cout << std::endl;
	std::cout << "list_push_back1 stores " << list_push_back1.size() << " numbers.\n";


	TEST_NS::list<test> list_push_back2;

	list_push_back2.push_back(test(3,5));
	list_push_back2.push_back(test(1,22));
	list_push_back2.push_back(test(2,33));
	list_push_back2.push_back(test(5,511));

	// std::cout << "=============" << std::endl;

	list_push_back2.clear();

	for (TEST_NS::list<test>::iterator iter = list_push_back2.begin(); iter != list_push_back2.end(); iter++)
		std::cout << iter->x << ", " << iter->y << " || ";
	std::cout << std::endl;

	std::cout << "list_push_back2 stores " << list_push_back2.size() << " numbers.\n";

	list_push_back2.push_back(test(3,5));
	list_push_back2.push_back(test(2,33));
	list_push_back2.push_back(test(5,511));

	for (TEST_NS::list<test>::iterator iter = list_push_back2.begin(); iter != list_push_back2.end(); iter++)
		std::cout << iter->x << ", " << iter->y << " || ";
	std::cout << std::endl;

	std::cout << "list_push_back2 stores " << list_push_back2.size() << " numbers.\n";


	std::cout << "=========================== push_back test end=========================" << std::endl;


	std::cout << "=========================== push_front test ===========================" << std::endl;

	TEST_NS::list<int> list_push_front1 (2,100);         // two ints with a value of 100
	list_push_front1.push_front (200);
	list_push_front1.push_front (300);

	std::cout << "mylist contains:";
	for (TEST_NS::list<int>::iterator it=list_push_front1.begin(); it!=list_push_front1.end(); ++it)
	  std::cout << ' ' << *it;

  	std::cout << '\n';

	std::cout << "list_push_front1 stores " << list_push_front1.size() << " numbers.\n";

	std::cout << "=========================== push_front test end========================" << std::endl;


	std::cout << "=========================== insert test ========================" << std::endl;

	TEST_NS::list<int> list_insert_test;
	TEST_NS::list<int>::iterator it_insert_test;

  // set some initial values:
	for (int i=1; i<=5; ++i) list_insert_test.push_back(i); // 1 2 3 4 5

	it_insert_test = list_insert_test.begin();
	++it_insert_test;       // it points now to number 2           ^

	list_insert_test.insert (it_insert_test,10);                        // 1 10 2 3 4 5

  // "it" still points to number 2                      ^
	list_insert_test.insert (it_insert_test,2,20);                      // 1 10 20 20 2 3 4 5

	--it_insert_test;       // it points now to the second 20            ^

	std::vector<int> vector_insert_test (2,30);
	list_insert_test.insert (it_insert_test,vector_insert_test.begin(),vector_insert_test.end());
                                                // 1 10 20 30 30 20 2 3 4 5
                                                //               ^



	it_insert_test = list_insert_test.begin();
	it_insert_test++;
	it_insert_test = list_insert_test.insert(it_insert_test, 778);
	std::cout << * it_insert_test << std::endl;


	std::cout << "mylist contains:";
	for (it_insert_test=list_insert_test.begin(); it_insert_test!=list_insert_test.end(); ++it_insert_test)
		std::cout << ' ' << *it_insert_test;
	std::cout << '\n';

	std::cout << "=========================== insert test end=====================" << std::endl;

	std::cout << "=========================== resize test ========================" << std::endl;

	TEST_NS::list<int> list_resize_test;

	// set some initial content:
	for (int i=1; i<10; ++i) list_resize_test.push_back(i);

	list_resize_test.resize(5);
	list_resize_test.resize(8,100);
	list_resize_test.resize(12);

  	std::cout << "list_resize_test contains:";
  	for (TEST_NS::list<int>::iterator it=list_resize_test.begin(); it!=list_resize_test.end(); ++it)
   	std::cout << ' ' << *it;

 	std::cout << '\n';

	std::cout << "=========================== resize test end=====================" << std::endl;

	std::cout << "=========================== splice test ========================" << std::endl;

	TEST_NS::list<int> list_splice_test1;

	list_splice_test1.push_back(2);
	list_splice_test1.push_back(3);
	list_splice_test1.push_back(4);

	TEST_NS::list<int>::iterator iter_splice_test1 = list_splice_test1.begin();
	iter_splice_test1++;

	TEST_NS::list<int> list_splice_test2;

	list_splice_test2.push_back(22);
	list_splice_test2.push_back(23);
	list_splice_test2.push_back(24);

	TEST_NS::list<int>::iterator iter_splice_test2 = list_splice_test2.begin();
	iter_splice_test2++;

	list_splice_test1.splice(iter_splice_test1, list_splice_test2, list_splice_test2.begin(), iter_splice_test2);

	list_splice_test1.insert(iter_splice_test1, 5);

	std::cout << "size : " <<list_splice_test1.size() << std::endl;



	for(TEST_NS::list<int>::iterator iter = list_splice_test1.begin(); iter != list_splice_test1.end(); iter++)
		std::cout << *iter << " ";
	std::cout << std::endl;


	TEST_NS::list<int> list_splice_test3, list_splice_test4;
	TEST_NS::list<int>::iterator iter_splice_test3;

  // set some initial values:
	for (int i=1; i<=4; ++i)
	   list_splice_test3.push_back(i);      // list_splice_test3: 1 2 3 4
	for (int i=1; i<=3; ++i)
	   list_splice_test4.push_back(i*10);   // list_splice_test4: 10 20 30

	iter_splice_test3 = list_splice_test3.begin();
	++iter_splice_test3;                         // points to 2
	list_splice_test3.splice (iter_splice_test3, list_splice_test4); // list_splice_test3: 1 10 20 30 2 3 4
	                              // list_splice_test4 (empty)
	                              // "it" still points to 2 (the 5th element)

	list_splice_test4.splice (list_splice_test4.begin(),list_splice_test3, iter_splice_test3);
	                              // list_splice_test3: 1 10 20 30 3 4
	                              // list_splice_test4: 2
	                              // "it" is now invalid.
	iter_splice_test3 = list_splice_test3.begin();

	iter_splice_test3++;
	iter_splice_test3++;
	iter_splice_test3++;       // "it" points now to 30
	list_splice_test3.splice ( list_splice_test3.begin(), list_splice_test3, iter_splice_test3, list_splice_test3.end());
	                              // list_splice_test3: 30 3 4 1 10 20
	std::cout << "list_splice_test3 contains:";
	for (iter_splice_test3=list_splice_test3.begin(); iter_splice_test3!=list_splice_test3.end(); ++iter_splice_test3)
	  std::cout << ' ' << *iter_splice_test3;
	std::cout << '\n';
	std::cout << "list_splice_test4 contains:";
	for (iter_splice_test3=list_splice_test4.begin(); iter_splice_test3!=list_splice_test4.end(); ++iter_splice_test3)
	  std::cout << ' ' << *iter_splice_test3;
	std::cout << '\n';

	std::cout << "=========================== splice test end=====================" << std::endl;


	std::cout << "=========================== remove test start =====================" << std::endl;


	int myints_remove[]= {17,89,7,14};
	TEST_NS::list<int> list_remove1(myints_remove,myints_remove+4);

	list_remove1.push_back(89);

	std::cout << "mylist contains:";
	for (TEST_NS::list<int>::iterator it=list_remove1.begin(); it!=list_remove1.end(); ++it)
		std::cout << ' ' << *it;
	std::cout << '\n';


	list_remove1.remove(89);

	std::cout << "mylist contains:";
	for (TEST_NS::list<int>::iterator it=list_remove1.begin(); it!=list_remove1.end(); ++it)
		std::cout << ' ' << *it;
	std::cout << '\n';

	std::cout << "=========================== remove test end=====================" << std::endl;


	std::cout << "=========================== remove if test start =======================" << std::endl;


	int myints_remove_if[]= {15,36,7,17,20,39,4,1};
	TEST_NS::list<int> list_remove_if1 (myints_remove_if,myints_remove_if+8);   // 15 36 7 17 20 39 4 1

	list_remove_if1.remove_if (single_digit);           // 15 36 17 20 39

	list_remove_if1.remove_if (is_odd());               // 36 20

	std::cout << "mylist contains:";
	for (TEST_NS::list<int>::iterator it=list_remove_if1.begin(); it!=list_remove_if1.end(); ++it)
		std::cout << ' ' << *it;
	std::cout << '\n';

	std::cout << "=========================== remove if test end =======================" << std::endl;


	std::cout << "=========================== unique test start =======================" << std::endl;

	double mydoubles_unique[]={ 12.15,  2.72, 73.0,  12.77,  3.14,
                       12.77, 73.35, 72.25, 15.3,  72.25 };
	TEST_NS::list<double> list_unique1 (mydoubles_unique,mydoubles_unique+10);

	list_unique1.sort();             //  2.72,  3.14, 12.15, 12.77, 12.77,
                             // 15.3,  72.25, 72.25, 73.0,  73.35

	list_unique1.unique();
	for (TEST_NS::list<double>::iterator iter = list_unique1.begin(); iter != list_unique1.end(); iter ++)
		std::cout << *iter << " ";
	std::cout << std::endl;




	list_unique1.unique (same_integral_part);  //  2.72,  3.14, 12.15
                                       // 15.3,  72.25, 73.0
	for (TEST_NS::list<double>::iterator iter = list_unique1.begin(); iter != list_unique1.end(); iter ++)
		std::cout << *iter << " ";
	std::cout << std::endl;

	list_unique1.unique (is_near());           //  2.72, 12.15, 72.25
	for (TEST_NS::list<double>::iterator iter = list_unique1.begin(); iter != list_unique1.end(); iter ++)
		std::cout << *iter << " ";
	std::cout << std::endl;
	std::cout << "=========================== unique test end =========================" << std::endl;

	std::cout << "=========================== sort test start =========================" << std::endl;

	TEST_NS::list<std::string> list_sort1;
	TEST_NS::list<std::string>::iterator iter_sort1;
	list_sort1.push_back ("one");
	list_sort1.push_back ("two");
	list_sort1.push_back ("Three");

	list_sort1.sort();

  	std::cout << "mylist contains:";
	for (iter_sort1=list_sort1.begin(); iter_sort1!=list_sort1.end(); ++iter_sort1)
		std::cout << ' ' << *iter_sort1;
	std::cout << '\n';

	list_sort1.sort(compare_nocase);

	std::cout << "mylist contains:";
	for (iter_sort1=list_sort1.begin(); iter_sort1!=list_sort1.end(); ++iter_sort1)
		std::cout << ' ' << *iter_sort1;
	std::cout << '\n';


	std::cout << "=========================== sort test end ============================" << std::endl;

	std::cout << "=========================== merge test start ============================" << std::endl;

	TEST_NS::list<double> list_merge_first, list_merge_second;

	list_merge_first.push_back (3.1);
	list_merge_first.push_back (2.2);
	list_merge_first.push_back (2.9);

	list_merge_second.push_back (3.7);
	list_merge_second.push_back (7.1);
	list_merge_second.push_back (1.4);

	list_merge_first.sort();
	list_merge_second.sort();

	list_merge_first.merge(list_merge_second);

  	// (second is now empty)

	list_merge_second.push_back (2.1);

	list_merge_first.merge(list_merge_second,mycomparison);

  	std::cout << "first contains:";
  	for (TEST_NS::list<double>::iterator it=list_merge_first.begin(); it!=list_merge_first.end(); ++it)
    	std::cout << ' ' << *it;
  	std::cout << '\n';

	std::cout << list_merge_first.size() << std::endl;
	std::cout << list_merge_second.size() << std::endl;

	std::cout << "=========================== merge test end ============================" << std::endl;


	std::cout << "=========================== reverse test start ============================" << std::endl;
  	TEST_NS::list<int> list_reverse;

  	for (int i=1; i<10; ++i) list_reverse.push_back(i);

  	list_reverse.reverse();

  	std::cout << "mylist contains:";
  	for (TEST_NS::list<int>::iterator it=list_reverse.begin(); it!=list_reverse.end(); ++it)
  		std::cout << ' ' << *it;
	std::cout << '\n';

	list_reverse.clear();
  	std::cout << "mylist contains:";
  	for (TEST_NS::list<int>::iterator it=list_reverse.begin(); it!=list_reverse.end(); ++it)
  		std::cout << ' ' << *it;
	std::cout << '\n';

	list_reverse.reverse();
  	std::cout << "mylist contains:";
  	for (TEST_NS::list<int>::iterator it=list_reverse.begin(); it!=list_reverse.end(); ++it)
  		std::cout << ' ' << *it;
	std::cout << '\n';

	list_reverse.push_back(55);
	list_reverse.reverse();
  	std::cout << "mylist contains:";
  	for (TEST_NS::list<int>::iterator it=list_reverse.begin(); it!=list_reverse.end(); ++it)
  		std::cout << ' ' << *it;
	std::cout << '\n';

	list_reverse.push_back(40);
	list_reverse.reverse();
  	std::cout << "mylist contains:";
  	for (TEST_NS::list<int>::iterator it=list_reverse.begin(); it!=list_reverse.end(); ++it)
  		std::cout << ' ' << *it;
	std::cout << '\n';
	std::cout << "=========================== reverse test end ==============================" << std::endl;



	std::cout << "=========================== sort iterator invalid test start ==============================" << std::endl;

	TEST_NS::list<int> list_sort2;

	list_sort2.push_back(3);
	list_sort2.push_back(-99999);
	list_sort2.push_back(2);
	list_sort2.push_back(5);

	TEST_NS::list<int>::iterator iter_sort2 = list_sort2.begin();
	list_sort2.sort();
	for(; iter_sort2 != list_sort2.end(); iter_sort2++)
		std::cout << *iter_sort2 << std::endl;

	std::cout << "=========================== sort iterator invalid test end ==============================" << std::endl;


	if (LEAK_TEST != 0)
		system("leaks list | grep leaked 1>&2");

	return (0);
}