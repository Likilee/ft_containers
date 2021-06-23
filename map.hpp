#ifndef MAP_HPP
# define MAP_HPP

# include <memory>
# include <exception>
# include "utils.hpp"
# include "rbtree.hpp"
# include "pair.hpp"
# include "map_iter.hpp"
# include "reverse_iterator.hpp"

namespace ft
{

template < class Key, class T, class Compare = less<Key>,
			class Alloc = std::allocator<pair<const Key,T> > >
class map
{
public:
	typedef Key key_type;
	typedef T mapped_type;
	typedef pair<const key_type, mapped_type> value_type;
	typedef Compare key_compare;
	typedef Alloc allocator_type;
	typedef value_type& reference;
	typedef const value_type& const_reference;
	typedef value_type* pointer;
	typedef const value_type* const_pointer;
	typedef rb_node<value_type> node;
	typedef node* node_ptr;
	typedef size_t size_type; // 사이즈 타입
	typedef ptrdiff_t difference_type;  // 이터레이터 간극 반환 타입
	typedef map_iter<value_type, value_type*, value_type&> iterator;
	typedef map_iter<value_type, const value_type*, const value_type&> const_iterator;
	typedef reverse_iterator<const_iterator> const_reverse_iterator;
	typedef reverse_iterator<iterator> reverse_iterator;

	class value_compare
	{
		protected:
			Compare comp;
		public:
			value_compare() : comp() {}
			bool operator()(const value_type& x, const value_type& y) const
			{
				return comp(x.first, y.first);
			}
	};
	typedef ft::rbtree<value_type, value_compare> tree_type;

private:
	tree_type _tree;
	key_compare _comp;
	allocator_type _alloc;
public:
	tree_type &getTree()
	{
		return (this->_tree);
	}

	explicit map(const key_compare& comp = key_compare(),
				const allocator_type& alloc = allocator_type())
	: _tree(), _comp(comp), _alloc(alloc)
	{}

	template <class InputIterator>
	map(InputIterator first, InputIterator last,
		const key_compare& comp = key_compare(),
		const allocator_type& alloc = allocator_type(),
		typename ft::enable_if<ft::is_iter<InputIterator>::value>::yes = 1)
	: _tree(), _comp(comp), _alloc(alloc)
	{
		insert(first, last);
	}

	map(const map& x) : _tree(), _comp(x._comp), _alloc(x._alloc)
	{
		*this = x;
	}

	~map() {}

	map	&operator=(const map &x)
	{
		this->_tree.copy(x._tree);
		return (*this);
	}

	//Iterators:
	iterator begin()
	{
		return (iterator(this->_tree.get_smallest()));
	}

	const_iterator begin() const
	{
		return (const_iterator(this->_tree.get_smallest()));
	}

	iterator end()
	{
		return (iterator(this->_tree.getNil()));
	}

	const_iterator end() const
	{
		return (const_iterator(this->_tree.getNil()));
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

// // 3. Capacity
	bool empty() const
	{
		return (this->_tree.getSize() == 0);
	}

	size_type size() const
	{
		return (this->_tree.getSize());
	}

	size_type max_size() const
	{
		// return (std::numeric_limits<size_type>::max() / sizeof(node));
		return (std::numeric_limits<size_type>::max() / sizeof(node));
	}

	mapped_type& operator[] (const key_type& k)
	{
		return ((*((this->insert(ft::make_pair(k, mapped_type()))).first)).second);
	}

	// 삽입한 이터 또는 기존 요소 이터 반환
	pair<iterator,bool> insert(const value_type& val)
	{
		pair<node_ptr, bool> result = this->_tree.insert(val);

		return (ft::make_pair(iterator(result.first), result.second));
	}

	// An iterator that points to the first of the newly inserted elements.
	iterator insert(iterator position, const value_type& val)
	{
		(void)position;
		pair<iterator,bool> result = this->insert(val);
		return (result.first);
	}

	template <class InputIterator>
	void insert(InputIterator first, InputIterator last,
				typename ft::enable_if<ft::is_iter<InputIterator>::value>::yes = 1)
	{
		for (;first != last; ++first)
			insert(*first);
	}

	void erase(iterator position)
	{
		this->_tree.erase(position);
	}

	size_type erase(const key_type& k)
	{
		return (this->_tree.erase(value_type(k, mapped_type())));
	}

	void erase(iterator first, iterator last)
	{
		while (first != last)
		{
			iterator temp = first;
			++first;
			std::cout << temp->first << std::endl;
			erase(temp);
			this->_tree.print();
		}
	}

	void swap (map& x)
	{
		tree_type temp = x._tree;
		x._tree = this->_tree;
		this->_tree = temp;
	}

	void clear()
	{
		this->erase(this->begin(), this->end());
	}

	key_compare key_comp() const
	{
		return (key_compare());
	}

	value_compare value_comp() const
	{
		return (value_compare());
	}

	iterator find(const key_type& k)
	{
		return (iterator(this->_tree.search(value_type(k, mapped_type()))));
	}

	const_iterator find(const key_type& k) const
	{
		return (iterator(this->_tree.search(value_type(k, mapped_type()))));
	}

	size_type count(const key_type& k) const
	{
		if (find(k) == this->end())
			return (0);
		return (1);
	}

	iterator lower_bound(const key_type& k)
	{
		//1. 가장 큰 요소가 k 미만 일 때, end 리턴
		//3. k 이상 첫 요소 찾아서 반화.
		return (iterator(this->_tree.lower_bound(value_type(k, mapped_type()))));
	}

	const_iterator lower_bound(const key_type& k) const
	{
		return (iterator(this->_tree.lower_bound(value_type(k, mapped_type()))));
	}

	iterator upper_bound (const key_type& k)
	{
		return (iterator(this->_tree.upper_bound(value_type(k, mapped_type()))));
	}

	const_iterator upper_bound (const key_type& k) const
	{
		return (iterator(this->_tree.upper_bound(value_type(k, mapped_type()))));
	}

	pair<const_iterator,const_iterator> equal_range(const key_type& k) const
	{
		return (make_pair(lower_bound(k), upper_bound(k)));
	}

	pair<iterator,iterator> equal_range (const key_type& k)
	{
		return (make_pair(lower_bound(k), upper_bound(k)));
	}
};
}

#endif