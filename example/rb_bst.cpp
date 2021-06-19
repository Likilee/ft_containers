#include <iostream>

// 1. 루트(root) 노드는 블랙이다.
// 2. 노드 색은 레드 아니면 블랙이다.
// 3. 모든 외부 노드(External Node)는 블랙이다.
// 4. 모든 외부 노드의 경우 루트(root)부터 외부 노드까지 방문하는 블랙 노드의 수가 같다.
// 5. 레드 노드는 두 개가 연속해서 등장할 수 없다.
namespace ft
{
enum Color
{
	RED,
	BLACK
};

template <typename T>
class rb_node
{
public:
	T *key;
	rb_node *left;
	rb_node *right;
	rb_node *parent;
	Color color;

	rb_node() : key(NULL), left(NULL), right(NULL), parent(NULL), color(RED) {};
	rb_node(const T& val) : left(NULL), right(NULL), parent(NULL), color(RED)
	{
		this->key = new T(val);
	}
	~rb_node()
	{
		delete key;
	}

	T& getData()
	{
		return (*this->key);
	}

	T& getColor()
	{
		return (this->color);
	}

	rb_node *getLeft()
	{
		return (this->left);
	}
	rb_node *getRight()
	{
		return (this->right);
	}
	rb_node *getParent()
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
	if (root->color == RED)
    	std::cout <<"\033[0;31m" << "[" << *root->key << "]" << std::endl;
	if (root->color == BLACK)
    	std::cout <<"\033[0;34m" << "[" << *root->key << "]" << std::endl;
	std::cout << "\033[0;37m";
    if (prev) {
        prev->str = prev_str;
    }
    trunk->str = "   |";
    printTree(root->left, trunk, false);
}

template <typename T>
class rbtree
{
public:
	typedef T key_type;
	typedef rb_node<T> rb_node;
private:
	rb_node *root;

	bool empty()
	{
		return (this->root == NULL);
	}

	void erase_leaf_node(rb_node* target)
	{
		if (target->is_root())
			this->root = NULL;
		else if (target->is_left())
			target->parent->left = NULL;
		else
			target->parent->right = NULL;
	}

	void erase_has_one_child_node(rb_node* target)
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

	void erase_has_two_child_node(rb_node* target)
	{
		rb_node *node = get_left_biggest_node(target->left);
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
	rbtree() : root(NULL) {}
	~rbtree() { this->clear(); } // root 바닥부터 싹 지워주는거 만들어야함.(재귀로 짜면될 듯)

	rb_node *getRoot()
	{
		return (this->root);
	}
	rb_node *search(const T& key)
	{
		return (search(this->root, key));
	}

	rb_node *search(rb_node *node, const T& key)
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
		if (this->empty())
		{
			this->root = new rb_node(key);
			return ;
		}

		//트리를 루트 노드부터 key값과 비교하며 같은게 있는지 찾는다.
		rb_node *current = this->root;
		rb_node *parent = NULL;
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
			else
				current = current->right;
		}
		// wile문을 빠져나왔으면 = 트리에 키가 존재하지 않음 아래 실행
		current = new rb_node(key);
		current->parent = parent;
		if (parent->getData() > key)
			parent->left = current;
		else
			parent->right = current;
	}

	rb_node *get_left_biggest_node(rb_node *left)
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
		rb_node *target;
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

	void clear(rb_node *node)
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
		rb_node* curr = this->root;
		rb_node* prev = NULL;
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
	ft::rbtree<int> rbtree;
	//Insert test
	std::cout << "*====== INSERT TEST ======*" << std::endl;

	for (int i = 0; i < 30; ++i)
		rbtree.insert(rand() % 15);
	rbtree.print();
	std::cout << std::endl; //end Insert test

	//Erase test
	std::cout << "*====== ERASE TEST ======*" << std::endl;
	for (int i = 0; i < 30; ++i)
	{
		rbtree.erase(rand() % 15);
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
	// rbtree.print();

	return (0);
}