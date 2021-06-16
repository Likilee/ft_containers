#ifndef LIST_HPP
# define LIST_HPP

# include <memory>
# include <exception>
# include "utils.hpp"
# include "bidirection_iter.hpp"
# include "reverse_iterator.hpp"

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

	// template <typename Integral>
	// void set_tail_value()
	// {

	// }
public:
	// 1. Constructors, Destructor, operator=
	explicit list(const allocator_type& alloc = allocator_type(), const node_allocator_type node_alloc = node_allocator_type())
		: _tail(0), _size(0), _alloc(alloc), _node_alloc(node_alloc) // list<value_type>() 기본 생성자
	{
		// this->_head = this->_node_alloc.allocate(1);
		// this->_node_alloc.construct(this->_head, node());
		this->_tail = this->_node_alloc.allocate(1);
		this->_node_alloc.construct(this->_tail, node());

		this->_tail->prev = this->_tail;
		this->_tail->next = this->_tail;
	}

	explicit list(size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type(),
				const node_allocator_type node_alloc = node_allocator_type()) // list<value_type>(n) 사이즈 넣고 생성
		: _tail(0), _size(0), _alloc(alloc), _node_alloc(node_alloc)
	{
		this->assign(n, val);
	}

// 	template <class InputIterator>
// 	list(InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type(),
// 			typename ft::enable_if<ft::is_iter<InputIterator>::value>::yes = 1)
// 		: _array(0), _size(0), _capacity(0), _alloc(alloc)
// 	{
// 		this->assign(first, last);
// 	}

// 	explicit list(const list &from) : _array(0), _size(0), _capacity(0), _alloc(from._alloc) // 깊은 복사가 되어야함.
// 	{
// 		this->assign(from.begin(), from.end());
// 	}

// 	~list()//This destroys all container elements, and deallocates all the storage capacity allocated by the list using its allocator.
// 	{
// 		this->_alloc.deallocate(this->_array, this->_capacity);
// 	}

// 	list	&operator=(const list &rvalue)
// 	{
// 		this->assign(rvalue.begin(), rvalue.end());
// 		return (*this);
// 	}

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
	if (n < this->_size)
		for (;n < this->_size; ++n)
			this->pop_back();
	else if (n > this->_size)
		for (;this->_size < n; --n)
			this->push_back(val);
}

bool empty() const
{
	return (this->_size == 0);
}

// 	// 4. Element access

// 	reference front()
// 	{
// 		return (_array[0]);
// 	}

// 	const_reference front() const
// 	{
// 		return (_array[0]);
// 	}

// 	reference back()
// 	{
// 		return (_array[this->_size - 1]);
// 	}

// 	const_reference back() const
// 	{
// 		return (_array[this->_size - 1]);
// 	}

// 5. Modifiers
//새 벡터의 크기가 현재 벡터 용량을 초과하는 경우에만 자동 재할당진행!
template <class InputIterator>
void assign (InputIterator first, InputIterator last, typename ft::enable_if<ft::is_iter<InputIterator>::value>::yes = 1)
{
	this->clear();
	this->insert(this->begin(), first, last);
}

void assign (size_type n, const value_type& val)
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
	node_ptr target = position.get_ptr();
	node_ptr new_node = this->_node_alloc.allocate(1);
	this->_node_alloc.construct(new_node, val);

	// if(this->empty())
	// {
	// 	this->_head = new_node;
	// 	this->_head->next = this->_tail;
	// 	this->_head->prev = this->_tail;
	// 	this->_tail->next = this->_head;
	// 	this->_tail->prev = this->_head;
	// }
	// else
		target->prev->next = new_node;
		new_node->prev = target->prev;
		target->prev = new_node;
		new_node->next = target;
	++this->_size;
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

iterator erase (iterator first, iterator last)
{
	while (first != last)
	{
		erase(first);
		++first;
	}
	return (first);
}

// 	void swap (list& x) // // All iterators, references and pointers remain valid for the swapped objects.
// 	{
// 		pointer temp_array = x._array;
// 		size_type temp_size = x.size();
// 		size_type temp_capacity = x.capacity();

// 		x._array = this->_array;
// 		x._size = this->_size;
// 		x._capacity = this->_capacity;
// 		this->_array = temp_array;
// 		this->_size = temp_size;
// 		this->_capacity = temp_capacity;
// 	}

void clear()
{
	this->erase(this->begin(), this->end());
	// this->_size = 0;
}

// };

// // 6. Relational operators

// template <class T, class Alloc>
// bool operator==(const list<T,Alloc>& lhs, const list<T,Alloc>& rhs)
// {
// 	return (lhs.size() == rhs.size() && ft::equal(lhs.begin(), lhs.end(), rhs.begin()));
// }

// template <class T, class Alloc>
// bool operator!=(const list<T,Alloc>& lhs, const list<T,Alloc>& rhs)
// {
// 	return (!(lhs == rhs));
// }

// template <class T, class Alloc>
// bool operator<(const list<T,Alloc>& lhs, const list<T,Alloc>& rhs)
// {
// 	return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
// }

// template <class T, class Alloc>
// bool operator<=(const list<T,Alloc>& lhs, const list<T,Alloc>& rhs)
// {
// 	return (!(rhs < lhs));
// }

// template <class T, class Alloc>
// bool operator>(const list<T,Alloc>& lhs, const list<T,Alloc>& rhs)
// {
// 	return (rhs < lhs);
// }

// template <class T, class Alloc>
// bool operator>=(const list<T,Alloc>& lhs, const list<T,Alloc>& rhs)
// {
// 	return (!(lhs < rhs));
// }

// // 7. Exchange contents of vectors
// template <class T, class Alloc>
// void swap (list<T,Alloc> &x, list<T,Alloc> &y)
// {
// 	x.swap(y);
// }
};
}

#endif