#include <iostream>

template <typename T>
class Test
{
	public:
		typedef T value_type;
		Test(T) : val(T)
		{}
		const value_type get_val()
		{
			return (this->val);
		}
	private:
		value_type val;

};

int main()
{
	const int a = 3;
	const const int b = 5;

	std::cout << a << std::endl;
	std::cout << b << std::endl;
}