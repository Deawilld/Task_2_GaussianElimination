#pragma once

#include "Matrix.h"

double* GaussianElimination(Matrix &matrix);

void printMatrix(Matrix& matrix);

Matrix* loadMatrixFromFile(const char* filename);