#include<iostream>
#include"Matrix.h"
#include"MatrixIO.h"

class Tripple
{
	public:
	void operator()(int& arg)
	{
		arg=arg * arg * arg;
	}
};

//a.apply(f)
/*
void tripple(int& arg)
{
	arg = arg * arg * arg;
}
*/

//a.apply(f,a)
void tripple(int& arg,const int& pow)
{
	arg = std::pow(arg,pow);
}

int main()
{
	Numeric_lib::Matrix<int, 2> m(3, 3);
	for (int i = 0; i < m.dim1(); i++)
	{
		for (int j = 0; j < m.dim2(); j++)
			m[i][j] = i + j;
	}
	std::cout << m;
	m.apply(Tripple());
	std::cout << m;
	m.apply(tripple,3);
	std::cout << m;
	m.apply([](int& arg) {arg = arg * arg * arg; });
	std::cout << m;
	return 0;
}

