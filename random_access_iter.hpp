#ifndef RANDOM_ACCESS_ITER_HPP
# define RANDOM_ACCESS_ITER_HPP

# include "iterator_traits.hpp"

namespace ft
{
template <typename T, typename Pointer = T*, typename Reference = T&,
		typename Category = ft::random_access_iterator_tag, typename Distance = ptrdiff_t>
class random_access_iter
{
public:
	typedef random_access_iter<T, Pointer, Reference> this_type_iterator;
	typedef random_access_iter<T, T*, T&> iterator;
	typedef random_access_iter<T, const T*, const T&> const_iterator;
	typedef T 			value_type;
	typedef Distance	difference_type;
	typedef Pointer		pointer;
	typedef Reference	reference;
	typedef Category	iterator_category;
private:
	pointer _p;
public:
	random_access_iter() : _p(0){}

	random_access_iter(const pointer x) : _p(x) {}

	random_access_iter(const iterator& from) : _p(from.get_ptr()) {}

	~random_access_iter() {}

	template <typename T2, typename A, typename B, typename C>
	const this_type_iterator &operator=(const random_access_iter<T2, A, B, C> &r)
	{
		this->_p = r.get_ptr();
		return (*this);
	}

	reference operator*()
	{
		return (*(this->_p));
	}

	pointer operator->()
	{
		return (_p);
	}

	this_type_iterator& operator++()
	{
		++_p;
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
		--_p;
		return (*this);
	}

	this_type_iterator operator--(int)
	{
		this_type_iterator temp(*this);
		this->operator--();
		return (temp);
	}

	this_type_iterator operator+(difference_type n) const
	{
		this_type_iterator temp(*this);
		temp._p += n;
		return (temp);
	}

	this_type_iterator operator-(difference_type n) const
	{
		this_type_iterator temp(*this);
		temp._p -= n;
		return (temp);
	}

	template <typename T2, typename A, typename B, typename C>
	difference_type operator-(const random_access_iter<T2, A, B, C> &r) const
	{
		return (this->_p - r.get_ptr());
	}

	this_type_iterator &operator+=(difference_type n)
	{
		this->_p += n;
		return (*this);
	}

	this_type_iterator &operator-=(difference_type n)
	{
		this->_p -= n;
		return (*this);
	}

	// Comparison
	template <typename T2, typename A, typename B, typename C>
	bool operator==(const random_access_iter<T2, A, B, C> &r) const
	{
		return (this->_p == r.get_ptr());
	}

	template <typename T2, typename A, typename B, typename C>
	bool operator!=(const random_access_iter<T2, A, B, C> &r) const
	{
		return (this->_p != r.get_ptr());
	}

	template <typename T2, typename A, typename B, typename C>
	bool operator<(const random_access_iter<T2, A, B, C> &r) const
	{
		return (this->_p < r.get_ptr());
	}

	template <typename T2, typename A, typename B, typename C>
	bool operator>(const random_access_iter<T2, A, B, C> &r) const
	{
		return (this->_p > r.get_ptr());
	}

	template <typename T2, typename A, typename B, typename C>
	bool operator>=(const random_access_iter<T2, A, B, C> &r) const
	{
		return (this->_p >= r.get_ptr());
	}

	template <typename T2, typename A, typename B, typename C>
	bool operator<=(const random_access_iter<T2, A, B, C> &r) const
	{
		return (this->_p <= r.get_ptr());
	}

	value_type &operator[](difference_type n)
	{
		return (*(*this + n));
	}

	value_type &operator[](difference_type n) const
	{
		return (*(*this + n));
	}

	pointer get_ptr() const
	{
		return (this->_p);
	}

	void set_ptr(pointer p)
	{
		this->_p = p;
	}
};

template <typename T, typename P, typename R, typename C>
random_access_iter<T, P, R, C>	operator+(typename random_access_iter<T, P, R, C>::difference_type n, const random_access_iter<T,P,R,C>& x)
{
	return (x + n);
};
}

#endif