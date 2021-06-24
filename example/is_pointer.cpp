#include <iostream>

template <typename T>
struct remove_const
{
	typedef T type;
};

template <typename T>
struct remove_const<const T>
{
	typedef T type;
};

template <typename T>
struct remove_volatile
{
	typedef T type;
};

template <typename T>
struct remove_volatile<volatile T>
{
	typedef T type;
};

template <typename T>
struct remove_cv : remove_const<typename remove_volatile<T>::type> {};

template <typename T>
struct is_unqualified_pointer
{
	enum { value = false };
};

template <typename T>
struct is_unqualified_pointer<T*>
{
	enum { value = true };
};

template <typename T>
struct is_pointer_type : is_unqualified_pointer<typename remove_cv<T>::type> {};

template <typename T>
bool is_pointer(const T&)
{
	return is_pointer_type<T>::value;
}

struct Test
{
	int a;
};

int main()
{
	int* a;
	Test* b;
	std::string *c;
	std::string d;
	Test e;
	char f;
	char *g;

	std::cout << is_pointer(a) << std::endl;
	std::cout << is_pointer(b) << std::endl;
	std::cout << is_pointer(c) << std::endl;
	std::cout << is_pointer(d) << std::endl;
	std::cout << is_pointer(e) << std::endl;
	std::cout << is_pointer(f) << std::endl;
	std::cout << is_pointer(g) << std::endl;

}