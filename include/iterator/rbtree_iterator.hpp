#ifndef RBTREE_ITERATOR_HPP
# define RBTREE_ITERATOR_HPP

# include "iterator/iterator_traits.hpp"
# include "utils/pair.hpp"
# include "rbtree/rbnode.hpp"
# include <iostream>

namespace ft
{
template <typename T, typename Pointer = T*, typename Reference = T&,
		typename Category = ft::bidirectional_iterator_tag, typename Distance = ptrdiff_t>
class rbtree_iterator
{
public:
	typedef T 			value_type;
	typedef Pointer		pointer;
	typedef Reference	reference;
	typedef ft::rb_node<value_type> node;
	typedef node*		node_ptr;
	typedef Distance	difference_type;
	typedef Category	iterator_category;
	typedef rbtree_iterator<T, Pointer, Reference> this_type_iterator;
	typedef rbtree_iterator<T, T*, T&> iterator;
	typedef rbtree_iterator<T, const T*, const T&> const_iterator;

private:
	node_ptr _p;

public:
	rbtree_iterator() : _p(NULL){}

	rbtree_iterator(const node_ptr x) : _p(x) {}

	rbtree_iterator(const iterator& from) : _p(from.get_ptr()) {}

	~rbtree_iterator() {}

	template <typename T2, typename P2, typename R2>
	const this_type_iterator &operator=(const rbtree_iterator<T2, P2, R2> &r)
	{
		this->_p = r.get_ptr();
		return (*this);
	}

	reference operator*() const
	{
		return (this->_p->get_value());
	}

	pointer operator->() const
	{
		return (&(this->_p->get_value()));
	}

	this_type_iterator& operator++()
	{
		this->_p = this->find_next();
		return (*this);
	}

	this_type_iterator operator++(int)
	{
		this_type_iterator temp(*this);
		this->operator++();
		return (temp);
	}

	this_type_iterator& operator--()
	{
		this->_p = this->find_before();
		return (*this);
	}

	this_type_iterator operator--(int)
	{
		this_type_iterator temp(*this);
		this->operator--();
		return (temp);
	}

	// Comparison
	template <typename T2, typename A, typename B, typename C>
	bool operator==(const rbtree_iterator<T2, A, B, C> &r) const
	{
		return (this->_p == r.get_ptr());
	}

	template <typename T2, typename A, typename B, typename C>
	bool operator!=(const rbtree_iterator<T2, A, B, C> &r) const
	{
		return (this->_p != r.get_ptr());
	}

	node_ptr get_ptr() const
	{
		return (this->_p);
	}

private:
	node_ptr find_next()
	{
		node_ptr result = this->_p->parent;

		if (!this->_p->right->empty()) //1. 오른쪽 원소 있으면 의 가장 작은 원소 가져오기
		{
			result = this->_p->right;
			while(!result->left->empty())
				result = result->left;
			return (result);
		}
		else if (!this->_p->parent->empty()) //2. 오른쪽 없으면 left child 인 result까지 올라기기
		{
			result = this->_p;
			while (!result->parent->empty())
			{
				if (result->is_left())
					return (result->parent);
				result = result->parent;
			}
			result = result->parent;
		}
		return (result);
	}

	node_ptr find_before()
	{
		node_ptr result = this->_p->parent;

		if (!this->_p->left->empty()) //1. 왼쪽 가장 큰 원소 가져오기
		{
			result = this->_p->left;
			while(!result->right->empty())
				result = result->right;
			return (result);
		}
		else if (!this->_p->parent->empty())
		{
			result = this->_p;
			while (!result->parent->empty())
			{
				if (result->is_right())
					return (result->parent);
				result = result->parent;
			}
			result = result->parent;
		}
		return (result);
	}
};
}

#endif