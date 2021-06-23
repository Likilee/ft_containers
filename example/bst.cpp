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
	T& getValue()
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
			std::cout << "is_left Error: target :" << this->getValue() << std::endl;
		if (this->parent->left == this)
			return (true);
		else
			return (false);
	}

	bool is_right()
	{
		if (this->parent == NULL)
			std::cout << "is_right Error: target :" << this->getValue() << std::endl;
		if (this->parent->right == this)
			return (true);
		else
			return (false);
	}

	bool is_leaf()
	{
		if (this->left == NULL && this->right == NULL)
			return (true);
		return (false);
	}

	bool has_one_child()
	{
		if (!is_leaf() && (this->left == NULL || this->right == NULL))
			return (true);
		return (false);
	}

	bool has_two_child()
	{
		if (this->left != NULL && this->right != NULL)
			return (true);
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

	bool empty()
	{
		return (this->root == NULL);
	}

	void erase_leaf_node(tree_node* target)
	{
		if (target->is_root())
			this->root = NULL;
		else if (target->is_left())
			target->parent->left = NULL;
		else
			target->parent->right = NULL;
	}

	void erase_has_one_child_node(tree_node* target)
	{
		if (target->left == NULL) // 오른쪽 자식이 있음
		{
			if (target->is_root())
				this->root = target->right;
			else if (target->is_left())
				target->parent->left = target->right;
			else
				target->parent->right = target->right;
			target->right->parent = target->parent;
		}
		else // 왼쪽 자식이 있음
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

	void erase_has_two_child_node(tree_node* target)
	{
		tree_node *node = get_left_biggest_node(target->left);
		if (node->parent == target) // node가 타겟의 바로 왼쪽노드이다.
		{
			// target의 오른쪽 브랜치를 node 로 가져온다.
			node->right = target->right;
			target->right->parent = node;
			if (target->is_root()) // target이 root 이면 node를 root로 세팅
			{
				this->root = node;
				node->parent = NULL;
			}
			else
			{
				if (target->is_left()) // target이 left 였으면 target의 부모의 왼쪽 브랜치와 node를 연결
					target->parent->left = node;
				else
					target->parent->right = node;
				node->parent = target->parent;
			}
		}
		else //노드가 타겟에서 2depth 이상 떨어져 있다.
		{
			//step1. 노드의 부모와 노드의 자식을 연결해준다 (노드가 원래 위치에서 빠져나온다. )
			node->parent->right = node->left;
			if (node->left != NULL)
				node->left->parent = node->parent;
			//노드를 타겟 자리로 옮긴다.
			node->parent = target->parent;
			node->right = target->right;
			target->right->parent = node;
			node->left = target->left;
			target->left->parent = node;
			//타겟의 부모의 브랜치에 node를 연결한다.
			if (target->is_root()) // target이 root 이면
				this->root = node;
			else if (target->is_left())
				target->parent->left = node;
			else
				target->parent->right = node;
		}
	}

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
		else if (node->getValue() == key)
		{
			// std::cout << "Success search" << std::endl;
			return (node);
		}
		else if (node->getValue() < key)
			return (search(node->getRight(), key));
		else //if (node->getValue() > key)
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
		if (this->empty())
			this->root = new tree_node(key);

		//트리를 루트 노드부터 key값과 비교하며 같은게 있는지 찾는다.
		tree_node *current = this->root;
		tree_node *parent = NULL;
		while (current != NULL)
		{
			parent = current;
			if (current->getValue() == key)
			{
				std::cout << "Key is already in" << std::endl;
				return ;
			}
			else if (current->getValue() > key)
				current = current->left;
			else
				current = current->right;
		}
		// wile문을 빠져나왔으면 = 트리에 키가 존재하지 않음 아래 실행
		current = new tree_node(key);
		current->parent = parent;
		if (parent->getValue() > key)
			parent->left = current;
		else
			parent->right = current;
	}

	tree_node *get_left_biggest_node(tree_node *left)
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
		//트리에 key가 없으면 아무 것도 안함.
		tree_node *target;
		if (NULL == (target = this->search(key)))
			return ;
		//비어 있지 않다면 해당 키값의 노드를 찾음.
		if (target->is_leaf()) // case1 -자식이 없는 리프노드
			erase_leaf_node(target);
		else if (target->has_one_child()) // case2 - 자식이 하나인 노드
			erase_has_one_child_node(target);
		else // case 3 - 자식이 둘인 노드
			erase_has_two_child_node(target);
		delete (target);
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
		delete (node);
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
	std::cout << "CLEAR" << std::endl;
	tree.print();
}