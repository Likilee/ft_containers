#ifndef VECTOR_HPP
# define VECTOR_HPP

# include <memory>

namespace ft
{
//iterator 콘셉트를 구현하여 알고리즘 오버로딩이 가능하도록
template<class Iter>
struct iterator_traits {
	typedef typename Iter::iterator_category iterator_category;
	typedef typename Iter::value_type value_type;
	//  typedef typename Iter::difference_type difference_type;
	//  typedef typename Iter::pointer pointer;
	//  typedef typename Iter::reference reference;
};


struct input_iterator_tag {};
struct output_iterator_tag {};
struct forward_iterator_tag : public input_iterator_tag {};
struct bidirectional_iterator_tag : public forward_iterator_tag {};
struct random_access_iterator_tag : public bidirectional_iterator_tag {};

template <typename T>
class vector_iterator
{
	typedef random_access_iterator_tag iterator_category;
	typedef T value_type;
	// typedef typename Iter::difference_type difference_type;
	// typedef typename Iter::pointer pointer;
	// typedef typename Iter::reference reference;
};

template <typename T, typename Alloc = std::allocator<T> >
class vector
// 
public:
	typedef T value_type;
	typedef Alloc allocator_type;
	typedef value_type& reference;
	typedef const value_type& const_reference;
	typedef value_type* pointer;
	typedef const pointer const_pointer;
	typedef size_t size_type; // 사이즈 타입
	typedef ptrdiff_t difference_type;  // 이터레이터 간극 반환 타입
	typedef vector_iterator<T> iterator;
	typedef vector_iterator<const T> const_iterator;
	// typedef ~ reverse_iterator;
	// typedef ~ const_reverse_iterator;
private:
	pointer array;
	size_type size;
	size_type capacity;
	Alloc alloc;
public:
	explicit vector(const allocator_type& alloc = allocator_type()){}  // vector<value_type>() 기본 생성자

	explicit vector(size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type()) // vector<value_type>(n) 사이즈 넣고 생성
	{
		this->array = this->alloc.allocate(0);
	}

	template <class InputIterator>
	vector (InputIterator first, InputIterator last,const allocator_type& alloc = allocator_type())
	{

	}

	vector (const vector& x);

	vector(const vector &from);

	~vector()//This destroys all container elements, and deallocates all the storage capacity allocated by the vector using its allocator.
	{
		this->alloc.deallocate(this->array, this->capacity)
	}
	// vector	&operator=(const vector &rvalue);
	// iterator begin();
	// const_iterator begin() const;
	// iterator end();
	// const_iterator end() const;
	// reverse_iterator rbegin();
	// const_reverse_iterator rbegin() const;
	// reverse_iterator rend();
	// const_reverse_iterator rend() const;

	size_type size() const
	{
		return (this->size);
	}

	size_type max_size() const
	{
		std::numeric_limits<size_type>::max() / sizeof(value_type);
	}

	// void resize (size_type n, value_type val = value_type())
	// size_type capacity() const;
	// bool empty() const;
	// void reserve (size_type n);
	// reference operator[] (size_type n);
	// const_reference operator[] (size_type n) const;
	// reference at (size_type n);
	// const_reference at (size_type n) const;
	// reference front();
	// const_reference front() const;
	reference back()
	{
		return (array[this->size - 1]);
	}

	const_reference back() const
	{
		return (array[this->size - 1]);
	}
	// template <class InputIterator>
	// void assign (InputIterator first, InputIterator last);
	// void assign (size_type n, const value_type& val);
	// void push_back (const value_type& val);
	// void pop_back();
	// iterator insert (iterator position, const value_type& val);
	// void insert (iterator position, size_type n, const value_type& val);
	// template <class InputIterator>
	// void insert (iterator position, InputIterator first, InputIterator last);
	// iterator erase (iterator position);
	// iterator erase (iterator first, iterator last);
	// void swap (vector& x);
	// void clear();
};

// template <class T, class Alloc>
// bool operator== (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs);

// template <class T, class Alloc>
// bool operator!= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs);

// template <class T, class Alloc>
// bool operator<  (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs);

// template <class T, class Alloc>
// bool operator<= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs);

// template <class T, class Alloc>
// bool operator>  (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs);

// template <class T, class Alloc>
// bool operator>= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs);

// template <class T, class Alloc>
// void swap (vector<T,Alloc>& x, vector<T,Alloc>& y);
}
#endif