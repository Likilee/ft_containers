#ifndef LIST_HPP
# define LIST_HPP

# include <memory>
//list 특징
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
class listiterator;

template <typename T, typename Alloc=std::allocator<T> >
class list
{
private:
	typedef T value_type;
	typedef Alloc allocator_type;
	typedef allocator_type::reference reference;
public:
	list()
	{

	}
	list(const list &from);
	~list();
	list	&operator=(const list &rvalue);
};
}
#endif