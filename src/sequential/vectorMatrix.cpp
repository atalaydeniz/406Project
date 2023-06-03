#include <iostream>
#include <vector>
#include <omp.h>

using namespace std;

vector<int> matrixVectorMultiplication(vector<vector<int>> matrix, vector<int> vector) {
    int matrixRows = matrix.size();
    int matrixColumns = matrix[0].size();
    int vectorSize = vector.size();

    vector<int> result(matrixRows, 0.0);
    for (int i = 0; i < matrixRows; i++) {
        for (int j = 0; j < matrixColumns; j++) {
            result[i] += matrix[i][j] * vector[j];
        }
    }

    return result;
}

int main() {
    vector<vector<int>> matrix = {{1, 2, 3}, {4, 5, 6}};
    vector<int> vector = {1, 2, 3};
    double s = omp_get_wtime();
    vector<int> result = matrixVectorMultiplication(matrix, vector);
    double e = omp_get_wtime();
    cout << e - s;
    cout << "Result: ";
    for (int val : result) {
        cout << val << " ";
    }
    cout << endl;

    return 0;
}
