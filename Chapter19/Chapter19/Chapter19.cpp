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
concept amount_multiplication =
requires(T t, U u)
{
	t* u + t * u;
};

template <typename T, typename U>
requires amount_multiplication <T,U>
double task2(const std::vector<T>& vt, const std::vector<U>& vu)
{
	double res = 0;
	if (vt.size() != vu.size()) throw std::runtime_error("vector sizes are not equal");
	for (int i = 0; i < vt.size(); i++)
		res += vt.at(i) * vu.at(i);
	return res;
}

/*
class Int
{
	int i;
public:
	Int():i(0) {}
	Int(int& ii) : i(ii) {}
	Int(const int& ii) : i(ii) {}
	Int(Int& ii) : i(ii.get()) {}
	int get() const { return i; }
	void set(int ii) { i = ii; }
	void operator=(const int& ii) { i = ii; }
	void operator=(const Int& ii) { i = ii.get(); }
	//Int operator+(int& ii) { return Int (i+ii);}
	int operator+(const Int& ii) { return i + ii.get(); }
	int operator-(const int& ii) { return i - ii; }
	int operator-(const Int& ii) { return i - ii.get(); }
	int operator*(const int& ii) { return i * ii; }
	int operator*(const Int& ii) { return i * ii.get(); }
	int operator/(const int& ii) { if(!ii) return i + ii; }
	int operator/(const Int& ii) { if (!ii.get()) return i + ii.get(); }
	friend std::ostream& operator<<(std::ostream& os, Int ii);
};
std::ostream& operator <<(std::ostream& os, Int ii)
{
	os << ii.get() << std::endl;
	return os;
}
*/



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
		std::vector<std::string> tmp5{ "Hello, ", "To be " , "Blah "};
		std::vector<std::string> tmp6{ "World!", "or not to be.", "blah" };
		//f(tmp5, tmp6);
		print(tmp5);
		std::cout << task2(tmp2, tmp3) << std::endl;
		std::cout << task2(tmp5, tmp6) << std::endl;
		/*Int a;
		std::cout << a;
		a = 3;
		std::cout << a;
		Int b(a);
		std::cout << b;
		Int c;
		c= a + b;
		std::cout << c;
		*/
	}
	catch (const std::exception & e) 
	{
		std::cout << " a standard exception was caught, with message '"
			<< e.what() << "'\n";
	}

}

