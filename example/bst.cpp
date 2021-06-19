#include <iostream>
# define COUNT 8

namespace ft
{
template <typename T>
class tree_node
{
public:
	T *key;
	tree_node *left;
	tree_node *right;
	tree_node *parent;

	tree_node() : key(NULL), left(NULL), right(NULL), parent(NULL) {};
	tree_node(const T& val) : left(NULL), right(NULL), parent(NULL)
	{
		this->key = new T(val);
	}
	~tree_node()
	{
		delete key;
	}
	T& getData()
	{
		return (*this->key);
	}
	tree_node *getLeft()
	{
		return (this->left);
	}
	tree_node *getRight()
	{
		return (this->right);
	}
	tree_node *getParent()
	{
		return (this->parent);
	}
	bool empty()
	{
		if (this->key == NULL)
			return (true);
		return (false);
	}
	bool is_root()
	{
		if (this->parent == NULL)
			return (true);
		return (false);
	}
	bool is_left()
	{
		if (this->parent == NULL)
			std::cout << "is_left Error: target :" << this->getData() << std::endl;
		if (this->parent->left == this)
			return (true);
		else
			return (false);
	}

	bool is_right()
	{
		if (this->parent == NULL)
			std::cout << "is_right Error: target :" << this->getData() << std::endl;
		if (this->parent->right == this)
			return (true);
		else
			return (false);
	}
};

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

// Helper function to print branches of the binary tree
void showTrunks(Trunk *p)
{
    if (p == NULL) {
        return;
    }

    showTrunks(p->prev);
    std::cout << p->str;
}

template<typename T>
void printTree(tree_node<T>* root, Trunk *prev, bool isLeft)
{
    if (root == NULL) {
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
    std::cout << "[" << *root->key << "]" << std::endl;

    if (prev) {
        prev->str = prev_str;
    }
    trunk->str = "   |";
    printTree(root->left, trunk, false);
}

template <typename T>
class tree
{
public:
	typedef T key_type;
	typedef tree_node<T> tree_node;
private:
	tree_node *root;
public:
	tree() : root(NULL) {}
	~tree() { } // root 바닥부터 싹 지워주는거 만들어야함.(재귀로 짜면될 듯)

	tree_node *getRoot()
	{
		return (this->root);
	}
	tree_node *search(const T& key)
	{
		return (search(this->root, key));
	}

	tree_node *search(tree_node *node, const T& key)
	{
		if (node == NULL)
		{
			// std::cout << "Failed search" << std::endl;
			return (NULL);
		}
		else if (node->getData() == key)
		{
			// std::cout << "Success search" << std::endl;
			return (node);
		}
		else if (node->getData() < key)
			return (search(node->getRight(), key));
		else //if (node->getData() > key)
			return (search(node->getLeft(), key));
	}

	void delete_root()
	{
		delete (this->root);
		this->root = NULL;
	}

	void insert(const T& key)
	{
		//빈 트리면, key를 루트노드로 추가한다.
		if (this->root == NULL)
			this->root = new tree_node(key);

		//트리를 루트 노드부터 key값과 비교하며 같은게 있는지 찾는다.
		tree_node *current = this->root;
		tree_node *parent = NULL;
		while (current != NULL)
		{
			parent = current;
			if (current->getData() == key)
			{
				std::cout << "Key is already in" << std::endl;
				return ;
			}
			else if (current->getData() > key)
				current = current->left;
			else //if(current->getData() < key)
				current = current->right;
		}
		// wile문을 빠져나왔으면 = 트리에 키가 존재하지 않음 아래 실행
		current = new tree_node(key);
		current->parent = parent;
		if (parent->getData() > key)
			parent->left = current;
		else
			parent->right = current;
	}

	tree_node *getLeftBiggest(tree_node *left)
	{
		while (left->right != NULL)
			left = left->right;
		return (left);
	}

	// case 1 자식이 없는 리프노드 : 부모노드의 해당 링크를 NULL로
	// case 2 자식이 하나인 노드 : 삭제되는 자리에 하나밖에 없는 그 노드를 위치시키면 됨
	// case 2 자식이 둘인 노드 : 왼쪽 서브트리의 최대 노드를 가져오거나, 오른쪽 서브트리의 최소 노드를 가져온다.
	void erase(const T& key)
	{
		// std::cout << "Try erase : " << key << std::endl;
		tree_node *node = this->root;
		if (node == NULL )//|| node->empty())
			return ;
		tree_node *target = search(key);
		if (target == NULL)
		{
			// std::cout << "No key in tree" << std::endl;
			return ;
		}
		else if (target->left == NULL && target->right == NULL) // case1 -자식이 없는 리프노드
		{
			if (target->is_root())
				this->root = NULL;
			else if (target->is_left())
				target->parent->left = NULL;
			else
				target->parent->right = NULL;
		}
		else if (target->left == NULL || target->right == NULL) // case2 - 자식이 하나인 노드
		{
			if (target->left == NULL)
			{
				if (target->is_root())
					this->root = target->right;
				else if (target->is_left())
					target->parent->left = target->right;
				else
					target->parent->right = target->right;
				target->right->parent = target->parent;
			}
			else
			{
				if (target->is_root())
					this->root = target->left;
				else if (target->is_right())
					target->parent->right = target->left;
				else
					target->parent->left = target->left;
				target->left->parent = target->parent;
			}
		}
		else // case 3 - 자식이 둘인 노드
		{
			node = getLeftBiggest(target->left);
			if (node->parent == target) // left_node의 오른쪽 자식이 아예 없다.
			{
				node->right = target->right;
				target->right->parent = node;
				if (target->is_root()) // target이 root 이면
				{
					this->root = node;
					node->parent = NULL;
				}
				else
				{
					if (target->is_left())
						target->parent->left = node;
					else
						target->parent->right = node;
					node->parent = target->parent;
					target->left = NULL;
					target->right = NULL;
				}
			}
			else
			{
				node->parent->right = node->left;
				if (node->left != NULL)
					node->left->parent = node->parent;
				node->parent = target->parent;
				node->right = target->right;
				target->right->parent = node;
				node->left = target->left;
				target->left->parent = node;
				if (target->is_root()) // target이 root 이면
					this->root = node;
				else if (target->is_left())
				{
					target->parent->left = node;
					node->parent = target->parent;
				}
				else
				{
					target->parent->right = node;
					node->parent = target->parent;
				}
			}
		}
		delete_node(target);
	}

	void delete_node(tree_node *node)
	{
		if (node != NULL)
			delete (node);
	}

	void clear()
	{
		clear(this->root);
	}

	void clear(tree_node *node)
	{
		if (node == NULL)
			return ;
		clear(node->left);
		clear(node->right);
		if (node->is_root())
		{
			delete_root();
			return ;
		}
		else if (node->is_left())
			node->parent->left = NULL;
		else
			node->parent->right = NULL;
		delete_node(node);
	}

	void print()
	{
		ft::printTree(this->root, NULL, false);
	}

	void check_traversal()
	{
		tree_node* curr = this->root;
		tree_node* prev = NULL;
		if (curr == NULL)
			return ;
		while (1)
		{
			if (prev == curr->right)
			{
				prev = curr;
				if (curr->parent != NULL)
					curr = curr->parent;
				else
					return ;
				continue ;
			}
			else if (prev == curr->left)
			{
				prev = curr;
				if (curr->right == NULL)
					curr = curr->parent;
				else
					curr = curr->right;
				continue ;
			}
			if (curr->left != NULL)
			{
				prev = curr;
				curr = curr->left;
				continue ;
			}
			if (curr->right != NULL)
			{
				prev = curr;
				curr = curr->right;
				continue ;
			}
			prev = curr;
			curr = curr->parent;
			continue ;
		}
	}
};
}



int main()
{
	// ft::tree<int> tree;
	// // ft::tree_node<int>* root_pointer = &root;
	// // std::cout << root.getData() << std::endl;
	// // std::cout << root.getRight() << std::endl;
	// tree.insert(32);
	// tree.insert(15);
	// tree.insert(61);
	// tree.insert(7);
	// tree.insert(10);
	// tree.insert(4);
	// tree.insert(9);
	// tree.insert(73);
	// tree.insert(8);
	// tree.insert(27);
	// tree.insert(5);
	// tree.insert(18);
	// tree.insert(16);
	// tree.insert(6);
	// tree.insert(26);
	// tree.insert(16);
	// tree.insert(89);
	// tree.insert(1);
	// tree.insert(3);
	// tree.insert(20);
	// tree.search(3);
	// std::cout << " ===== BEFORE =====" << std::endl;
	// tree.print();
	// int irase = 5;
	// tree.erase(irase); // earser
	// tree.erase(1); // earser
	// tree.erase(20); // earser
	// tree.erase(89); // earser
	// tree.erase(18); // earser
	// std::cout << "\n ===== AFTER erase " << irase << " =====" << std::endl;
	// tree.print();

	// std::cout << " ===== CHAR TREE BEFORE =====" << std::endl;
	// ft::tree<char> tree2;
	// for (int i = 97; i < 125; ++i)
	// 	tree2.insert(i);
	// tree2.print();
	// std::cout << " ===== CHAR TREE CLEAR =====" << std::endl;
	// tree2.clear();
	// tree2.print();

	srand(clock());
	ft::tree<int> tree;
	for (int i = 0; i < 1000; ++i)
		tree.insert(rand() % 500);
	tree.print();

	for (int i = 0; i < 3000; ++i)
	{
		tree.erase(rand() % 500);
		tree.check_traversal();
	}
	tree.print();
	tree.insert(rand() % 500);
	tree.print();
	tree.clear();
	tree.print();
	// tree.print();



}