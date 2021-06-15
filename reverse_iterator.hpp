#ifndef REVERSE_ITERATOR_HPP
# define REVERSE_ITERATOR_HPP

# include "iterator_traits.hpp"
# include "iterator.hpp"

namespace ft
{
template <typename Iterator>
class reverse_iterator
{
public:
	typedef Iterator iterator_type;
	typedef typename iterator_traits<Iterator>::iterator_category iterator_category;
	typedef typename iterator_traits<Iterator>::value_type value_type;
	typedef typename iterator_traits<Iterator>::difference_type difference_type;
	typedef typename iterator_traits<Iterator>::pointer pointer;
	typedef typename iterator_traits<Iterator>::reference reference;
private:
	iterator_type _base;
public:
	reverse_iterator() : _base(iterator_type()) {}

	explicit reverse_iterator (iterator_type it) : _base(it) {}

	template <class Iter>
	reverse_iterator (const reverse_iterator<Iter>& rev_it) : _base(rev_it.base()) {}

	~reverse_iterator() {};

	iterator_type base() const
	{
		return (this->_base);
	}

	reference operator*() const
	{
		iterator_type temp_itr = this->_base;
		--temp_itr;
		return (*temp_itr);
	}

	reverse_iterator operator+(difference_type n) const
	{
		reverse_iterator result(this->_base - n);
		return (result);
	}

	reverse_iterator& operator++()
	{
		--(this->_base);
		return (*this);
	}

	reverse_iterator  operator++(int)
	{
		reverse_iterator temp = *this;
		++(*this);
		return (temp);
	}

	reverse_iterator& operator+= (difference_type n)
	{
		this->_base -= n;
		return (*this);
	}

	reverse_iterator operator-(difference_type n) const
	{
		reverse_iterator result(this->_base + n);
		return (result);
	}

	reverse_iterator& operator--()
	{
		++(this->_base);
		return (*this);
	}

	reverse_iterator  operator--(int)
	{
		reverse_iterator temp = *this;
		--(*this);
		return (temp);
	}

	reverse_iterator& operator-= (difference_type n)
	{
		this->_base += n;
		return (*this);
	}

	pointer operator->() const
	{
		return &(this->operator*());
	}

	reference operator[] (difference_type n) const
	{
		return (this->_base[-n-1]);
	}
};

template <typename Iterator>
reverse_iterator<Iterator> operator+(typename reverse_iterator<Iterator>::difference_type n,
									const reverse_iterator<Iterator>& x)
{
	return (x + n);
}

template <typename Iterator, typename Iterator2>
typename reverse_iterator<Iterator>::difference_type operator- (const reverse_iterator<Iterator>& lhs,
															const reverse_iterator<Iterator2>& rhs)
{
	return (rhs.base() - lhs.base());
}
//덧셈 연산자 n + iter 오버로딩

//비교 연산자 정의
template <typename Iterator, typename Iterator2>
bool operator== (const reverse_iterator<Iterator>& lhs,
				const reverse_iterator<Iterator2>& rhs)
{
	return (lhs.base() == rhs.base());
}

template <typename Iterator, typename Iterator2>
bool operator!= (const reverse_iterator<Iterator>& lhs,
			const reverse_iterator<Iterator2>& rhs)
{
	return (lhs.base() != rhs.base());
}

template <typename Iterator, typename Iterator2>
bool operator<(const reverse_iterator<Iterator>& lhs,
			const reverse_iterator<Iterator2>& rhs)
{
	return (lhs.base() > rhs.base());
}

template <typename Iterator, typename Iterator2>
bool operator<=(const reverse_iterator<Iterator>& lhs,
			const reverse_iterator<Iterator2>& rhs)
{
	return (lhs.base() >= rhs.base());
}

template <typename Iterator, typename Iterator2>
bool operator>(const reverse_iterator<Iterator>& lhs,
				const reverse_iterator<Iterator2>& rhs)
{
	return (lhs.base() < rhs.base());
}
template <typename Iterator, typename Iterator2>
bool operator>= (const reverse_iterator<Iterator>& lhs,
				const reverse_iterator<Iterator2>& rhs)
{
	return (lhs.base() <= rhs.base());
}

}
#endif