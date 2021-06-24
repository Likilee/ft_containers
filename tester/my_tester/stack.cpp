#include "stack.hpp"
#include <stack>
#include <iostream>
#include <string>

#ifndef LEAK_TEST
# define LEAK_TEST 1
#endif

#ifndef TEST_NS
# define TEST_NS ft
#endif

int			main()
{
	std::cout << "==================== empty test start ===================" << std::endl;

	TEST_NS::stack<int> stack_empty;
	int sum (0);

	for (int i=1;i<=10;i++) stack_empty.push(i);

	while (!stack_empty.empty())
	{
		 sum += stack_empty.top();
		 stack_empty.pop();
	}

	std::cout << "total: " << sum << '\n';

	std::cout << "==================== empty test end ===================" << std::endl;

	std::cout << "==================== size test start ===================" << std::endl;

	TEST_NS::stack<int> stack_size;
	std::cout << "0. size: " << stack_size.size() << '\n';

	for (int i=0; i<5; i++) stack_size.push(i);
	std::cout << "1. size: " << stack_size.size() << '\n';

	stack_size.pop();
	std::cout << "2. size: " << stack_size.size() << '\n';

	std::cout << "==================== size test end =====================" << std::endl;

	std::cout << "==================== top test start =====================" << std::endl;

	TEST_NS::stack<int> stack_top;

	stack_top.push(10);
	stack_top.push(20);

	stack_top.top() -= 5;

	std::cout << "stack_top.top() is now " << stack_top.top() << '\n';

	std::cout << "==================== top test end =======================" << std::endl;

	std::cout << "==================== push pop test start =====================" << std::endl;

	std::stack<int> stack_push;

	for (int i=0; i<5; ++i) stack_push.push(i);

	std::cout << "Popping out elements...";
	while (!stack_push.empty())
	{
		 std::cout << ' ' << stack_push.top();
		 stack_push.pop();
	}
	std::cout << '\n';

	std::cout << "==================== push pop test end =======================" << std::endl;

	if (LEAK_TEST != 0)
		system("leaks stack | grep leaked 1>&2 ");



}