#pragma once

#include <stdexcept>
#include <iostream>
#pragma hdrstop

class Matrix {
private:
	double* A;
	int height;
	int width;

public:	

	Matrix(int n = 0);

	~Matrix();

	inline double& at(unsigned int row, unsigned int column) {
#ifdef _DEBUG
		if (row >= height || column >= width) {
			throw std::out_of_range("Tried to access a non-existing element of the matrix");
		}
#endif

		return A[row * width + column];
	}

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