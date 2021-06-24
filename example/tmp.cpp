// 어떻게 하면 이터레이터인지 식별하는 메타템플릿 함수를 만들 수 있지? (is_iterator)
// 템플릿 특수화를 이용해서
#include <vector>
#include <list>
#include <iostream>

//**** 템플릿 메타프로그래밍 실습 ****
namespace ft
{
//0. enable_if<true>::type 존재, enable_if<false>::type 존재x
template <bool B, class T = void>
struct enable_if;

template <class T>
struct enable_if<true, T>
{
	typedef T type;
	typedef int yes;
};

//1. is_same<typename, typename> : 타입 네임이 같으면 value = true, 다르면 false;
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

//2. is_void<typename> : 타입 네임이 void 이면 true, 아니면 false
template <typename T>
struct is_void
{
	static const bool value = false;
};

template <>
struct is_void<void>
{
	static const bool value = true;
};

// iterator_traits : is_iter에서 사용
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

//3. is_iter<typename> : 이터레이터이지 아닌지 판단해서 bool return , std iter도 호환됨
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

//4. 오버로딩 테스트 함수
void printIter(int a)
{
	std::cout << "no it isn't!" << std::endl;
};

template <typename T>
void printIter(T a, typename ft::enable_if<ft::is_iter<T>::value>::yes = 1)
{
	std::cout << "It's iterator" << std::endl;
};
}

int main()
{
	// std::cout << ft::is_same<int,int>::value << std::endl;
	// std::cout << ft::is_same<int,const int>::value << std::endl;
	// std::cout << ft::is_same<std::vector<int>::iterator,std::vector<std::string>::iterator>::value << std::endl;
	std::cout << ft::is_iter<int>::value << std::endl;
	std::cout << ft::is_iter<std::vector<std::string>::iterator>::value << std::endl;
	std::cout << ft::is_iter<std::list<std::string>::iterator>::value << std::endl;
	std::vector<int>::iterator itr;

	ft::printIter(itr);
	ft::printIter(3);
};