#pragma once
#include<iostream>


template<typename T, int N>
class Vector
{
	T* elem;
	int sz;
public:
	Vector() :sz(0), elem(new T[N])	{}
	Vector(std::initializer_list<T>);
	Vector(const Vector<T, N>&);
	Vector(Vector<T, N>&&);
	~Vector() {	delete[] elem;	}

	Vector<T, N>& operator=(const Vector<T, N>&);
	Vector<T, N>& operator=(Vector<T, N>&&);
	
	void push_back(const T&);
	void erase(int i);
	int size()const { return sz;	}
	T& operator[](const int&);
	int available() const {	return N - sz;	}
	
};

