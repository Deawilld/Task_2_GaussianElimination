#include <chrono>
#define _USE_MATH_DEFINES
#include <math.h>
#pragma hdrstop
#include "GaussianElimination.h"
#include "RandomDouble.h"

using namespace std;

void mult(Matrix& A, double* x);
void fillRandomMatrix(Matrix& A, RandomDouble& rnd);
void fillRandomArray(double* x, size_t n, RandomDouble& rnd);

void runGauusian()
{
	Matrix* matrixptr = loadMatrixFromFile("input.txt");
	if (!matrixptr) return;
	Matrix& matrix = *matrixptr;

	cout << "Initial matrix:\n";
	printMatrix(matrix);

	double* solution = new double[matrix.getheight()];
	int status = GaussianElimination(matrix, solution);

	cout << "After elimination:\n";
	printMatrix(matrix);

	if (status == GAUSS_SUCCESS) {
		cout << "Solution:\n";
		for (int i = 0; i < matrix.getheight(); i++) {
			cout << solution[i] << ", ";
		}
		cout << endl;
	}
	else if (status == GAUSS_NO_SOLS) {
		cout << "No solutions: the system is inconsistent\n";
	}
	else if (status == GAUSS_INFINITE_SOLS) {
		cout << "No unique solution: the system is linearly dependent";
	}

	delete[] solution;
	delete matrixptr;
}

void runAccuracyTest(const size_t n) {
	Matrix matrix(n);

	RandomDouble rnd(123456789);

	fillRandomMatrix(matrix, rnd);

	double* x = new double[n];
	fillRandomArray(x, n, rnd);

	mult(matrix, x);

	if (n < 50) {
		cout << "Generated matrix:\n";
		printMatrix(matrix);
	}

	double* solution = new double[n];
	chrono::time_point timer_start = chrono::high_resolution_clock::now();
	int status = GaussianElimination(matrix, solution);
	chrono::time_point timer_end = chrono::high_resolution_clock::now();

	if (n < 50) {
		cout << "\nTriangulated matrix:\n";
		printMatrix(matrix);

		cout << "\nExpected solution:\n";
		for (int i = 0; i < n; i++) {
			cout << x[i] << " ";
		}
		cout << "\nComputed solution:\n";
		for (int i = 0; i < n; i++) {
			cout << solution[i] << " ";
		}
		cout << "\n";
	}

	cout << "Size: " << n << "\n";

	cout << "Status: ";
	switch (status) {
	case GAUSS_SUCCESS:
		cout << "SUCCESS";
		break;
	case GAUSS_INFINITE_SOLS:
		cout << "INFINITE";
		break;
	case GAUSS_NO_SOLS:
		cout << "NO_SOLS";
		break;
	}
	cout << "\n";

	double* difference_abs = x;

	//double square_sum = 0;
	double abs_sum = 0;
	double max_diff = 0;

	for (int i = 0; i < n; i++) {
		difference_abs[i] = abs(x[i] - solution[i]);

		//square_sum += difference_abs[i] * difference_abs[i];
		abs_sum += difference_abs[i];
		max_diff = std::max(max_diff, difference_abs[i]);
	}
	
	cout << "Average absolute difference: " << abs_sum / n;
	cout << "\nMaximum difference: " << max_diff;
	cout << "\nTime taken: " << chrono::duration_cast<chrono::nanoseconds>(timer_end - timer_start).count() / 1000.0 << " us\n";
}

int main() {
	int n;
	cout << "Test n: \n";
	cin >> n;
	runAccuracyTest(n);
	return 0;
}

void mult(Matrix& A, double* x) {
	for (int i = 0; i < A.getheight(); i++) {
		double sum = 0;
		for (int j = 0; j < A.getheight(); j++) {
			sum += A.at(i, j) * x[j];
		}
		A.at(i, A.getheight()) = sum;
	}
}

void fillRandomMatrix(Matrix& A, RandomDouble& gen) {
	for (int i = 0; i < A.getheight(); i++) {
		for (int j = 0; j < A.getheight(); j++) {
			A.at(i, j) = gen.nextlognormsigned() * M_E;
		}
	}
}

void fillRandomArray(double* x, size_t n, RandomDouble& gen) {
	for (int i = 0; i < n; i++) {
		x[i] = gen.nextlognormsigned();
	}
}