#ifndef RBTREE_HPP
# define RBTREE_HPP

# include <iostream>
# include "rbnode.hpp"
# include "print_tree.hpp"
# include "pair.hpp"
# include "utils.hpp"
# include "map_iter.hpp"
// 1. 루트(root) 노드는 블랙이다.
// 2. 노드 색은 레드 아니면 블랙이다.
// 3. 모든 외부 노드(External Node)는 블랙이다.
// 4. 모든 외부 노드의 경우 루트(root)부터 외부 노드까지 방문하는 블랙 노드의 수가 같다.
// 5. 레드 노드는 두 개가 연속해서 등장할 수 없다.
namespace ft
{
template <typename T, typename Compare = ft::less<T>, typename Alloc = std::allocator<T> >
class rbtree
{
public:
	typedef T value_type;
	typedef ft::rb_node<value_type> node_type;
	typedef Compare comp_type;
	typedef Alloc allocator_type;
	typedef typename Alloc::template rebind<node_type>::other node_allocator_type;
	typedef map_iter<value_type, value_type*, value_type&> iterator;
	typedef map_iter<value_type, const value_type*, const value_type&> const_iterator;
private:
	node_type *root;
	node_type *nil;
	size_t size;
	comp_type comp;
	node_allocator_type node_alloc;

	node_type* construct_node(const value_type& value)
	{
		node_type* result = this->node_alloc.allocate(1);
		this->node_alloc.construct(result, node_type(value));
		return (result);
	}

	node_type* construct_node()
	{
		node_type* result = this->node_alloc.allocate(1);
		this->node_alloc.construct(result, node_type());
		return (result);
	}

	void destroy_node(node_type* node)
	{
		this->node_alloc.destroy(node);
		this->node_alloc.deallocate(node, 1);
	}

public:
	rbtree() : size(0), comp(comp_type()), node_alloc(node_allocator_type())
	{
		// this->nil = this->node_alloc.allocate(1);
		// this->node_alloc.construct(this->nil, node_type()); // 두 번째 인자를 복사해서 때려넣는다.
		this->nil = this->construct_node();
		this->nil->left = nil;
		this->nil->parent = nil;
		this->nil->right = nil;

		this->root = nil;
	}

	rbtree(const rbtree& x) : rbtree()
	{
		this->copy(x);
	}

	~rbtree()  // root 바닥부터 싹 지워주는거 만들어야함.(재귀로 짜면될 듯)
	{
		this->clear();
		destroy_node(this->nil);
	}

	node_type *getRoot()
	{
		return (this->root);
	}

	node_type *getNil() const
	{
		return (this->nil);
	}

	size_t getSize() const
	{
		return (this->size);
	}

	node_type *search(const T& value) const
	{
		return (search(this->root, value));
	}

	node_type *search(node_type *node, const T& value) const
	{
		if (node == this->nil)
		{
			// std::cout << "Failed search" << std::endl;
			return (this->nil);
		}
		else if (same_value(node->getValue(), value))
		{
			// std::cout << "Success search" << std::endl;
			return (node);
		}
		else if (comp(node->getValue(), value))
			return (search(node->getRight(), value));
		else
			return (search(node->getLeft(), value));
	}

	//key 이상인 첫지점을 찾는거임, 그럼 어떻게 해야겠어?, key보다 크면 왼쪽으로 내려가쟈!, 키보다 작으면 오른쪽으로 내려가자!()
	// 크면 무족건 왼쪽으로 가봐, 계속 가 작거나 같아질 때 까지가. 그러다가 작아졌어, 그럼, 오른쪽에서
	//탑다운으로 변곡점까지 가고
	//이터순회로 거슬러올라와.
	node_type *lower_bound(const T& value) const
	{
		return (lower_bound(this->root, value));
	}

	node_type *lower_bound(node_type *node, const T& value) const
	{
		if (comp(this->get_biggest()->getValue(), value))
			return (this->nil);
		while (1)
		{
			//현재 node 가 nil 이면 nil 리턴( 로워 바운드가 없는거) // 여기 없애도 될거 같음.
			if (node == this->nil)
				return (this->nil);
				//현재 node 와 value가 같으면 node 리턴 ( 차자따!)
			else if (same_value(node->getValue(), value))
				return (node);
			else if (comp(value, node->getValue())) // 현재 node가 찾는 값보다 작으면,
			{
				if (node->left == this->nil)
					return (node);
				node = node->left;
			}
			else
			{
				if (node->right == this->nil)
					return (this->get_next_node(node)); //여기 수정 현재보다 한개 큰노드 가져오기
				node = node->right;
			}
		}
	}

	node_type *upper_bound(const T& value) const
	{
		return (upper_bound(this->root, value));
	}

	node_type *upper_bound(node_type *node, const T& value) const
	{
		if (!comp(value, this->get_biggest()->getValue()))
			return (this->nil);
		while (1)
		{
			//현재 node 가 nil 이면 nil 리턴( 로워 바운드가 없는거) // 여기 없애도 될거 같음.
			if (node == this->nil)
				return (this->nil);
				//현재 node 와 value가 같으면 node 리턴 ( 차자따!)
			else if (comp(value, node->getValue())) // 현재 node가 찾는 값보다 작으면,
			{
				if (node->left == this->nil)
					return (node);
				node = node->left;
			}
			else
			{
				if (node->right == this->nil)
					return (this->get_next_node(node)); //여기 수정 현재보다 한개 큰노드 가져오기
				node = node->right;
			}
		}
	}

	pair<node_type*, bool> insert(const T& value)
	{
		//빈 트리면, key를 루트노드로 추가한다.
		if (this->empty())
		{
			this->root = this->construct_node(value);
			this->root->parent = this->nil;
			this->root->left = this->nil;
			this->root->right = this->nil;
			this->root->color = BLACK;
			++this->size;
			this->nil->parent = this->get_biggest();
			return (pair<node_type*, bool>(this->root, true));
		}
		//트리를 루트 노드부터 key값과 비교하며 같은게 있는지 찾는다.
		node_type *current = this->root;
		node_type *parent = this->nil;
		while (current != this->nil)
		{
			parent = current;
			if (same_value(value, current->getValue()))
			{
				// std::cout << "Key is already in" << std::endl;
				return (pair<node_type*, bool>(current, false));
			}
			else if (comp(value, current->getValue()))
				current = current->left;
			else
				current = current->right;
		}
		// wile문을 빠져나왔으면 = 트리에 키가 존재하지 않음 아래 실행
		current = this->construct_node(value);
		current->left = this->nil;
		current->right = this->nil;
		current->parent = parent;
		if (comp(value, parent->getValue()))
			parent->left = current;
		else
			parent->right = current;
		fix_violation(current);
		++this->size;
		this->nil->parent = this->get_biggest();
		return (pair<node_type*, bool>(current, true));
	}

	size_t erase(node_type *target)
	{
		if (this->nil == target)
			return (0);
		//비어 있지 않다면 해당 키값의 노드를 찾음.
		if (!target->is_leaf()) // case1 -자식이 없는 리프노드
			; // root 이면 무시하고 종료. 아니면 자기 자리 그대로.
		else if (target->has_one_child()) // case2 - 자식이 하나인 노드
			switch_has_one_child_node(target);
		else // case 3 - 자식이 둘인 노드
			switch_has_two_child_node(target);
		// 여기까지 왔을 때 target의 위치가 바뀌어 있어야함.

		std::cout << "Switch after:" << std::endl;
		this->print();
		std::cout << std::endl;
		delete_node(target);
		return (1);
	}

	size_t erase(const T& value)
	{
		return (erase(this->search(value)));
	}

	template <typename InputIter>
	size_t erase(InputIter iterator, typename ft::enable_if<ft::is_iter<InputIter>::value>::yes = 1)
	{
		return (erase(iterator.get_ptr()));
	}

	void delete_node(node_type *target)
	{
		//삭제노드가 루트다 -> 그냥 삭제
		if (target->is_root() && target->is_leaf())
		{
			delete_root();
			return ;
		}
		node_type *child;
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
		this->destroy_node(target);
		--this->size;
	}

	void clear()
	{
		clear(this->root);
		this->size = 0;
	}

	void clear(node_type *node)
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
		this->destroy_node(node);
	}

	void copy(const rbtree& x)
	{
		this->clear();
		copy(x.root);
	}

	void copy(const node_type* node)
	{
		if(false == copy(node->value))
			return ;
		copy(node->left);
		copy(node->right);
	}

	bool copy(const value_type* value)
	{
		if (value == NULL)
			return (false);
		insert(*value);
		return (true);
	}

	void print()
	{
		ft::printTree(this->root, NULL, false);
		std::cout << "Tree size: " << this->size << std::endl;
	}

	void check_traversal()
	{
		node_type* curr = this->root;
		node_type* prev = this->nil;
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

	node_type *get_smallest() const
	{
		node_type *result = this->root;
		while (!result->left->empty())
			result = result->left;
		return (result);
	}

	node_type *get_biggest() const
	{
		node_type *result = this->root;
		while (!result->right->empty())
			result = result->right;
		return (result);
	}

private:
	bool same_value(const value_type &a, const value_type &b) const
	{
		return (!comp(a, b) && !comp(b, a));
	}

	bool empty() const
	{
		return (this->root == this->nil);
	}

	void switch_has_one_child_node(node_type* parent)
	{
		node_type *child;

		if (parent->left == this->nil) // 오른쪽 자식이 있음
			child = parent->right;
		else // 왼쪽 자식이 있음
			child = parent->left;
		swap_one_depth(parent, child);
	}

	void switch_has_two_child_node(node_type* target)
	{
		node_type *node = get_left_biggest_node(target->left);

		if (node->parent == target) // node가 타겟의 바로 왼쪽노드이다.
			swap_one_depth(target, node);
		else //노드가 타겟에서 2depth 이상 떨어져 있다.
			swap_over_one_depth(target, node);
	}

	void swap_over_one_depth(node_type *&high, node_type *&low)
	{
		node_type *temp_l = high->left;
		node_type *temp_r = high->right;
		node_type *temp_p = high->parent;

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

	void swap_one_depth(node_type *&p, node_type *&c)
	{
		node_type *temp_p = p->parent;
		node_type *temp_l = p->left;
		node_type *temp_r = p->right;

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

	void rotate_left(node_type *&pt)
	{
		node_type *pt_right = pt->right;

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

	void rotate_right(node_type *pt)
	{
		node_type *pt_left = pt->left;

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
		this->destroy_node(this->root);
		this->root = this->nil;
		--this->size;
	}

	//insert후 틀어진 rb_tree 규칙에 맞게 노드 조정
	void fix_violation(node_type *current)
	{
		node_type *parent_pt = this->nil;
		node_type *grand_parent_pt = this->nil;

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

				node_type *uncle_pt = grand_parent_pt->right;

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
				node_type *uncle_pt = grand_parent_pt->left;

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

	node_type *get_left_biggest_node(node_type *left)
	{
		while (left->right != this->nil)
			left = left->right;
		return (left);
	}

	node_type *get_next_node(node_type *position) const
	{
		iterator itr(position);
		++itr;
		return (itr.get_ptr());
	}


	void replace_node(node_type* target, node_type* child)
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

	void delete_case1(node_type *target)
	{
		if (!target->parent->empty())
			delete_case2(target);
	}

	void delete_case2(node_type *target)
	{
		node_type *s = target->sibling();

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

	void delete_case3(node_type *target)
	{
		node_type *s = target->sibling();

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

	void delete_case4(node_type *target)
	{
		node_type *s = target->sibling();

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

	void delete_case5(node_type *target)
	{
		node_type *s = target->sibling();

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

	void delete_case6(node_type *target)
	{
		node_type *s = target->sibling();

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

};
}

#endif