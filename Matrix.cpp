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

double& Matrix::at(unsigned int row, unsigned int column) {
#ifdef _DEBUG
	if (row >= height || column >= width) {
		throw std::out_of_range("Tried to access a non-existing element of the matrix");
	}
#endif

	return A[row * width + column];
}