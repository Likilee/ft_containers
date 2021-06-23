#ifndef RBNODE_HPP
# define RBNODE_HPP

# include <memory>

namespace ft
{
enum rb_color
{
	RED,
	BLACK
};

template <typename T, typename Alloc = std::allocator<T> >
struct rb_node
{
public:
	T *value;
	rb_node *left;
	rb_node *right;
	rb_node *parent;
	rb_color color;
	Alloc alloc;

	rb_node() : value(NULL), left(NULL), right(NULL), parent(NULL), color(BLACK), alloc(Alloc()) {}; // nil_node

	rb_node(const T& val) : value(NULL), left(NULL), right(NULL), parent(NULL), color(RED), alloc(Alloc())
	{
		this->value = alloc.allocate(1);
		alloc.construct(this->value, val);
	}

	rb_node(const rb_node& x) : value(NULL), left(NULL), right(NULL), parent(NULL), color(RED), alloc(Alloc())
	{
		if (!(x.value == NULL))
		{
			this->value = alloc.allocate(1);
			alloc.construct(this->value, x.getValue());
		}
	}

	~rb_node()
	{
		if (this->value != NULL)
		{
			alloc.destroy(this->value);
			alloc.deallocate(this->value, 1);
		}
	}

	T& getValue() const
	{
		return (*this->value);
	}

	T& getColor()
	{
		return (this->color);
	}

	rb_node *getLeft()
	{
		return (this->left);
	}

	rb_node *getRight()
	{
		return (this->right);
	}

	rb_node *getParent()
	{
		return (this->parent);
	}

	bool empty()
	{
		if (this->value == NULL)
			return (true);
		return (false);
	}

	bool is_root()
	{
		if (this->parent->empty())
			return (true);
		return (false);
	}

	bool is_left()
	{
		if (this->parent->left == this)
			return (true);
		else
			return (false);
	}

	bool is_right()
	{
		if (this->parent->right == this)
			return (true);
		else
			return (false);
	}

	bool is_leaf()
	{
		if (this->left->empty() && this->right->empty())
			return (true);
		return (false);
	}

	bool has_one_child()
	{
		if (!is_leaf() && (this->left->empty() || this->right->empty()))
			return (true);
		return (false);
	}

	bool has_two_child()
	{
		if (!this->left->empty() && !this->right->empty())
			return (true);
		return (false);
	}

	rb_node *sibling()
	{
		if (this == this->parent->left)
			return (this->parent->right);
		else
			return (this->parent->left);
	}

	bool operator<(const rb_node& x) const
	{
		return (*(this->value) < *x.value);
	}

	bool operator>(const rb_node& x) const
	{
		return (x < *this);
	}

	bool operator==(const rb_node& x) const
	{
		return (*(this->value) == *x.value);
	}
};
}

#endif