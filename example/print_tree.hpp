#ifndef PRINT_TREE_HPP
# define PRINT_TREE_HPP

# include <iostream>
# include "rbnode.hpp"

namespace ft
{
	struct Trunk
	{
		Trunk *prev;
		std::string str;

		Trunk(Trunk *prev, std::string str)
		{
			this->prev = prev;
			this->str = str;
		}
	};

	// Helper function to print branches of the binary rbtree
	void showTrunks(Trunk *p)
	{
		if (p == NULL) {
			return;
		}

		showTrunks(p->prev);
		std::cout << p->str;
	}

	template<typename T>
	void printTree(rb_node<T>* root, Trunk *prev, bool isLeft)
	{
		if (root->empty()) {
			return;
		}
		std::string prev_str = "    ";
		Trunk *trunk = new Trunk(prev, prev_str);

		printTree(root->right, trunk, true);

		if (!prev) {
			trunk->str = "———";
		}
		else if (isLeft)
		{
			trunk->str = ",———";
			prev_str = "   |";
		}
		else {
			trunk->str = "`———";
			prev->str = prev_str;
		}

		showTrunks(trunk);
		if (root->color == RED)
			std::cout <<"\033[0;31m" << "[" << *root->value << "]" << std::endl;
		if (root->color == BLACK)
			std::cout <<"\033[0;34m" << "[" << *root->value << "]" << std::endl;
		std::cout << "\033[0;37m";
		if (prev) {
			prev->str = prev_str;
		}
		trunk->str = "   |";
		printTree(root->left, trunk, false);
	}
} // namespace ft


#endif