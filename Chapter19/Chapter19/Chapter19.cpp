#include <iostream>
#include <vector>


template <typename T>
void f(std::vector<T>& v1, const std::vector<T>& v2)
{
	if (v1.size() != v2.size()) throw std::runtime_error("vector sizes are not equal");
	for (int i = 0; i < v1.size(); i++)
	{
		v1.at(i) += v2.at(i);
	}
}

template <typename T>
void print(const std::vector<T>& v)
{
	for (int i = 0; i < v.size(); i++)
		std::cout << v.at(i) << std::endl;
}

template <typename T, typename U>
double task2(const std::vector<T>& vt, const std::vector<U>& vu)
{
	double res = 0;
	if (vt.size() != vu.size()) throw std::runtime_error("vector sizes are not equal");
	for (int i = 0; i < vt.size(); i++)
		res += vt.at(i) * vu.at(i);
	return res;
}


int main()
{
	try
	{
		std::vector<int> tmp1{ 1,2,3 };
		std::vector<int> tmp2{ 3,2,1 };
		f(tmp1, tmp2);
		print(tmp1);
		std::vector<double> tmp3{ 1.1,2.2,3.3 };
		std::vector<double> tmp4{ 3.3,2.2,1.1 };
		f(tmp3, tmp4);
		print(tmp3);
		std::vector<std::string> tmp5{ "Hello, ", "To be " };
		std::vector<std::string> tmp6{ "World!", "or not to be." };
		f(tmp5, tmp6);
		print(tmp5);
		std::cout << task2(tmp2, tmp4) << std::endl;
		
	}
	catch (const std::exception & e) 
	{
		std::cout << " a standard exception was caught, with message '"
			<< e.what() << "'\n";
	}

}

