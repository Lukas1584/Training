#include "Vector.h"
#include <algorithm>

template<typename T, int N>
void Vector<T,N>::push_back(const T& arg)
{
	if (sz == N) throw std::runtime_error("Vector is full");
	elem[sz] = arg;
	sz++;
}

template<typename T, int N>
T& Vector<T, N>::operator[](const int& i)
{ 
	if(i<0||i>=sz) throw std::runtime_error("Wrong value of 'i'");
	return elem[i]; 
}

template<typename T, int N>
Vector<T, N>::Vector(const Vector<T, N>& vec)
{
	elem = new T[N];
	for (int i = 0; i < vec.size(); i++)
		elem[i] = vec.elem[i];
	sz = vec.sz;
}

template<typename T, int N>
Vector<T, N>::Vector(Vector<T, N>&& vec)
{
	elem = vec.elem;
	sz = vec.sz;
	vec.elem = nullptr;
	vec.sz = 0;
}

template<typename T, int N>
Vector<T, N>& Vector<T, N>::operator=(const Vector<T, N>& vec)
{
	T* ptr= new T[N];
	for (int i = 0; i < vec.size(); i++)
		ptr[i] = vec.elem[i];
	delete[]elem;
	elem = ptr;
	ptr = nullptr;
	sz = vec.sz;
	return *this;
}

template<typename T, int N>
Vector<T, N>& Vector<T, N>::operator=(Vector<T, N>&& vec)
{
	delete[]elem;
	elem = vec.elem;
	sz = vec.sz;
	vec.elem = nullptr;
	vec.sz = 0;
	return *this;
}

template<typename T, int N>
Vector<T, N>::Vector(std::initializer_list<T> lst)
{
	elem = new T[N];
	sz = static_cast<int>(lst.size());
	std::copy(lst.begin(), lst.end(), elem);
}

template<typename T, int N>
void Vector<T, N>::erase(int k)
{
	if(k<0||sz<=k) throw std::runtime_error("Wrong value of 'i'");
	for (int i = k; i < sz-1; i++)
		elem[i] = elem[i + 1];
	sz--;
}