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

	rb_node() : key(NULL), left(NULL), right(NULL), parent(NULL), color(BLACK) {}; // nil_node
	rb_node(const T& val) : left(NULL), right(NULL), parent(NULL), color(RED)
	{
		this->key = new T(val);
	}
	~rb_node()
	{
		delete key;
	}

	T& getValue()
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
		if (this->parent->empty())
			return (true);
		return (false);
	}

	bool is_left()
	{
		// if (this->parent->empty())
		// 	std::cout << "is_left Error: target :" << this->getValue() << std::endl;
		if (this->parent->left == this)
			return (true);
		else
			return (false);
	}

	bool is_right()
	{
		// if (this->parent->empty())
		// 	std::cout << "is_right Error: target :" << this->getValue() << std::endl;
		if (this->parent->right == this)
			return (true);
		else
			return (false);
	}

	bool is_leaf()
	{
		if (this->left->empty() && this->right->empty())
			return (true);
		return (false);
	}

	bool has_one_child()
	{
		if (!is_leaf() && (this->left->empty() || this->right->empty()))
			return (true);
		return (false);
	}

	bool has_two_child()
	{
		if (!this->left->empty() && !this->right->empty())
			return (true);
		return (false);
	}

	rb_node *sibling()
	{
		if (this == this->parent->left)
			return (this->parent->right);
		else
			return (this->parent->left);
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
	rb_node *nil;

	bool empty()
	{
		return (this->root == this->nil);
	}

	void erase_leaf_node(rb_node* target)
	{
		if (target->is_root())
			this->root = this->nil;
		else if (target->is_left())
			target->parent->left = this->nil;
		else
			target->parent->right = this->nil;
	}

	void erase_has_one_child_node(rb_node* target)
	{
		if (target->left == this->nil) // 오른쪽 자식이 있음
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

	void switch_has_one_child_node(rb_node* parent)
	{
		rb_node *child;

		if (parent->left == this->nil) // 오른쪽 자식이 있음
			child = parent->right;
		else // 왼쪽 자식이 있음
			child = parent->left;
		swap_parent_child(parent, child);
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
				node->parent = this->nil;
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
			if (node->left != this->nil)
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

	void swap_far_node(rb_node *&high, rb_node *&low)
	{
		rb_node *temp_l = high->left;
		rb_node *temp_r = high->right;
		rb_node *temp_p = high->parent;

		//high를 low 위치로 이동
		high->parent = low->parent;
		if (low->is_left())
			low->parent->left = high;
		else
			low->parent->right = high;
		high->left = low->left;
		if (!low->left->empty())
			low->left->parent = high;
		high->right = low->right;
		if (!low->right->empty())
			low->right->parent = high;

		//low를 high 위치로 이동
		low->parent = temp_p;
		if (temp_p->left == high)
			temp_p->left = low;
		else if (temp_p->right == high)
			temp_p->right = low;
		low->left = temp_l;
		if (!temp_l->empty())
			temp_l->parent = low;
		low->right = temp_r;
		if (!temp_r->empty())
			temp_r->parent = low;

		//색 바꾸고
		swap(high->color, low->color);
		//치환한게 루트이면 루트 바꿔주고
		if (low->parent->empty())
			this->root = low;
	}

	void switch_has_two_child_node(rb_node* target)
	{
		rb_node *node = get_left_biggest_node(target->left);

		if (node->parent == target) // node가 타겟의 바로 왼쪽노드이다.
			swap_parent_child(target, node);
		else //노드가 타겟에서 2depth 이상 떨어져 있다.
			swap_far_node(target, node);
	}

	void rotate_left(rb_node *&pt)
	{
		rb_node *pt_right = pt->right;

		pt->right = pt_right->left;
		if (pt->right != this->nil)
			pt->right->parent = pt;

		pt_right->parent = pt->parent;
		if (pt->parent == this->nil)
			this->root = pt_right;
		else if (pt == pt->parent->left)
			pt->parent->left = pt_right;
		else
			pt->parent->right = pt_right;
		pt_right->left = pt;
		pt->parent = pt_right;
	}

	void rotate_right(rb_node *pt)
	{
		rb_node *pt_left = pt->left;

		pt->left = pt_left->right;
		if (pt->left != this->nil)
			pt->left->parent = pt;

		pt_left->parent = pt->parent;
		if (pt->parent == this->nil)
			this->root = pt_left;
		else if (pt == pt->parent->left)
			pt->parent->left = pt_left;
		else
			pt->parent->right = pt_left;

		pt_left->right = pt;
		pt->parent = pt_left;
	}

	void swap(Color &a, Color &b)
	{
		Color temp;
		temp = a;
		a = b;
		b = temp;
	}

	void swap_parent_child(rb_node *&p, rb_node *&c)
	{
		rb_node *temp_p = p->parent;
		rb_node *temp_l = p->left;
		rb_node *temp_r = p->right;
		Color temp_c = p->color;

		if (c->sibling() != this->nil)
			c->sibling()->parent = c;
		if (c->is_left())
			temp_l = p;
		else
			temp_r = p;

		if (p->is_left())
			p->parent->left = c;
		else if (p->is_right())
			p->parent->right = c;
		p->parent = c;
		p->left = c->left;
		if (!p->left->empty())
			p->left->parent = p;
		p->right = c->right;
		if (!p->right->empty())
			p->right->parent = p;

		c->parent = temp_p;
		c->left = temp_l; // 여기가 문제
		c->right = temp_r; // 여기가 문제
		swap(p->color, c->color);
		if (c->parent->empty())
			this->root = c;
	}

public:
	rbtree()
	{
		nil = new rb_node;
		root = nil;
	}
	~rbtree()  // root 바닥부터 싹 지워주는거 만들어야함.(재귀로 짜면될 듯)
	{
		this->clear();
		delete this->nil;
	}

	rb_node *get_root()
	{
		return (this->root);
	}
	rb_node *search(const T& key)
	{
		return (search(this->root, key));
	}

	rb_node *search(rb_node *node, const T& key)
	{
		if (node == this->nil)
		{
			// std::cout << "Failed search" << std::endl;
			return (this->nil);
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
		this->root = this->nil;
	}

	void insert(const T& key)
	{
		//빈 트리면, key를 루트노드로 추가한다.
		if (this->empty())
		{
			this->root = new rb_node(key);
			this->root->parent = this->nil;
			this->root->left = this->nil;
			this->root->right = this->nil;
			this->root->color = BLACK;
			return ;
		}
		//트리를 루트 노드부터 key값과 비교하며 같은게 있는지 찾는다.
		rb_node *current = this->root;
		rb_node *parent = this->nil;
		while (current != this->nil)
		{
			parent = current;
			if (current->getValue() == key)
			{
				// std::cout << "Key is already in" << std::endl;
				return ;
			}
			else if (current->getValue() > key)
				current = current->left;
			else
				current = current->right;
		}
		// wile문을 빠져나왔으면 = 트리에 키가 존재하지 않음 아래 실행
		current = new rb_node(key);
		current->left = this->nil;
		current->right = this->nil;
		current->parent = parent;
		if (parent->getValue() > key)
			parent->left = current;
		else
			parent->right = current;
		// **** 여기부터 RBTREE 기능 추가
// 		Algorithm:
// Let x be the newly inserted node.

// Perform standard BST insertion and make the colour of newly inserted nodes as RED.


// (i) Change the colour of parent and uncle as BLACK.
// (ii) Colour of a grandparent as RED.
// (iii) Change x = x’s grandparent, repeat steps 2 and 3 for new x.
// b) If x’s uncle is BLACK, then there can be four configurations for x, x’s parent (p) and x’s grandparent (g) (This is similar to AVL Tree)
// (i) Left Left Case (p is left child of g and x is left child of p)
// (ii) Left Right Case (p is left child of g and x is the right child of p)
// (iii) Right Right Case (Mirror of case i)
// (iv) Right Left Case (Mirror of case ii)

		//1. If x is the root, change the colour of x as BLACK (Black height of complete tree increases by 1).
		rb_node *parent_pt = this->nil;
		rb_node *grand_parent_pt = this->nil;

		while ((current != this->root) && (current->color != BLACK)
				&& (current->parent->color == RED))
		{
			parent_pt = current->parent;
			grand_parent_pt = current->parent->parent;

			/*  Case : A
				Parent of pt is left child
				of Grand-parent of pt */
			if (parent_pt == grand_parent_pt->left)
			{

				rb_node *uncle_pt = grand_parent_pt->right;

				/* Case : 1
					The uncle of pt is also red
					Only Recoloring required */
				if (uncle_pt != this->nil && uncle_pt->color ==
														RED)
				{
					grand_parent_pt->color = RED;
					parent_pt->color = BLACK;
					uncle_pt->color = BLACK;
					current = grand_parent_pt;
				}
				else
				{
					/* Case : 2
						current is right child of its parent
						Left-rotation required */
					if (current == parent_pt->right)
					{
						this->rotate_left(parent_pt);
						current = parent_pt;
						parent_pt = current->parent;
					}

					/* Case : 3
						current is left child of its parent
						Right-rotation required */
					this->rotate_right(grand_parent_pt);
					swap(parent_pt->color,
								grand_parent_pt->color);
					current = parent_pt;
				}
			}

			/* Case : B
				Parent of current is right child
				of Grand-parent of current */
			else
			{
				rb_node *uncle_pt = grand_parent_pt->left;

				/*  Case : 1
					The uncle of current is also red
					Only Recoloring required */
				if ((uncle_pt != this->nil) && (uncle_pt->color == RED))
				{
					grand_parent_pt->color = RED;
					parent_pt->color = BLACK;
					uncle_pt->color = BLACK;
					current = grand_parent_pt;
				}
				else
				{
					/* Case : 2
						current is left child of its parent
						Right-rotation required */
					if (current == parent_pt->left)
					{
						this->rotate_right(parent_pt);
						current = parent_pt;
						parent_pt = current->parent;
					}

					/* Case : 3
						current is right child of its parent
						Left-rotation required */
					this->rotate_left(grand_parent_pt);
					this->swap(parent_pt->color,
								grand_parent_pt->color);
					current = parent_pt;
				}
			}
		}
		this->root->color = BLACK;
	}

	rb_node *get_left_biggest_node(rb_node *left)
	{
		while (left->right != this->nil)
			left = left->right;
		return (left);
	}

	// case 1 자식이 없는 리프노드 : 부모노드의 해당 링크를 this->nil로
	// case 2 자식이 하나인 노드 : 삭제되는 자리에 하나밖에 없는 그 노드를 위치시키면 됨
	// case 2 자식이 둘인 노드 : 왼쪽 서브트리의 최대 노드를 가져오거나, 오른쪽 서브트리의 최소 노드를 가져온다.
	void erase(const T& key)
	{
		//트리에 key가 없으면 아무 것도 안함.
		rb_node *target;
		if (this->nil == (target = this->search(key)))
			return ;
		//비어 있지 않다면 해당 키값의 노드를 찾음.
		//switch
		if (target->is_leaf()) // case1 -자식이 없는 리프노드
			erase_leaf_node(target); // root 이면 무시하고 종료. 아니면 자기 자리 그대로.
		else if (target->has_one_child()) // case2 - 자식이 하나인 노드
			erase_has_one_child_node(target);
		else // case 3 - 자식이 둘인 노드
			erase_has_two_child_node(target);
		// 여기까지 왔을 때 target의 위치가 바뀌어 있어야함.
		// delete (target); // delete_node()
	}

	//
	void erase_rbt(const T& key)
	{
		// std::cout << "Erase: " << key << std::endl;

		//트리에 key가 없으면 아무 것도 안함.
		rb_node *target;
		if (this->nil == (target = this->search(key)))
			return ;
		//비어 있지 않다면 해당 키값의 노드를 찾음.
		//switch
		if (target->is_leaf()) // case1 -자식이 없는 리프노드
			; // root 이면 무시하고 종료. 아니면 자기 자리 그대로.
		else if (target->has_one_child()) // case2 - 자식이 하나인 노드
			switch_has_one_child_node(target);
		else // case 3 - 자식이 둘인 노드
			switch_has_two_child_node(target);

		// 여기까지 왔을 때 target의 위치가 바뀌어 있어야함.
		delete_node(target);
	}

	void replace_node(rb_node* target, rb_node* child)
	{
		/*
		*앞에서 n의 부모가 NULL이 되는 경우를 delete_case에 오지 않게 미리 처리해주면 된다.
		*/
		child->parent = target->parent;
		if (target->parent->left == target)
			target->parent->left = child;
		else if (target->parent->right == target)
			target->parent->right = child;
	}

	void delete_node(rb_node *target)
	{
		//삭제노드가 루트다 -> 그냥 삭제
		if (target->is_root())
		{
			delete_root();
			return ;
		}
		rb_node *child;
		if (target->left->empty())
			child = target->right;
		else
			child = target->left;
		replace_node(target, child);
		if (target->color == BLACK)
		{
			if (child->color == RED)
				child->color = BLACK;
			else
				delete_case1(child);
		}
		delete target;
	}

	void delete_case1(rb_node *target)
	{
		if (!target->parent->empty())
			delete_case2(target);
	}

	void delete_case2(rb_node *target)
	{
		rb_node *s = target->sibling();

		if (s->color == RED)
		{
			target->parent->color = RED;
			s->color = BLACK;
			if (target == target->parent->left)
				rotate_left(target->parent);
			else
				rotate_right(target->parent);
		}
		delete_case3(target);
	}

	void delete_case3(rb_node *target)
	{
		rb_node *s = target->sibling();

		if ((target->parent->color == BLACK) &&
			(s->color == BLACK) &&
			(s->left->color == BLACK) &&
			(s->right->color == BLACK))
		{
			s->color = RED;
			delete_case1(target->parent);
		}
		else
			delete_case4(target);
	}

	void delete_case4(rb_node *target)
	{
		rb_node *s = target->sibling();

		if ((target->parent->color == RED) &&
			(s->color == BLACK) &&
			(s->left->color == BLACK) &&
			(s->right->color == BLACK))
		{
			s->color = RED;
			target->parent->color = BLACK;
		}
		else
			delete_case5(target);
	}

	void delete_case5(rb_node *target)
	{
		rb_node *s = target->sibling();

		if  (s->color == BLACK) {
			/* 이 문은 자명하다,
				case 2로 인해서(case 2에서 '''N'''의 형제 노드를 원래 형제 노드 '''S'''의 자식노드로 바꾸지만,
				빨강 부모노드는 빨강 자식 노드를 가질 수 없기 때문에 '''N'''의 새로운 형제노드는 빨강일 수 없다). */
			/* 다음의 문은 빨강을 '''N'''의 부모노드의 오른쪽 자식의 오른쪽 자식으로 두기 위함이다.
				혹은 '''N'''의 부모노드의 왼쪽 자식의 왼쪽 자식으로 두기 위함. case 6에 넘기기 위해 */
			if ((target == target->parent->left) &&
				(s->right->color == BLACK) &&
				(s->left->color == RED))
			{ /* this last test is trivial too due to cases 2-4. */
				s->color = RED;
				s->left->color = BLACK;
				rotate_right(s);
			}
			else if ((target == target->parent->right) &&
				(s->left->color == BLACK) &&
				(s->right->color == RED))
			{/* this last test is trivial too due to cases 2-4. */
				s->color = RED;
				s->right->color = BLACK;
				rotate_left(s);
			}
		}
		delete_case6(target);
	}

	void delete_case6(rb_node *target)
	{
		rb_node *s = target->sibling();

		s->color = target->parent->color;
		target->parent->color = BLACK;

		if (target == target->parent->left) {
			s->right->color = BLACK;
			rotate_left(target->parent);
		} else {
			s->left->color = BLACK;
			rotate_right(target->parent);
		}
	}

	void clear()
	{
		clear(this->root);
	}

	void clear(rb_node *node)
	{
		if (node == this->nil)
			return ;
		clear(node->left);
		clear(node->right);
		if (node->is_root())
		{
			delete_root();
			return ;
		}
		else if (node->is_left())
			node->parent->left = this->nil;
		else
			node->parent->right = this->nil;
		delete (node);
	}

	void print()
	{
		ft::printTree(this->root, NULL, false);
	}

	void check_traversal()
	{
		rb_node* curr = this->root;
		rb_node* prev = this->nil;
		if (curr == this->nil)
			return ;
		while (1)
		{
			if (prev == curr->right)
			{
				prev = curr;
				if (curr->parent != this->nil)
					curr = curr->parent;
				else
					return ;
				continue ;
			}
			else if (prev == curr->left)
			{
				prev = curr;
				if (curr->right == this->nil)
					curr = curr->parent;
				else
					curr = curr->right;
				continue ;
			}
			if (curr->left != this->nil)
			{
				prev = curr;
				curr = curr->left;
				continue ;
			}
			if (curr->right != this->nil)
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
	// tree.erase_rbt(8);
	// // tree.erase_rbt(5);
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
		rbtree.erase_rbt(rand() % 800);
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