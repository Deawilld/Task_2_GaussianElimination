#pragma once

#include "Matrix.h"

const int GAUSS_SUCCESS = 0;
const int GAUSS_NO_SOLS = -1;
const int GAUSS_INFINITE_SOLS = -2;
const int GAUSS_UNKNOWN = -3;

int GaussianElimination(Matrix &matrix, double* solution_ptr);

void printMatrix(Matrix& matrix);

Matrix* loadMatrixFromFile(const char* filename);