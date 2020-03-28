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
T task2(const std::vector<T>& vt, const std::vector<U>& vu)
{
	T res = 0;
	if (vt.size() != vu.size()) throw std::runtime_error("vector sizes are not equal");
	for (int i = 0; i < vt.size(); i++)
		res = res + vt.at(i) * vu.at(i);
	return res;
}

class Int
{
	int value;
public:
	Int():value(0) {}
	Int(const int& i) : value(i) {}
	Int(const Int& i) : value(i.get()) {}
	
	int get() const { return value; }
	void set(const int& i) { value = i; }
	
	void operator=(const int&& i) { value = i; }
	void operator=(const Int& i) { value = i.get(); }
		
	Int operator+(const Int& right)	{ return Int(value + right.get());}
	Int operator-(const Int& right) { return Int(value - right.get()); }
	Int operator*(const Int& right) { return Int(value * right.get()); }
	Int operator/(const Int& right) { if (right.get()!=0) return Int(value / (right.get())); }
};

std::ostream& operator <<(std::ostream& left, const Int& right)
{
	left << right.get() << std::endl;
	return left;
}

std::istream& operator>>(std::istream& left, Int& right)
{
	int temp = 0;
	left >> temp;
	right.set(temp);
	return left;
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
		std::vector<std::string> tmp5{ "Hello, ", "To be " , "Blah "};
		std::vector<std::string> tmp6{ "World!", "or not to be.", "blah" };
		f(tmp5, tmp6);
		print(tmp5);
		std::cout << task2(tmp3, tmp2) << std::endl;
		
		Int a(10), b, c, d, e, f;
		b = 5;
		c = a + b;
		d = a - b;
		e = d + a * b;
		f = a / b;
		std::cout << a << b << c << d << e << f;
		std::cout << "Input two values" << std::endl;
		std::cin >> a >> b;
		std::cout << a << b;
		std::vector <Int> t { a,b,c,d,e,f };
		std::vector <int> u { 1,2,3,4,5,6 };
		std::vector <Int> t2{ f,e,d,c,b,a };
		//std::cout << task2(t, t2);
		
	}
	catch (const std::exception & e) 
	{
		std::cout << " a standard exception was caught, with message '"
			<< e.what() << "'\n";
	}

}

