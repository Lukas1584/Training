#include<iostream>
#include<vector>
#include<random>
#include<chrono>
#include<memory>
#include<algorithm>

const int MAX = 10000;
std::vector<int> rand_bite(MAX);
std::vector<int> rand_order(MAX);

struct Soo
{
	int a[125];
};

void fill_rand_bite()
{
	std::default_random_engine ran;
	for (int count = 0; count < rand_bite.size(); count++)
		rand_bite[count]=(std::uniform_int_distribution<>{ 0, 250 }(ran));
}

void fill_rand_order()
{
	std::default_random_engine ran;
	for (int count = 0; count < rand_order.size(); count++)
	{
		int n = std::uniform_int_distribution<>{ 0, MAX }(ran);
		if (!(std::binary_search(rand_order.begin(), rand_order.end(), n)))
			rand_order[count]=n;
	}
}

void random()
{
	int* a[MAX];
	auto t1 = std::chrono::system_clock::now();
	for (int count = 0; count < MAX; count++ )
	{
		a[count] = new int(rand_bite[count] * sizeof(int));
	}
	auto t2 = std::chrono::system_clock::now();
	std::cout << "1 - in order, 2 - random" << std::endl;
	char choice = 0;
	std::cin >> choice;

	auto t3 = std::chrono::system_clock::now();
	if (choice == '1')
		for (int i = MAX - 1; i >= 0; i--)
			delete a[i];
	if (choice == '2')
	{
		for (int count = MAX-1; count >= 0; )
		{
			delete a[rand_order[count]];
			a[rand_order[count]] = nullptr;
			count--;
		}
	}
	auto t4 = std::chrono::system_clock::now();
	std::cout << "Created: " << std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count() << std::endl;
	std::cout << "Deleted: " << std::chrono::duration_cast<std::chrono::milliseconds>(t4 - t3).count() << std::endl;
}

void pool()
{
	Soo* b[MAX];
	auto t1 = std::chrono::system_clock::now();
	for (int i = 0; i < MAX; i++)
		b[i] = new Soo;
	auto t2 = std::chrono::system_clock::now();
	std::cout << "1 - in order, 2 - random" << std::endl;
	char choice = 0;
	std::cin >> choice;
	auto t3 = std::chrono::system_clock::now();
	
	if (choice == '1')
		for (int i = MAX - 1; i >= 0; i--)
			delete b[i];
	
	if (choice == '2')
	{
		for (int count = MAX - 1; count >= 0; )
		{
			delete b[rand_order[count]];
			b[rand_order[count]] = nullptr;
			count--;
		}
	}
	auto t4 = std::chrono::system_clock::now();
	std::cout << "Created: " << std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count() << std::endl;
	std::cout << "Deleted: " << std::chrono::duration_cast<std::chrono::milliseconds>(t4 - t3).count() << std::endl;

}

void stack(int count)
{
	Soo a;
	count--;
	if (count == 0)
		return;
	stack(count);
}

void stack()
{
	auto t1 = std::chrono::system_clock::now();
	stack(1250);
	auto t2 = std::chrono::system_clock::now();
	std::cout << "Created & deleted 1250*500bit: " << std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count() << std::endl;
}

void vector()
{
	Soo a;
	std::vector<Soo> vec;
	auto t1 = std::chrono::system_clock::now();
	vec.reserve(MAX);
	for (int i = 0; i < MAX; i++)
		vec.push_back(a);
	auto t2 = std::chrono::system_clock::now();
	for (int i = MAX; i > 0; i--)
		vec.erase(vec.end()-1);
	   //vec.erase(vec.begin());
	auto t3 = std::chrono::system_clock::now();
	std::cout << "Created: " << std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count() << std::endl;
	std::cout << "Erased: " << std::chrono::duration_cast<std::chrono::milliseconds>(t3 - t2).count() << std::endl;
}

void pointer()
{
	std::unique_ptr<Soo> arr[MAX];
	auto t1 = std::chrono::system_clock::now();
	for (int count = 0; count < MAX; count++)
		arr[count] = std::unique_ptr<Soo>(new Soo);
	auto t2 = std::chrono::system_clock::now();
	
	for (int count = MAX - 1; count >= 0; count--)
		arr[count].release();
	auto t3 = std::chrono::system_clock::now();
	std::cout << "Created: " << std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count() << std::endl;
	std::cout << "Deleted: " << std::chrono::duration_cast<std::chrono::milliseconds>(t3 - t2).count() << std::endl;
}

int main()
{
	fill_rand_bite();
	fill_rand_order();
	std::cout << "1-random, 2-pool, 3 - stack, 4 - vector, 5 - smart pointer" << std::endl;
	char choice=0;
	std::cin >> choice;
	switch (choice)
	{
	case '1':
		random();
		break;
	case'2':
		pool();
		break;
	case '3':
		stack();
		break;
	case'4':
		vector();
		break;
	case '5':
		pointer();
		break;
	default:
		std::cout << "Wrong number";
	}


	
	
	return 0;
}