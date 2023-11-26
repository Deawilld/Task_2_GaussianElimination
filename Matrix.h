#include <stdexcept>
#include <iostream>

#pragma once

class Matrix {
private:
	double* A;
	int height;
	int width;

public:	

	Matrix(int n = 0);

	~Matrix();

	double& at(unsigned int row, unsigned int column);

	//Bounds are not checked in operator[]
	double& operator[](int i) {
		return A[i];
	}

	inline int getwidth() {
		return width;
	}
	inline int getheight() {
		return height;
	}

	inline int totalSize() {
		return width * height;
	}
};