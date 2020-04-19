#include<iostream>
#include<vector>
#include<string>
#include <iterator>
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

//Testing. From the book
struct Test
{
	std::string label;
	int val;
	std::vector<int> seq;
	bool res;
};

std::istream& operator>>(std::istream& is, Test& t)
{
    std::string a, b;
    if (is >> a >> t.label >> t.val >> b && (a != "{" || b != "{"))
    {
        std::cerr << "ERROR: Invalid test file format" << std::endl;
        return is;
    }
    t.seq.clear();
    std::copy(
        std::istream_iterator<int>(is),
        std::istream_iterator<int>(),
        std::back_inserter(t.seq)
    );
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

std::ostream& operator<<(std::ostream& os, const Test& t)
{
    os << "{ " << t.label << ' ' << t.val << " { ";
    std::copy(t.seq.begin(), t.seq.end(), std::ostream_iterator<int>(os, " "));
    return os << "} " << t.res << " }";
}

int test_all()
{
    int error_count = 0;
    Test t;
    std::ifstream is("test.txt");
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

int main()
{
    int errors = test_all();
    std::cout << "number of errors: " << errors << "\n";
    return 0;
}