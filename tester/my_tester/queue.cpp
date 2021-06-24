#include "queue.hpp"
#include <queue>

#ifndef LEAK_TEST
# define LEAK_TEST 1
#endif

#ifndef TEST_NS
# define TEST_NS ft

#endif
int		main()
{
	std::cout << "===================== empty test start =====================" << std::endl;

	TEST_NS::queue<int> queue_empty;
	int sum (0);

	for (int i=1;i<=10;i++)
	{
		queue_empty.push(i);
		//std::cout << queue_empty.size() << std::endl;
	}

	while (!queue_empty.empty())
	{
		std::cout << queue_empty.size() << std::endl;
		sum += queue_empty.front();
		queue_empty.pop();
	}

	std::cout << "total: " << sum << '\n';

	std::cout << "===================== empty test end =======================" << std::endl;

	std::cout << "===================== size test start =======================" << std::endl;

	TEST_NS::queue<int> queue_size;
	std::cout << "0. size: " << queue_size.size() << '\n';

	for (int i=0; i<5; i++) queue_size.push(i);
	std::cout << "1. size: " << queue_size.size() << '\n';

	queue_size.pop();
	std::cout << "2. size: " << queue_size.size() << '\n';

	std::cout << "===================== size test end =======================" << std::endl;

	std::cout << "===================== front test start =======================" << std::endl;

	TEST_NS::queue<int> queue_front;

	queue_front.push(77);
	queue_front.push(16);

	queue_front.front() -= queue_front.back();		// 77-16=61

	std::cout << "queue_front.front() is now " << queue_front.front() << '\n';


	std::cout << "===================== front test end =========================" << std::endl;

	std::cout << "===================== back test start =========================" << std::endl;

	TEST_NS::queue<int> queue_back;

	queue_back.push(12);
	queue_back.push(75);	 // this is now the back

	queue_back.back() -= queue_back.front();

	std::cout << "queue_back.back() is now " << queue_back.back() << '\n';

	std::cout << "===================== back test end =========================" << std::endl;

	std::cout << "===================== push and pop test start =======================" << std::endl;

	TEST_NS::queue<int> queue_push;

	for (int i=0; i<10; i++)
		queue_push.push(i * 5);


	while (!queue_push.empty())
	{
		std::cout << ' ' << queue_push.front();
		queue_push.pop();
	}
	std::cout << '\n';


	std::cout << "===================== push and pop test end =========================" << std::endl;

	if (LEAK_TEST != 0)
		system("leaks queue | grep leaked 1>&2 ");


}