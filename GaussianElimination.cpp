#include "GaussianElimination.h"
#include "Matrix.h"
#include <iostream>
#include <fstream>

using namespace std;

int GaussianElimination(Matrix& matrix, double* solution_ptr) {
	for (int k = 0; k < matrix.getheight() - 1; k++) { //k - index of the main element along the diagonal

		//If the main element is 0, find another row with a non-zero element on index k
		int mainline = k;
		while (matrix.at(mainline, k) == 0) {
			if (++mainline >= matrix.getheight()) return GAUSS_UNKNOWN; //CHECK IT LATER
		}
		double a1 = matrix.at(mainline, k); //the main element

		//SWAP LINES AND NORMALISE
		for (int i = k; i < matrix.getwidth(); i++) {
			double el = matrix.at(mainline, i);
			if (mainline != k) matrix.at(mainline, i) = matrix.at(k, i);
			matrix.at(k, i) = el / a1;
		}

		for (int row = k + 1; row < matrix.getheight(); row++) {
			double a2 = matrix.at(row, k);
			if (a2 == 0) continue;

			for (int i = k + 1; i < matrix.getwidth(); i++) {

				matrix.at(row, i) = matrix.at(k, i) - matrix.at(row, i) / a2;
			}

			matrix.at(row, k) = 0;
		}
	}

	for (int k = matrix.getheight() - 1; k >= 0; k--) {
		double this_el = matrix.at(k, k);
		double free_el = matrix.at(k, matrix.getwidth() - 1);

		//"moving" known members to the "right side" of the equation and accumulation
		double tmp_sum = free_el;
		for (int i = k + 1; i < matrix.getwidth() - 1; i++) {

			tmp_sum -= matrix.at(k, i) * solution_ptr[i];
		}

		if (this_el == 0) {
			if (tmp_sum == 0) {
				//0*x = 0   infinite solutions
				return GAUSS_INFINITE_SOLS;
			}
			else {
				//0*x = a  no solutions
				return GAUSS_NO_SOLS;
			}
		}

		solution_ptr[k] = tmp_sum / this_el;
	}

	return GAUSS_SUCCESS;
}


void printMatrix(Matrix& matrix) {
	for (int i = 0; i < matrix.getheight(); i++) {
		for (int j = 0; j < matrix.getwidth(); j++) {
			cout << matrix.at(i, j) << " ";
		}
		cout << endl;
	}
}

Matrix* loadMatrixFromFile(const char* filename) {
	ifstream filein("input.txt");
	if (!filein.is_open()) {
		cerr << "Failed to open input file" << endl;
		return nullptr;
	}
	int height = 0;
	filein >> height;

	Matrix* matrix = new Matrix(height);
	
	for (int i = 0; i < matrix->totalSize(); i++) {
		if (filein.eof()) {
			cerr << "Error: end of file!\n";
			delete matrix;
			return nullptr;
		}
		filein >> (*matrix)[i];
		if (filein.fail()) {
			cerr << "Error: failed to read a value!\n";
			delete matrix;
			return nullptr;
		}
	}
	return matrix;
}