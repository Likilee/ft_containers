/*
T* // A non-const iterator to a non-const element. Corresponds to std::vector<T>::iterator
T* const // A const iterator to a non-const element. Corresponds to const std::vector<T>::iterator
const T* // A non-const iterator to a const element. Corresponds to std::vector<T>::const_iterator
*/

// 이게 되려나
#include <iostream>
namespace ft
{
template<class Iter>
struct iterator_traits {
	typedef typename Iter::value_type value_type;
	typedef typename Iter::iterator_category iterator_category;
	typedef typename Iter::difference_type difference_type;
	typedef typename Iter::pointer pointer;
	typedef typename Iter::reference reference;
};

struct input_iterator_tag {};
struct output_iterator_tag {};
struct forward_iterator_tag : public input_iterator_tag {};
struct bidirectional_iterator_tag : public forward_iterator_tag {};
struct random_access_iterator_tag : public bidirectional_iterator_tag {};


template <typename T, typename Pointer = T*, typename Reference = T&, typename Distance = ptrdiff_t, typename >
class Randomiter : public ft::iterator<ft::random_access_iterator_tag, T>
{
	public:
		typedef Randomiter<T> iterator;
		typedef Randomiter<const T> const_iterator;
	public:
		typename ft::iterator<ft::random_access_iterator_tag, T>::pointer p;
		Randomiter()
		{
			this->p = new T;
		}
};
}

int main()
{
	ft::Randomiter<int> itr;
	*(itr.p) = 3;
	std::cout << *(itr.p) << std::endl;
}