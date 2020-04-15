#include<iostream>
#include "Vector.h"
#include "Vector.cpp"

void task14() //testing Vector
{
	Vector<int,1000> a;
	for (int i=0; i<1000;i++)
		a.push_back(i);
	Vector<int, 1000> b;
	b = a;
	b[555] = 120;
	std::cout << a.size() << std::endl;
	std::cout << a.available() << std::endl;
	std::cout << a[0] << std::endl;
	std::cout << a[555] << std::endl;
	std::cout << a[999] << std::endl;
	std::cout << b.size() << std::endl;
	std::cout << b.available() << std::endl;
	std::cout << b[0] << std::endl;
	std::cout << b[555] << std::endl;
	std::cout << b[999] << std::endl;
	Vector<std::string, 1000> c{ "1","2","3","4","5","6","7","8","9","10","Yo" };
	c.erase(0);
	std::cout << c.size() << std::endl;
	std::cout << c.available() << std::endl;
	std::cout << c[0] << std::endl;
	std::cout << c[5] << std::endl;
	std::cout << c[9] << std::endl; 
}


int main()
{
	try
	{
		task14();
	}
	catch (const std::exception& e)
	{
		std::cout << "Exception: " << e.what();
	}
	return 0;
}