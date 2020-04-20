#include<iostream>
#include<vector>
#include<string>
#include<iterator>
#include<fstream>

template <typename Iter,typename T>
bool binary_search(Iter begin,Iter end,const T& value)
{
	Iter result;
	while (true)
	{
        if (begin == end) return false;
        result = begin + (end - begin) / 2;
		if (*result == value) return true;
		if (*result > value)
		{
			if (result == end)
				return false;
			end = result;
		}
		else
		{
			if (result == begin)
				return false;
			begin = result;
		}
	}
}

template <typename Iter, typename T, typename Compare>
bool binary_search(Iter begin, Iter end, const T& value, Compare comp)
{
    Iter result;
    while (true)
    {
        if (begin == end) return false;
        result = begin + (end - begin) / 2;
        if (*result == value) return true;
        if (comp(value, *result))
        {
            if (result == end)
                return false;
            end = result;
        }
        else
        {
            if (result == begin)
                return false;
            begin = result;
        }
    }
}

template<typename T>
struct Test
{
	std::string label;
	T val;
    std::vector<T> seq;
	bool res;
};

template<typename T>
std::istream& operator>>(std::istream& is, Test<T>& t)
{
    std::string a, b;
    if (is >> a >> t.label >> t.val >> b && (a != "{" || b != "{"))
    {
        std::cerr << "ERROR: Invalid test file format" << std::endl;
        return is;
    }
    t.seq.clear();
    char ch;
    while (is.get(ch))
    {
        if (ch == ' ')
            is.get(ch);
        if (ch == '}')
        {
            is.unget();
            break;
        }
        else
        {
            is.unget();
            T value;
            is >> value;
            t.seq.push_back(value);
        }
    }
    is.clear();
    std::string c, d;
    int res = 0;
    if (is >> c >> res >> d && (c != "}" || d != "}"))
    {
        std::cerr << "ERROR: Invalid test file format" << std::endl;
        return is;
    }
    t.res = res;
    return is;
}

template<typename T>
std::ostream& operator<<(std::ostream& os, const Test<T>& t)
{
    os << "{ " << t.label << ' ' << t.val << " { ";
    std::copy(t.seq.begin(), t.seq.end(), std::ostream_iterator<T>(os, " "));
    return os << "} " << t.res << " }";
}

template<typename T>
int test_all(const std::string& s)
{
    int error_count = 0;
    Test<T> t;
    std::ifstream is(s);
    if (!is) std::cerr<<"ERROR: File doesn't exist!";
    while (is >> t) {
        std::cout << t << std::endl;
        bool r = binary_search(t.seq.begin(), t.seq.end(), t.val);
        if (r != t.res) {
            std::cout << "failure: test " << t.label
                << " binary_search: "
                << t.seq.size() << " elements, v==" << t.val
                << " -> " << t.res << '\n';
            ++error_count;
        }
    }
    return error_count;
}

template<typename T,typename Compare>
int test_all(const std::string& s,Compare comp)
{
    int error_count = 0;
    Test<T> t;
    std::ifstream is(s);
    if (!is) std::cerr << "ERROR: File doesn't exist!";
    while (is >> t) {
        std::cout << t << std::endl;
        bool r = binary_search(t.seq.begin(), t.seq.end(), t.val, comp);
        if (r != t.res) {
            std::cout << "failure: test " << t.label
                << " binary_search: "
                << t.seq.size() << " elements, v==" << t.val
                << " -> " << t.res << '\n';
            ++error_count;
        }
    }
    return error_count;
}

int main()
{
    int errors_int = test_all<int>("test_int.txt");
    std::cout << "number of errors: " << errors_int << "\n";
    int errors_double = test_all<double>("test_double.txt");
    std::cout << "number of errors: " << errors_double << "\n";
    int errors_string = test_all<std::string>("test_string.txt");
    std::cout << "number of errors: " << errors_string << "\n";
    int errors_char = test_all<char>("test_char.txt");
    std::cout << "number of errors: " << errors_char << "\n";
    int errors_int_comp = test_all<int>("test_int_comp.txt", [](const int& a,const int& b) {return a > b; });
    std::cout << "number of errors: " << errors_int_comp << "\n";
    int errors_double_comp = test_all<double>("test_double_comp.txt", [](const double& a, const double& b) {return a > 2*b; });
    std::cout << "number of errors: " << errors_double_comp << "\n";
    return 0;
}