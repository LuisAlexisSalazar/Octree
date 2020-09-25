#pragma once
#include<iostream>

using namespace std;

template<typename T>
class CPunto
{
public:
	T x;
	T y;
	T z;


	CPunto() {
		this->x = -1;
		this->y = -1;
		this->z = -1;
	}


	CPunto(T x, T y, T z) {
		this->x = x;
		this->y = y;
		this->z = z;
	}


	

	friend istream& operator>>(istream& is, CPunto<T>& punto) {
		is >> punto.x >> punto.y >> punto.z;
		return is;
	}
	

};

