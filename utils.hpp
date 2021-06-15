#ifndef UTILS_HPP
# define UTILS_HPP

# include "iterator_traits.hpp"

namespace ft
{
// 1. Iterator Compare Utility function
template <class InputIterator1, class InputIterator2>
bool lexicographical_compare (InputIterator1 first1, InputIterator1 last1,
							InputIterator2 first2, InputIterator2 last2)
{
	while (first1 != last1)
	{
		if (first2 == last2 || *first2 < *first1)
			return (false);
		else if (*first1 < *first2)
			return (true);
		++first1;
		++first2;
	}
	return (first2 != last2);
}

template <class InputIterator1, class InputIterator2>
bool equal(InputIterator1 first1, InputIterator1 last1,
			InputIterator2 first2)
{
	while (first1!=last1)
	{
		if (!(*first1 == *first2))	// or: if (!pred(*first1,*first2)), for version 2
			return (false);
		++first1;
		++first2;
	}
	return (true);
}

template <typename InputItr>
typename InputItr::difference_type distance(InputItr first, InputItr last)
{
	typename InputItr::difference_type dist = 0;

	while (first++ != last)
		++dist;
	return (dist);
}

// 2. For template overloading
template <bool B, class T = void>
struct enable_if;

template <class T>
struct enable_if<true, T>
{
	typedef T type;
	typedef int yes;
};

template <typename T, typename U>
struct is_same
{
	static const bool value = false;
};

template <typename T>
struct is_same<T,T>
{
	static const bool value = true;
};

template <typename T, typename Enable = void>
struct is_iter
{
	static const bool value = false;
};

template <typename T>
struct is_iter<T, typename ft::enable_if<ft::is_same<typename T::value_type, typename ft::iterator_traits<T>::value_type>::value>::type>
{
	static const bool value = true;
};
}
#endif