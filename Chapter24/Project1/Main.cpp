#include<iostream>
#include"Matrix.h"
#include"MatrixIO.h"
#include <random>
#include <vector>

struct Tripple
{
	void operator()(int& arg)
	{
		arg=arg * arg * arg;
	}
};

/*
void tripple(int& arg)  //a.apply(f)
{
	arg = arg * arg * arg;
}
*/

void tripple(int& arg,const int& pow)  //a.apply(f,a)
{
	arg = (int)std::pow(arg,pow);
}

void fill_matrix(Numeric_lib::Matrix<int, 2>& m)
{
	for (int i = 0; i < m.dim1(); i++)
		for (int j = 0; j < m.dim2(); j++)
			m[i][j] = i + j;
}

void task1()
{
	Numeric_lib::Matrix<int, 2> m(3, 3);
	fill_matrix(m);
	std::cout << m;
	m.apply(Tripple());
	std::cout << m;
	m.apply(tripple, 3);
	std::cout << m;
	m.apply([](int& arg) {arg = arg * arg * arg; });
	std::cout << m;
}



//Matrix: n[][]*m[]
Numeric_lib::Matrix<double,2> operator*(const Numeric_lib::Matrix<double,2>& mtrx, const Numeric_lib::Matrix<double>& vec)
{
	if (mtrx.dim2() != vec.dim1())throw std::runtime_error("Wrong matrix sizes");
	Numeric_lib::Matrix<double, 2> result=mtrx;
	for (int i = 0; i < result.dim1(); i++)
		for(int j=0;j<result.dim2();j++)
			result[i][j] *= vec[j];
	return result;
}

//Matrix: n+m
template <int N>
Numeric_lib::Matrix<double,N> operator+(const Numeric_lib::Matrix<double, N>& left, const Numeric_lib::Matrix<double, N>& right)
{
	if(left.size()!=right.size()) throw std::runtime_error("Wrong matrix sizes");
	Numeric_lib::Matrix<double, N> result=left;
	const double* ptrRight = right.data();
	double* ptrResult = result.data();
	for (int i = 0; i < result.size(); i++, ptrRight++, ptrResult++)
		*ptrResult +=  (*ptrRight);
	return result;
}

void fill(Numeric_lib::Matrix<double, 2>& n) 
{
	for (int i = 0; i < n.dim1(); i++)
		for (int j = 0; j < n.dim2(); j++)
			n[i][j] = i + j;
}

void task12() //Matrix: n[][]*m[], n+m
{
	Numeric_lib::Matrix<double> vec(3);
	vec[0] = 1; 
	vec[1] = 2; 
	vec[2] = 3;
	Numeric_lib::Matrix<double, 2> n(2, 3);
	fill(n);
	std::cout << n << std::endl << "Multiply" << std::endl 
		<< vec << std::endl << "Result:" << std::endl << n * vec;

	std::cout << "n=" << std::endl << n << std::endl 
		<< "n+n+n=" << std::endl << n + n + n;
}



void task6() //random
{
	int d, n;
	std::cout << "Input two integer values" << std::endl;
	std::cin >> n >> d;
	std::vector<int> vec(n + 1);
	std::default_random_engine ran;
	for (int i = 0; i < d; i++)
		vec[std::uniform_int_distribution<>{ 0, n }(ran)] ++;
	for (unsigned int i = 0; i < vec.size(); i++)
		std::cout << i << ":" << vec[i] << std::endl;
}



int main()
{	
	try
	{
		task1();
		task6();
		task12();
	}
	catch (const std::exception& e)
	{
		std::cout << "Exception:" << e.what();
	}
	return 0;
}

