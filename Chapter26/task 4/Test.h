#pragma once

template<typename T>
struct Test
{
	void testing(const std::string& name);
private:	
	void print_result();
	void read_from_file(const std::string& name);
	void read(std::istream& os);
	std::vector< std::pair<T, bool> > val;
	std::vector<T> seq;
	std::vector<std::string> results;
};

template<typename T>
void Test<T>::read_from_file(const std::string& name)
{
	std::ifstream ifs(name);
	read(ifs);
}

template<typename T>
void Test<T>::read(std::istream& is)
{
	std::string buf;
	std::getline(is, buf);
	std::stringstream ss;
	ss << buf;
	T value;
	while (ss >> value)
		seq.push_back(value);
	ss.clear();
	while (std::getline(is, buf))
	{
		ss << buf;
		T first;
		bool last;
		ss >> first >> last;
		val.push_back({ first,last });
		ss.clear();
	}
}

template<typename T>
void Test<T>::print_result()
{
	for (size_t i=0; i<val.size(); i++)
	{
		for (auto k : seq)
			std::cout << k << " ";
		std::cout <<"Looking for: "<<val[i].first << " Expected:" << val[i].second << " Result:"<< results[i]<< std::endl;
	}
}

template <typename Iter, typename T>
bool binary_search(Iter begin, Iter end, const T& value)
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

template<typename T>
void Test<T>::testing(const std::string& name)
{
	read_from_file(name);
	for (auto i : val)
	{
		if (i.second == binary_search(seq.begin(), seq.end(), i.first))
			results.push_back("Good");
		else 
			results.push_back("!!!Error!!!");
	}
	print_result();
}

