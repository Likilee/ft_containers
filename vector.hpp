#ifndef VECTOR_HPP
# define VECTOR_HPP

# include <memory>
# include <exception>
# include "iterator.hpp"
# include "reverse_iterator.hpp"
# include <iostream>

namespace ft
{
//iterator 콘셉트를 구현하여 알고리즘 오버로딩이 가능하도록
// template<class Iter>
// struct iterator_traits {
// 	typedef typename Iter::value_type value_type;
// 	typedef typename Iter::iterator_category iterator_category;
// 	typedef typename Iter::difference_type difference_type;
// 	typedef typename Iter::pointer pointer;
// 	typedef typename Iter::reference reference;
// };

// struct input_iterator_tag {};
// struct output_iterator_tag {};
// struct forward_iterator_tag : public input_iterator_tag {};
// struct bidirectional_iterator_tag : public forward_iterator_tag {};
// struct random_access_iterator_tag : public bidirectional_iterator_tag {};

template <typename T, typename Alloc = std::allocator<T> >
class vector
{
public:
	typedef T value_type;
	typedef Alloc allocator_type;
	typedef value_type& reference;
	typedef const value_type& const_reference;
	typedef value_type* pointer;
	typedef const pointer const_pointer;
	typedef size_t size_type; // 사이즈 타입
	typedef ptrdiff_t difference_type;  // 이터레이터 간극 반환 타입
	typedef random_access_iter<T, T*, T&> iterator;
	typedef random_access_iter<T, const T*, const T&> const_iterator;
	typedef reverse_iterator<const_iterator > const_reverse_iterator;
	typedef reverse_iterator<iterator> reverse_iterator; // 이거 위아래 순서 바꾸면 컴파일 안됨 왜지?

private:
	pointer _array;
	size_type _size;
	size_type _capacity;
	Alloc _alloc;
	// 삭제
	// 제할당
	void put(size_type idx, const value_type &val)
	{
		(*this)[idx] = val;
	}
	void copy_right(iterator position, size_type gap)
	{
		if (position + gap > this->end())
			this->reserve(this->_size * 2);
		*(position + gap) = *position;
		++this->_size;
	}

public:
	explicit vector(const allocator_type& alloc = allocator_type())
		: _array(0), _size(0), _capacity(0), _alloc(alloc) // vector<value_type>() 기본 생성자
	{
		this->_array = this->_alloc.allocate(0);
	}

	explicit vector(size_type n, const value_type& val = value_type(),
					const allocator_type& alloc = allocator_type()) // vector<value_type>(n) 사이즈 넣고 생성
		: _array(0), _size(0), _capacity(0), _alloc(alloc)
	{
		this->assign(n, val);
	}

	template <class InputIterator>
	vector(InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type(),
			typename ft::enable_if<ft::is_iter<InputIterator>::value>::yes = 1)
		: _array(0), _size(0), _capacity(0), _alloc(alloc)
	{
		this->assign(first, last);
	}

	explicit vector(const vector &from) : _array(0), _size(0), _capacity(0), _alloc(from._alloc) // 깊은 복사가 되어야함.
	{
		this->assign(from.begin(), from.end());
	}

	~vector()//This destroys all container elements, and deallocates all the storage capacity allocated by the vector using its allocator.
	{
		this->_alloc.deallocate(this->_array, this->_capacity);
	}

	vector	&operator=(const vector &rvalue)
	{
		this->assign(rvalue.begin(), rvalue.end());
		return (*this);
	}

	iterator begin()
	{
		return (iterator(this->_array));
	}

	const_iterator begin() const
	{
		return (const_iterator(this->_array));
	}

	iterator end()
	{
		return (iterator(this->_array + this->_size));
	}
	const_iterator end() const
	{
		return (const_iterator(this->_array + this->_size));
	}
	reverse_iterator rbegin()
	{
		return (reverse_iterator(this->end()));
	}

	const_reverse_iterator rbegin() const
	{
		return (const_reverse_iterator(this->end()));
	}

	reverse_iterator rend()
	{
		return (reverse_iterator(this->begin()));
	}
	const_reverse_iterator rend() const
	{
		return (const_reverse_iterator(this->begin()));
	}

	size_type size() const
	{
		return (this->_size);
	}

	size_type max_size() const
	{
		return (std::numeric_limits<size_type>::max() / sizeof(value_type));
	}

	void resize(size_type n, value_type val = value_type())
	{
		if (n > this->_capacity)
		{
			if (n < this->_capacity * 2)
				this->reserve(this->_capacity * 2);
			else
				this->reserve(n);
		}
		if (n < this->_size)
			for (size_type i = n; i < this->_size; ++i)
				this->_alloc.destroy(&_array[i]);
		else if (n > this->_size)
			for (size_type i = this->_size; i < n; ++i)
				this->put(i, val);
		this->_size = n;
	}

	size_type capacity() const
	{
		return (this->_capacity);
	}

	bool empty() const
	{
		return (this->_size == 0);
	}
	void reserve (size_type n)
	{
		if (n == 0)
			n = 1;
		if (n > this->_capacity)
		{
			pointer new_array = this->_alloc.allocate(n);// -2*size 크기의 메모리를 새로 할당
			for(size_type i = 0; i < this->_size; ++i)// 새로 할당한 메모리로 기존 원소 전부를 복사/이동
			{
				new_array[i] = this->_array[i];
				this->_alloc.destroy(&this->_array[i]);
			}
			this->_alloc.deallocate(this->_array, this->_capacity);
			this->_array = new_array; // 데이터 포인터를 새로운 할당메모리로 지정
			this->_capacity = n;
		}
	}
	reference operator[](size_type n)
	{
		return this->_array[n];
	}

	const_reference operator[](size_type n) const
	{
		return this->_array[n];
	}

	reference at(size_type n)
	{
		if (n >= this->_size)
			throw std::out_of_range("kilee");
		return (this->_array[n]);
	}

	const_reference at(size_type n) const
	{
		if (n >= this->_size)
			throw std::out_of_range("kilee");
		return (this->_array[n]);
	}

	reference front()
	{
		return (_array[0]);
	}

	const_reference front() const
	{
		return (_array[0]);
	}

	reference back()
	{
		return (_array[this->_size - 1]);
	}

	const_reference back() const
	{
		return (_array[this->_size - 1]);
	}

	//새 벡터의 크기가 현재 벡터 용량을 초과하는 경우에만 자동 재할당진행!
	template <class InputIterator>
	void assign (InputIterator first, InputIterator last, typename ft::enable_if<ft::is_iter<InputIterator>::value>::yes = 1)
	{
		difference_type gap = ft::distance(first, last);
		this->clear();
		this->reserve(gap);
		for (difference_type i = 0; i < gap; ++i)
		{
			this->_array[i] = *first;
			++first;
		}
		this->_size = gap;
	}

	void assign (size_type n, const value_type& val)
	{
		this->clear();
		this->reserve(n);
		for (size_type i = 0; i < n; ++i)
			this->put(i, val);
		this->_size = n;
	}

	void push_back (const value_type& val)
	{
		//마지막 원소 다음에 val 저장
		//벡터 크기를 1만큼 증가
		//끝
		if (this->_size < this->_capacity)
		{
			this->_array[_size] = val;
			++(this->_size);
		}
		else
		{
			this->reserve(this->_size * 2);
			// this->_array[_size] = val; // 마지막 원소 다음에 val 저장하고 벡터 크기를 1만큼 증가
			// ++this->_size;
			this->push_back(val);
		}
	}
	void pop_back()
	{
		//맨 뒤 원소 제거(원소가 없으면 아무일도 안함)
		this->erase(this->end() - 1);
	}

	iterator insert(iterator position, const value_type& val)
	{
		insert(position, 1, val);
		return (position);
	}

	void insert(iterator position, size_type n, const value_type& val)
	{
		ft::vector<T> temp(position, this->end());
		size_type pos = position - this->begin();

		this->resize(this->_size + n);

		while (n--)
			this->put(pos++, val);
		for (iterator itr = temp.begin(); itr != temp.end(); ++itr)
			this->put(pos++, *itr);
	}

	template <class InputIterator>
	void insert (iterator position, InputIterator first, InputIterator last,
				typename ft::enable_if<ft::is_iter<InputIterator>::value>::yes = 1)
	{
		ft::vector<T> temp(position, this->end());
		size_type n = ft::distance(first, last); // 이거 계산하는 거 공용 함수 만들어야할 듯(iterate_traits에 맞춰서)
		size_type pos = position - this->begin();

		this->resize(this->_size + n);

		while (first != last)
			this->put(pos++, *first++);
		for (iterator itr = temp.begin(); itr != temp.end(); ++itr)
			this->put(pos++, *itr);
	}

	iterator erase (iterator position) // 범위 밖의 이터레이터 들어오는거 테스트해보니 segfault
	{
		iterator target = position;

		this->_alloc.destroy(target.get_ptr());
		while(target != this->end())
		{
			*target = *(target + 1);
			++target;
		}
		--this->_size;
		return (position);
	}

	iterator erase (iterator first, iterator last)
	{
		iterator target = first;
		difference_type gap = last - first;
		while (target != last)
		{
			this->_alloc.destroy(target.get_ptr());
			++target;
		}
		while (target != this->end())
		{
			*(target - gap) = *target;
			++target;
		}
		this->_size -= gap;
		return (first);
	}

//all iterators, references and pointers remain valid for the swapped objects.
	void swap (vector& x)
	{
		pointer temp_array = x._array;
		size_type temp_size = x.size();
		size_type temp_capacity = x.capacity();

		x._array = this->_array;
		x._size = this->_size;
		x._capacity = this->_capacity;
		this->_array = temp_array;
		this->_size = temp_size;
		this->_capacity = temp_capacity;
	}

	void clear()
	{
		this->erase(this->begin(), this->end());
		this->_size = 0;
	}

};

//두 구간의 대응되는 요소를 차례대로 비교하는데 첫 번째 요소가 두 번째 요소보다 작으면
//true를 리턴하고 크면 false를 리턴하며 즉시 종료한다.
// 만약 같다면 다음 요소를 똑같은 방식으로 계속 비교하기를 구간끝까지 반복한다.
//디폴트 비교 함수 객체가 less이므로 첫 번째 구간이 두 번째 구간보다 작아야만 true를 리턴하며 같을 경우는 작지 않으므로 false가 리턴된다.
//만약 첫 번째 구간이 먼저 끝나고 두 번째 구간은 아직 값이 남았으면 이 경우는 true를 리턴한다.
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

template <class T, class Alloc>
bool operator==(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
{
	return (lhs.size() == rhs.size() && ft::equal(lhs.begin(), lhs.end(), rhs.begin()));
}

template <class T, class Alloc>
bool operator!=(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
{
	return (!(lhs == rhs));
}

template <class T, class Alloc>
bool operator<(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
{
	return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
}

template <class T, class Alloc>
bool operator<=(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
{
	return (!(rhs < lhs));
	// return ((lhs == rhs) || (lhs < rhs));
}
template <class T, class Alloc>
bool operator>(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
{
	return (rhs < lhs);
	// return (ft::lexicographical_compare(rhs.begin(), rhs.end(), lhs.begin(), lhs.end()));
}

template <class T, class Alloc>
bool operator>=(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
{
	return (!(lhs < rhs));
	// return ((lhs == rhs) || (lhs > rhs));
}

template <class T, class Alloc>
void swap (vector<T,Alloc> &x, vector<T,Alloc> &y)
{
	x.swap(y);
}
}
#endif