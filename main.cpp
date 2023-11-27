#include "GaussianElimination.h"

using namespace std;

int main()
{
	Matrix* matrixptr = loadMatrixFromFile("input.txt");
	if (!matrixptr) return -1;
	Matrix& matrix = *matrixptr;

	cout << "Initial matrix:\n";
	printMatrix(matrix);

	double* solution = GaussianElimination(matrix);

	cout << "After elimination:\n";
	printMatrix(matrix);

	cout << "Solution:\n";
	for (int i = 0; i < matrix.getheight(); i++) {
		cout << solution[i] << ", ";
	}
	cout << endl;

	delete[] solution;
	delete matrixptr;

	return 0;
}