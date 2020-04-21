#include<iostream>
#include<vector>
#include<fstream>
#include<sstream>
#include<utility>
#include "Test.h"

int main()
{
	Test<int> a;
	a.testing("test_int.txt");
	Test<double> b;
	b.testing("test_double.txt");
	Test<std::string> c;
	c.testing("test_string.txt");
	return 0;
}