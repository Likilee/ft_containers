# include "print_tree.hpp"
# include "rbtree.hpp"

int main()
{
	ft::rbtree<int> tree;

	// tree.insert(3);
	// tree.insert(5);
	// tree.insert(8);
	// tree.insert(7);
	// tree.insert(9);
	// tree.insert(10);
	// tree.insert(13);
	// tree.insert(12);
	// tree.insert(11);
	// tree.insert(4);
	// tree.insert(19);
	// tree.print();
	// tree.erase(8);
	// // tree.erase(5);
	// tree.print();
	// tree.clear();


// TESTER
	srand(clock());
	ft::rbtree<int> rbtree;
	//Insert test
	std::cout << "*====== INSERT TEST ======*" << std::endl;

	for (int i = 0; i < 1000; ++i)
		rbtree.insert(rand() % 800);
	rbtree.print();
	std::cout << std::endl; //end Insert test

	//Erase test
	std::cout << "*====== ERASE TEST ======*" << std::endl;
	for (int i = 0; i < 1000; ++i)
	{
		rbtree.erase(rand() % 800);
		// rbtree.print();
		rbtree.check_traversal();
	}
	rbtree.print();
	std::cout << std::endl; //end Erase test

	//Clear test
	std::cout << "*====== CLEAR TEST ======*" << std::endl;
	rbtree.clear();
	rbtree.print();

	std::cout << std::endl; //end Clear test

	//Insert after clear test
	std::cout << "*====== INSERT AFTER CLEAR TEST ======*" << std::endl;
	rbtree.insert(1004);
	rbtree.print();

	return (0);
}
