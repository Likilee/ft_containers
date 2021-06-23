#ifndef MAP_ITER_HPP
# define MAP_ITER_HPP

# include "iterator_traits.hpp"
# include "pair.hpp"
# include "rbnode.hpp"
# include <iostream>

namespace ft
{
template <typename T, typename Pointer = T*, typename Reference = T&,
		typename Category = ft::bidirectional_iterator_tag, typename Distance = ptrdiff_t>
class map_iter
{
public:
	typedef map_iter<T, Pointer, Reference> this_type_iterator;
	typedef map_iter<T, T*, T&> iterator;
	typedef map_iter<T, const T*, const T&> const_iterator;
	typedef T 			value_type;
	typedef Pointer		pointer;
	typedef Reference	reference;
	typedef rb_node<value_type> node;
	typedef node*		node_ptr;
	typedef Distance	difference_type;
	typedef Category	iterator_category;
private:
	node_ptr _p;

	node_ptr find_next()
	{
		node_ptr result = this->_p->parent;
		//1. 오른쪽의 가장 작은 원소 가져오기
		if (!this->_p->right->empty())
		{
			result = this->_p->right;
			while(!result->left->empty())
				result = result->left;
			return (result);
		}
		//2. 오른쪽이 없으면 current - child : left child 인 current까지 올라기기
		else if (!this->_p->parent->empty())
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
		//3. 부모가 empty면 자신이 가장 큰값.
		return (result);
	}

	node_ptr find_before()
	{
		node_ptr result = this->_p->parent;
		//1. 왼쪽 가장 큰 원소 가져오기
		if (!this->_p->left->empty())
		{
			result = this->_p->left;
			while(!result->right->empty())
				result = result->right;
			return (result);
		}
		//2. 왼쪽 없으면 current - child : right child 인 current까지 올라기기
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
		//3. 부모가 empty면 자신이 가장 작은 값.
		return (result);
	}

public:
	map_iter() : _p(NULL){}

	map_iter(const node_ptr x) : _p(x) {}

	map_iter(const iterator& from) : _p(from.get_ptr()) {}

	~map_iter() {}

	template <typename T2, typename P2, typename R2>
	const this_type_iterator &operator=(const map_iter<T2, P2, R2> &r)
	{
		this->_p = r.get_ptr();
		return (*this);
	}

	reference operator*() const//pair<T,C> 리턴
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
	bool operator==(const map_iter<T2, A, B, C> &r) const
	{
		return (this->_p == r.get_ptr());
	}

	template <typename T2, typename A, typename B, typename C>
	bool operator!=(const map_iter<T2, A, B, C> &r) const
	{
		return (this->_p != r.get_ptr());
	}

	node_ptr get_ptr() const
	{
		return (this->_p);
	}
};
}

#endif