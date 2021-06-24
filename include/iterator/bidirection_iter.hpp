#ifndef BIDIRECTION_ITER_HPP
# define BIDIRECTION_ITER_HPP

# include "iterator/iterator_traits.hpp"
# include <iostream>

namespace ft
{

template <typename T>
class list_node
{
public:
	T data;
	list_node *prev;
	list_node *next;
	list_node() : data(T()), prev(NULL), next(NULL) {}
	list_node(const T &val) : data(val), prev(NULL), next(NULL) {}
	~list_node() {}
};

template <typename T, typename Pointer = T*, typename Reference = T&, typename NodePtr = ft::list_node<T>*,
		typename Category = ft::bidirectional_iterator_tag, typename Distance = ptrdiff_t>
class bidirection_iter
{
public:
	typedef bidirection_iter<T, Pointer, Reference> this_type_iterator;
	typedef bidirection_iter<T, T*, T&> iterator;
	typedef bidirection_iter<T, const T*, const T&> const_iterator;
	typedef T 			value_type;
	typedef Distance	difference_type;
	typedef Pointer		pointer;
	typedef Reference	reference;
	typedef Category	iterator_category;
	typedef NodePtr node_ptr;
private:
	node_ptr _p;
public:
	bidirection_iter() : _p(NULL){}

	bidirection_iter(const node_ptr x) : _p(x) {}

	bidirection_iter(const iterator& from) : _p(from.get_ptr()) {}

	~bidirection_iter() {}

	template <typename T2, typename A, typename B, typename C>
	const this_type_iterator &operator=(const bidirection_iter<T2, A, B, C> &r)
	{
		this->_p = r.get_ptr();
		return (*this);
	}

	reference operator*()
	{
		return (this->_p->data);
	}

	pointer operator->()
	{
		return (&(this->_p->data));
	}

	this_type_iterator& operator++()
	{
		this->_p = this->_p->next;
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
		this->_p = this->_p->prev;
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
	bool operator==(const bidirection_iter<T2, A, B, C> &r) const
	{
		return (this->_p == r.get_ptr());
	}

	template <typename T2, typename A, typename B, typename C>
	bool operator!=(const bidirection_iter<T2, A, B, C> &r) const
	{
		return (this->_p != r.get_ptr());
	}

	node_ptr get_ptr() const
	{
		return (this->_p);
	}

	void set_ptr(node_ptr p)
	{
		this->_p = p;
	}
};
}

#endif