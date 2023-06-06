/*

Classified as "Algorithm/Data Stucture" --> "Inefficient Algorithm"
              "Micro-Architectural" --> "Data Locality"
              "Missing Parallelization" --> "Vector Parallelism"

*/

#include <iostream>
#include <vector>
#include <random>
#include <omp.h>

using namespace std;

vector<vector<double>> matrixMatrixMultiplication(vector<vector<double>>& matrix1, vector<vector<double>>& matrix2) {
    int matrix1Rows = matrix1.size();
    int matrix1Columns = matrix1[0].size();
    int matrix2Rows = matrix2.size();
    int matrix2Columns = matrix2[0].size();

    vector<vector<double>> result(matrix1Rows, vector<double>(matrix2Columns, 0));

    for (int i = 0; i < matrix1Rows; i++) {
        for (int j = 0; j < matrix2Columns; j++) {
            for (int k = 0; k < matrix1Columns; k++) {
                result[i][j] += matrix1[i][k] * matrix2[k][j];
            }
        }
    }

    return result;
}

int main(int argc, char* argv[]) {

    int size = atoi(argv[1]);

    double lower_bound = 0;
    double upper_bound = 100;
    uniform_real_distribution<double> unif(lower_bound,
                                           upper_bound);
    default_random_engine re;

    vector<vector<double>> matrix1(size, vector<double>(size, 0));
    vector<vector<double>> matrix2(size, vector<double>(size, 0));

    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            double r = unif(re);
            matrix1[i][j] = r;
            r = unif(re);
            matrix2[i][j] = r;
        }
    }
    double s = omp_get_wtime();
    vector<vector<double>> result = matrixMatrixMultiplication(matrix1, matrix2);
    double e = omp_get_wtime();
    cout << "Result: " << endl;
    for (const auto& row : result) {
        for (double val : row) {
            cout << val << " ";
        }
        cout << endl;
    }
    cout << "Time: " << e - s << endl;

    return 0;
}
