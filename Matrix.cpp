#include "Matrix.h"

Matrix::Matrix(int n) {
	height = n;
	width = n + 1;
	if (n) {
		A = new double[n * width];
	}
	else {
		A = nullptr;
	}
}

Matrix::~Matrix() {
	if (A) {
		delete[] A;
	}
}