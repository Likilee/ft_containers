#ifndef VECTOR_HPP
# define VECTOR_HPP

# include <memory>
# include <exception>

namespace ft
{
//iterator 콘셉트를 구현하여 알고리즘 오버로딩이 가능하도록
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

template <typename T>
class vector_iterator
{
	public:
		typedef T value_type;
		typedef random_access_iterator_tag iterator_category;
		typedef ptrdiff_t difference_type;
		typedef value_type* pointer;
		typedef value_type& reference;
	private:
		pointer _p;
	public:
		vector_iterator() : _p(0) {}

		vector_iterator(pointer x) : _p(x) {}

		vector_iterator(const vector_iterator<value_type>& vec_itr) : _p(vec_itr._p) {}

		~vector_iterator() {}

		vector_iterator &operator=(const vector_iterator &r)
		{
			this->_p = r._p;
			return (this);
		}

		bool operator==(const vector_iterator &r) const
		{
			return (this->_p == r._p);
		}

		bool operator!=(const vector_iterator &r) const
		{
			return (this->_p != r._p);
		}

		reference operator*()
		{
			return (*(this->_p));
		}

		pointer operator->()
		{
			return (_p);
		}

		vector_iterator& operator++()
		{
			++_p;
			return (*this);
		}

		vector_iterator operator++(int)
		{
			vector_iterator temp(*this);
			this->operator++();
			return (temp);
		}

		vector_iterator& operator--()
		{
			--_p;
			return (*this);
		}

		vector_iterator operator--(int)
		{
			vector_iterator temp(*this);
			this->operator--();
			return (temp);
		}

		vector_iterator operator+(difference_type n) const
		{
			vector_iterator temp(*this);
			temp._p += n;
			return (temp);
		}

		vector_iterator operator-(difference_type n) const
		{
			vector_iterator temp(*this);
			temp._p -= n;
			return (temp);
		}

		difference_type operator-(const vector_iterator &r) const
		{
			return (this->_p - r._p);
		}

		vector_iterator &operator+=(difference_type n)
		{
			this->_p += n;
			return (*this);
		}

		vector_iterator &operator-=(difference_type n)
		{
			this->_p -= n;
			return (*this);
		}

		bool operator<(const vector_iterator &r) const
		{
			return (this->_p < r._p);
		}

		bool operator>(const vector_iterator &r) const
		{
			return (this->_p > r._p);
		}

		bool operator>=(const vector_iterator &r) const
		{
			return (this->_p >= r._p);
		}

		bool operator<=(const vector_iterator &r) const
		{
			return (this->_p <= r._p);
		}

		value_type &operator[](difference_type n)
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
	typedef vector_iterator<T> iterator;
	typedef vector_iterator<const T> const_iterator;
	// typedef ~ reverse_iterator;
	// typedef ~ const_reverse_iterator;
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

	// template <class InputIterator>
	// vector(InputIterator first, InputIterator last,const allocator_type& alloc = allocator_type())
	// {

	// }

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
	// reverse_iterator rbegin();
	// const_reverse_iterator rbegin() const;
	// reverse_iterator rend();
	// const_reverse_iterator rend() const;

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
	void assign (InputIterator first, InputIterator last)
	{
		difference_type gap = last - first;
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
	// void pop_back();
	// iterator insert (iterator position, const value_type& val);
	// void insert (iterator position, size_type n, const value_type& val);
	// template <class InputIterator>
	// void insert (iterator position, InputIterator first, InputIterator last);
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
			if (target + gap != this->end())
				*target = *(target + gap);
			++target;
		}
		this->_size -= gap;
		return (first);
	}
	// void swap (vector& x);
	void clear()
	{
		this->erase(this->begin(), this->end());
		this->_size = 0;
	}
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