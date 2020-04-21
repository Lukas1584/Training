#include<iostream>
#include<random>
#include<chrono>
#include<algorithm>
#include<array>
#include<list>
#include<set>
const int LITTLE = 50000;
const int BIG = 500000;

template <typename Iter>
void fill(Iter begin,Iter end)
{
	std::default_random_engine ran;
	for (auto i = begin; i != end; i++)
	{
		double n = std::uniform_real_distribution<>{ 0, 1.0 }(ran);
		*i = n;
	}
}

template <typename Iter>
void print(Iter begin, Iter end)
{
	for (auto i = begin; i != end; i++)
		std::cout << *i << std::endl;
}

void task12()
{
	std::vector<double> vec_little(LITTLE);
	std::vector<double> vec_big(BIG);
	std::list<double> list_little(LITTLE);
	std::list<double> list_big(BIG);
	fill(vec_little.begin(), vec_little.end());
	fill(vec_big.begin(), vec_big.end());
	fill(list_little.begin(), list_little.end());
	fill(list_big.begin(), list_big.end());
	auto start_t = std::chrono::system_clock::now();
	std::sort(vec_little.begin(), vec_little.end());
	auto vec_little_t = std::chrono::system_clock::now();
	std::sort(vec_big.begin(), vec_big.end());
	auto vec_big_t = std::chrono::system_clock::now();
	list_little.sort();
	auto list_little_t = std::chrono::system_clock::now();
	list_big.sort();
	auto list_big_t = std::chrono::system_clock::now();
	std::cout << "Little vector double sort time: " << std::chrono::duration_cast<std::chrono::milliseconds>(vec_little_t - start_t).count() << std::endl;
	std::cout << "Big vector double sort time: " << std::chrono::duration_cast<std::chrono::milliseconds>(vec_big_t - vec_little_t).count() << std::endl;
	std::cout << "Little list double sort time: " << std::chrono::duration_cast<std::chrono::milliseconds>(list_little_t - vec_big_t).count() << std::endl;
	std::cout << "Big list double sort time: " << std::chrono::duration_cast<std::chrono::milliseconds>(list_big_t - list_little_t).count() << std::endl;
}

template <typename Iter>
void fill_vec_string(Iter begin, Iter end)
{
	std::default_random_engine ran;
	for (auto i = begin; i != end; i++)
	{
		int n = std::uniform_int_distribution<>{ 0, 100 }(ran);   //string lenght = 0...100
		for (int k = 0; k < n; k++)
		{
			char ch = std::uniform_int_distribution<>{ 97, 122 }(ran);   // letters a...z
			*i += ch;
		}
	}
}

void task13()
{
	std::vector<std::string> vec_little(LITTLE);
	std::vector<std::string> vec_big(BIG);
	std::list<std::string> list_little(LITTLE);
	std::list<std::string> list_big(BIG);
	fill_vec_string(vec_little.begin(), vec_little.end());
	fill_vec_string(vec_big.begin(), vec_big.end());
	fill_vec_string(list_little.begin(), list_little.end());
	fill_vec_string(list_big.begin(), list_big.end());
	auto start_t = std::chrono::system_clock::now();
	std::sort(vec_little.begin(), vec_little.end());
	auto vec_little_t = std::chrono::system_clock::now();
	std::sort(vec_big.begin(), vec_big.end());
	auto vec_big_t = std::chrono::system_clock::now();
	list_little.sort();
	auto list_little_t = std::chrono::system_clock::now();
	list_big.sort();
	auto list_big_t = std::chrono::system_clock::now();
	std::cout << "Little vector string sort time: " << std::chrono::duration_cast<std::chrono::milliseconds>(vec_little_t - start_t).count() << std::endl;
	std::cout << "Big vector string sort time: " << std::chrono::duration_cast<std::chrono::milliseconds>(vec_big_t - vec_little_t).count() << std::endl;
	std::cout << "Little list string sort time: " << std::chrono::duration_cast<std::chrono::milliseconds>(list_little_t - vec_big_t).count() << std::endl;
	std::cout << "Big list string sort time: " << std::chrono::duration_cast<std::chrono::milliseconds>(list_big_t - list_little_t).count() << std::endl;
}


void fill_set_string(std::multiset<std::string>& set, const int& size, const std::string& name)
{
	std::vector<std::string> temp;
	std::default_random_engine ran;
	for (int i = 0; i < size; i++)
	{
		int n = std::uniform_int_distribution<>{ 0, 100 }(ran);   //string lenght = 0...100
		std::string s;
		for (int k = 0; k < n; k++)
		{
			char ch = std::uniform_int_distribution<>{ 97, 122 }(ran);  // letters a...z
			s+= ch;
		}
		temp.push_back(s);
	}
	auto start_t = std::chrono::system_clock::now();
	for (int i = 0; i < size; i++)
		set.insert(temp[i]);
	auto set_end = std::chrono::system_clock::now();
	std::cout << name << " set string time: " << std::chrono::duration_cast<std::chrono::milliseconds>(set_end - start_t).count() << std::endl;
}

void task14()
{
	std::multiset<std::string> set_little;
	std::multiset<std::string> set_big;
	fill_set_string(set_little, LITTLE, "Little");
	fill_set_string(set_big, BIG, "Big");
}

int main()
{
	task12();
	task13();
	task14();
	return 0;
}