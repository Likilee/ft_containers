#ifndef RBTREE_HPP
# define RBTREE_HPP

# include <iostream>
# include "rbnode.hpp"

// 1. 루트(root) 노드는 블랙이다.
// 2. 노드 색은 레드 아니면 블랙이다.
// 3. 모든 외부 노드(External Node)는 블랙이다.
// 4. 모든 외부 노드의 경우 루트(root)부터 외부 노드까지 방문하는 블랙 노드의 수가 같다.
// 5. 레드 노드는 두 개가 연속해서 등장할 수 없다.
namespace ft
{
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

	void switch_has_one_child_node(rb_node* parent)
	{
		rb_node *child;

		if (parent->left == this->nil) // 오른쪽 자식이 있음
			child = parent->right;
		else // 왼쪽 자식이 있음
			child = parent->left;
		swap_one_depth(parent, child);
	}

	void switch_has_two_child_node(rb_node* target)
	{
		rb_node *node = get_left_biggest_node(target->left);

		if (node->parent == target) // node가 타겟의 바로 왼쪽노드이다.
			swap_one_depth(target, node);
		else //노드가 타겟에서 2depth 이상 떨어져 있다.
			swap_over_one_depth(target, node);
	}

	void swap_over_one_depth(rb_node *&high, rb_node *&low)
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
		swap_color(high->color, low->color);
		//치환한게 루트이면 루트 바꿔주고
		if (low->parent->empty())
			this->root = low;
	}

	void swap_one_depth(rb_node *&p, rb_node *&c)
	{
		rb_node *temp_p = p->parent;
		rb_node *temp_l = p->left;
		rb_node *temp_r = p->right;
		rb_color temp_c = p->color;

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
		swap_color(p->color, c->color);
		if (c->parent->empty())
			this->root = c;
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

	void swap_color(rb_color &a, rb_color &b)
	{
		rb_color temp;
		temp = a;
		a = b;
		b = temp;
	}

	void delete_root()
	{
		delete (this->root);
		this->root = this->nil;
	}

	//insert후 틀어진 rb_tree 규칙에 맞게 노드 조정
	void fix_violation(rb_node *current)
	{
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
					swap_color(parent_pt->color,
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
					this->swap_color(parent_pt->color,
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

		if  (s->color == BLACK)
		{
			if ((target == target->parent->left) &&
				(s->right->color == BLACK) &&
				(s->left->color == RED))
			{
				s->color = RED;
				s->left->color = BLACK;
				rotate_right(s);
			}
			else if ((target == target->parent->right) &&
				(s->left->color == BLACK) &&
				(s->right->color == RED))
			{
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
		if (node == this->nil)
		{
			// std::cout << "Failed search" << std::endl;
			return (this->nil);
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
			if (current->getData() == key)
			{
				// std::cout << "Key is already in" << std::endl;
				return ;
			}
			else if (current->getData() > key)
				current = current->left;
			else
				current = current->right;
		}
		// wile문을 빠져나왔으면 = 트리에 키가 존재하지 않음 아래 실행
		current = new rb_node(key);
		current->left = this->nil;
		current->right = this->nil;
		current->parent = parent;
		if (parent->getData() > key)
			parent->left = current;
		else
			parent->right = current;
		fix_violation(current);
	}

	void erase(const T& key)
	{
		// std::cout << "Erase: " << key << std::endl;
		//트리에 key가 없으면 아무 것도 안함.
		rb_node *target;
		if (this->nil == (target = this->search(key)))
			return ;
		//비어 있지 않다면 해당 키값의 노드를 찾음.
		if (target->is_leaf()) // case1 -자식이 없는 리프노드
			; // root 이면 무시하고 종료. 아니면 자기 자리 그대로.
		else if (target->has_one_child()) // case2 - 자식이 하나인 노드
			switch_has_one_child_node(target);
		else // case 3 - 자식이 둘인 노드
			switch_has_two_child_node(target);
		// 여기까지 왔을 때 target의 위치가 바뀌어 있어야함.
		delete_node(target);
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

#endif