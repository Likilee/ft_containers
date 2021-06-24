#ifndef LIST_HPP
# define LIST_HPP

# include <memory>
# include <exception>
# include "utils/utils.hpp"
# include "iterator/bidirection_iter.hpp"
# include "iterator/reverse_iterator.hpp"

//list 특징
// ** 이터레이터 테스트 해보니 환형(원형) 으로 구현해야할듯, 그리고 int 일 때는 end()노드에 size값이 담겨있다..
// char 일때는 널문자 담긴듯.
// 1. 데이터가 순서대로 저장된다.
// 2. 중복을 허용한다.
// 3. 노드를 추가할 때 현재 위치에 다른 노드가 있으면 뒤로 밀어버린다.
// 4. 노드를 삭제하면 뒤에 있는 노드를 당겨온다.
// 5. 처음/끝/중간에 노드(엘리먼트)를 추가/삭제할 수 있다.
// 6. 모든 데이터에 접근할 수 있다.
// 7. 양방향 반복을 허용
// 8. 처음/끝/중간에 추가 삭제 시간이 동일
namespace ft
{

template <typename T, typename Alloc = std::allocator<T> >
class list
{
public:
	typedef T value_type;
	typedef value_type& reference;
	typedef const value_type& const_reference;
	typedef value_type* pointer;
	typedef list_node<T> node;
	typedef node* node_ptr;
	typedef const pointer const_pointer;
	typedef size_t size_type; // 사이즈 타입
	typedef Alloc allocator_type;
	typedef typename Alloc::template rebind<node>::other node_allocator_type;
	typedef ptrdiff_t difference_type;  // 이터레이터 간극 반환 타입
	typedef bidirection_iter<T, T*, T&> iterator;
	typedef bidirection_iter<T, const T*, const T&> const_iterator;
	typedef reverse_iterator<const_iterator > const_reverse_iterator;
	typedef reverse_iterator<iterator> reverse_iterator; // 이거 위아래 순서 바꾸면 컴파일 안됨 왜지?

private:
	node_ptr _tail;
	size_type _size;
	allocator_type _alloc;
	node_allocator_type _node_alloc;

	void	create_tail()
	{
		this->_tail = this->_node_alloc.allocate(1);
		this->_node_alloc.construct(this->_tail, node());

		this->_tail->prev = this->_tail;
		this->_tail->next = this->_tail;
	}

	void add_node(iterator position, iterator element)
	{
		if (position == element)
			return ;
		node_ptr target = position.get_ptr();
		node_ptr src = element.get_ptr();

		target->prev->next = src;
		src->prev = target->prev;
		target->prev = src;
		src->next = target;
		++this->_size;
	}

	// void add_node(iterator position, iterator first, iterator last)
	// {
	// 	// this->_size += ft::distance(first, last) + 1;
	// 	node_ptr front = position.get_ptr()->prev;
	// 	node_ptr back = position.get_ptr();
	// 	front->next = first.get_ptr();
	// 	first.get_ptr()->prev = front;
	// 	back->prev = last.get_ptr();
	// 	last.get_ptr()->next = back;
	// }

	void sub_node(iterator position)
	{
		node_ptr target = position.get_ptr();

		target->prev->next = target->next;
		target->next->prev = target->prev;
		target->next = NULL;
		target->prev = NULL;
		--this->_size;
	}

	// void sub_node(iterator first, iterator last)
	// {
	// 	node_ptr front = first.get_ptr()->prev;
	// 	node_ptr back = last.get_ptr();
	// 	front->next = back;
	// 	back->prev = front;
	// 	// this->_size -= ft::distance(first, last);
	// 	// std::cout << "Sub distance" << ft::distance(first, last) << std::endl;
	// }

public:
	// 1. Constructors, Destructor, operator=
	explicit list(const allocator_type& alloc = allocator_type(), const node_allocator_type node_alloc = node_allocator_type())
		: _tail(0), _size(0), _alloc(alloc), _node_alloc(node_alloc) // list<value_type>() 기본 생성자
	{
		create_tail();
	}

	explicit list(size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type(),
				const node_allocator_type node_alloc = node_allocator_type()) // list<value_type>(n) 사이즈 넣고 생성
		: _tail(0), _size(0), _alloc(alloc), _node_alloc(node_alloc)
	{
		create_tail();
		this->assign(n, val);
	}

	template <class InputIterator>
	list(InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type(),
		const node_allocator_type node_alloc = node_allocator_type(), typename ft::enable_if<ft::is_iter<InputIterator>::value>::yes = 1)
		: _tail(0), _size(0), _alloc(alloc), _node_alloc(node_alloc)
	{
		create_tail();
		this->assign(first, last);
	}

	explicit list(const list &from) : _tail(0), _size(0), _alloc(from._alloc), _node_alloc(from._node_alloc) // 깊은 복사가 되어야함.
	{
		create_tail();
		this->assign(from.begin(), from.end());
	}

	~list()//This destroys all container elements, and deallocates all the storage capacity allocated by the list using its allocator.
	{
		this->clear();
	}

	list	&operator=(const list &rvalue)
	{
		this->assign(rvalue.begin(), rvalue.end());
		return (*this);
	}

	// 2. Iterators
	iterator begin()
	{
		return (iterator(this->_tail->next));
	}

	const_iterator begin() const
	{
		return (const_iterator(this->_tail->next));
	}

	iterator end()
	{
		return (iterator(this->_tail));
	}
	const_iterator end() const
	{
		return (const_iterator(this->_tail));
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

	// 3. Capacity
	bool empty() const
	{
		return (this->_size == 0);
	}

	size_type size() const
	{
		return (this->_size);
	}

	size_type max_size() const
	{
		return (std::numeric_limits<size_type>::max() / sizeof(node));
	}

	// 4. Element access
	reference front()
	{
		return (*(this->begin()));
	}

	const_reference front() const
	{
		return (*(this->begin()));
	}

	reference back()
	{
		iterator back = this->end().get_ptr();
		--back;
		return (*back);
	}

	const_reference back() const
	{
		iterator back = this->end().get_ptr();
		--back;
		return (*back);
	}

	// 5. Modifiers
	//새 벡터의 크기가 현재 벡터 용량을 초과하는 경우에만 자동 재할당진행!
	template <class InputIterator>
	void assign (InputIterator first, InputIterator last, typename ft::enable_if<ft::is_iter<InputIterator>::value>::yes = 1)
	{
		this->clear();
		this->insert(this->begin(), first, last);
	}

	void assign(size_type n, const value_type& val)
	{
		this->clear();
		this->insert(this->begin(), n, val);
	}

	void push_front(const value_type& val)
	{
		this->insert(this->_tail->next, val);
	}

	void pop_front()
	{
		this->erase(this->begin());
	}

	void push_back(const value_type& val)
	{
		this->insert(this->_tail, val);
	}

	void pop_back()
	{
		iterator temp = this->end();
		--temp;
		this->erase(temp);
	}

	//An iterator that points to the first of the newly inserted elements.
	iterator insert(iterator position, const value_type& val)
	{
		node_ptr new_node = this->_node_alloc.allocate(1);
		this->_node_alloc.construct(new_node, val);

		add_node(position, new_node);
		return (new_node);
	}

	void insert(iterator position, size_type n, const value_type& val)
	{
		for (size_type i = 0; i < n; ++i)
			insert(position, val);
	}

	template <class InputIterator>
	void insert(iterator position, InputIterator first, InputIterator last,
				typename ft::enable_if<ft::is_iter<InputIterator>::value>::yes = 1)
	{
		for (;first != last; ++first)
			insert(position, *first);
	}

	//지우면 타겟의 넥스트를 리턴
	iterator erase(iterator position) // 범위 밖의 이터레이터 들어오는거 테스트해보니 segfault, 디펜스 안해도 될듯.
	{
		node_ptr target = position.get_ptr();
		target->prev->next = target->next;
		target->next->prev = target->prev;
		++position;
		this->_node_alloc.destroy(target);
		this->_node_alloc.deallocate(target, 1);
		--this->_size;
		return (position);
	}

	iterator erase(iterator first, iterator last)
	{
		iterator temp;

		while (first != last)
		{
			temp = first;
			++first;
			erase(temp);
		}
		return (first);
	}

	void swap (list& x) // // All iterators, references and pointers remain valid for the swapped objects.
	{
		node_ptr temp_tail = x._tail;
		size_type temp_size = x._size;

		x._tail = this->_tail;
		x._size = this->_size;

		this->_tail = temp_tail;
		this->_size = temp_size;
	}

	void resize(size_type n, value_type val = value_type())
	{
		size_type origin_size = this->_size;

		if (n < origin_size )
			for (;n < origin_size; ++n)
				this->pop_back();
		else if (n > origin_size)
			for (;origin_size < n; --n)
				this->push_back(val);
	}

	void clear()
	{
		this->erase(this->begin(), this->end());
	}

	// Operations
	// Splice 는 전송, 노드 그자체를 이동시키는 거구먼 오케잉~

	void splice (iterator position, list& x)
	{
		splice (position, x, x.begin(), x.end());
	}

	void splice(iterator position, list& x, iterator i)
	{
		splice(position, x, i, ++i);
	}

	void splice(iterator position, list& x, iterator first, iterator last)
	{
		difference_type gap = ft::distance(first, last);
		if (first == last)
			return ;
		node_ptr x_first = first.get_ptr();
		node_ptr x_last = last.get_ptr()->prev;
		node_ptr pos = position.get_ptr();
		node_ptr first_prev = pos->prev;
		x_first->prev->next = x_last->next;
		x_last->next->prev = x_first->prev;

		pos->prev->next = x_first;
		pos->prev = x_last;
		x_first->prev = first_prev;
		x_last->next = pos;

		x._size -= gap;
		this->_size += gap;
	}

	void remove(const value_type& val)
	{
		for (iterator itr = this->begin(); itr != this->end();)
		{
			if (*itr == val)
				itr = erase(itr);
			else
				++itr;
		}
	}

	template <class Predicate>
	void remove_if (Predicate pred)
	{
		for (iterator itr = this->begin(); itr != this->end();)
		{
			if (pred(*itr))
				itr = erase(itr);
			else
				++itr;
		}
	}

	void unique()
	{
		iterator itr = this->begin();
		iterator compare;
		++itr;
		while (itr != this->end())
		{
			compare = itr;
			--compare;
			if (*itr == *compare)
				itr = erase(itr);
			else
				++itr;
		}
	}

	template <class BinaryPredicate>
	void unique(BinaryPredicate binary_pred)
	{
		iterator itr = this->begin();
		iterator compare;
		++itr;
		while (itr != this->end())
		{
			compare = itr;
			--compare;
			if (binary_pred(*itr,*compare))
				itr = erase(itr);
			else
				++itr;
		}
	}

	// merge 양쪽 포인터 이동하면서 가르키고있는거 비교 합치고, 포인터 이동~, Splice 잘 쓰면 될 듯
	// 실험 해보니 이전에 있던 이터레이터 들은 해당 노드를 그대로 가리키고 있음.
	//The function does nothing if (&x == this).
	void merge(list& x)
	{
		if (this == &x)
			return ;
		iterator to = this->begin();
		iterator from = x.begin();
		iterator temp;

		while (from != x.end())
		{
			if (*from < *to)
			{
				temp = from;
				++from;
				splice(to, x, temp);
			}
			else
				++to;
			if (to == this->end())
			{
				splice(to, x, from, x.end());
				break ;
			}
		}
	}

	template <class Compare>
	void merge(list& x, Compare comp)
	{
		if (this == &x)
			return ;

		iterator to = this->begin();
		iterator from = x.begin();
		iterator temp;

		while (from != x.end())
		{
			if (comp(*from, *to))
			{
				temp = from;
				++from;
				splice(to, x, temp);
			}
			else
				++to;
			if (to == this->end())
			{
				splice(to, x, from, x.end());
				break ;
			}
		}
	}

	// Node have to stable after sort
	void sort()
	{
		iterator i, j, key;
		i = this->begin();
		++i;
		while (i != this->end())
		{
			key = i;
			j = i;
			++i;
			--j;
			while (j != this->end() && *key <*j)
				--j;
			++j;
			if (j != key)
			{
				sub_node(key);
				add_node(j, key);
			}
		}
	}

	template <class Compare>
	void sort(Compare comp)
	{
		iterator i, j, key;

		i = this->begin();
		++i;
		while (i != this->end())
		{
			key = i;
			j = i;
			++i;
			--j;
			while (j != this->end() && comp(*key, *j))
				--j;
			++j;
			if (j != key)
			{
				sub_node(key);
				add_node(j, key);
			}
		}
	}

	void reverse()
	{
		iterator i = this->begin();
		iterator current;
		node_ptr temp;
		while (1)
		{
			current = i;
			++i;
			temp = current.get_ptr()->next;
			current.get_ptr()->next = current.get_ptr()->prev;
			current.get_ptr()->prev = temp;
			if (current == this->end())
				break ;
		}
	}

};

// 6. Relational operators
template <class T, class Alloc>
bool operator==(const list<T,Alloc>& lhs, const list<T,Alloc>& rhs)
{
	return (lhs.size() == rhs.size() && ft::equal(lhs.begin(), lhs.end(), rhs.begin()));
}

template <class T, class Alloc>
bool operator!=(const list<T,Alloc>& lhs, const list<T,Alloc>& rhs)
{
	return (!(lhs == rhs));
}

template <class T, class Alloc>
bool operator<(const list<T,Alloc>& lhs, const list<T,Alloc>& rhs)
{
	return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
}

template <class T, class Alloc>
bool operator<=(const list<T,Alloc>& lhs, const list<T,Alloc>& rhs)
{
	return (!(rhs < lhs));
}

template <class T, class Alloc>
bool operator>(const list<T,Alloc>& lhs, const list<T,Alloc>& rhs)
{
	return (rhs < lhs);
}

template <class T, class Alloc>
bool operator>=(const list<T,Alloc>& lhs, const list<T,Alloc>& rhs)
{
	return (!(lhs < rhs));
}

// 7. Exchange contents of vectors
template <class T, class Alloc>
void swap (list<T,Alloc> &x, list<T,Alloc> &y)
{
	x.swap(y);
}
}

#endif