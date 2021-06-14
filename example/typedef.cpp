class parent
{
	public:
		typedef int I;
		typedef char C;
};

class child : public parent
{
	public:
		I i;
		C c;
};

#include <iostream>
#include <algorithm>
#include <vector>

int main()
{
	std::sort()
	child me;

	me.i = 0;
	me.c = 'c';
	std::cout << me.i << me.c << std::endl;
}