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
    int blockSize = 32; // Adjust the block size as needed

    vector<vector<double>> result(matrix1Rows, vector<double>(matrix2Columns, 0));

    #pragma omp parallel for collapse(2)
    for (int i = 0; i < matrix1Rows; i += blockSize) {
        for (int j = 0; j < matrix2Columns; j += blockSize) {
            for (int k = 0; k < matrix1Columns; k += blockSize) {
                for (int ii = i; ii < min(i + blockSize, matrix1Rows); ii++) {
                    for (int jj = j; jj < min(j + blockSize, matrix2Columns); jj++) {
                        double sum = 0;
                        for (int kk = k; kk < min(k + blockSize, matrix1Columns); kk++) {
                            sum += matrix1[ii][kk] * matrix2[kk][jj];
                        }
                        result[ii][jj] += sum;
                    }
                }
            }
        }
    }

    return result;
}

int main() {
    double lower_bound = 0;
    double upper_bound = 100;
    uniform_real_distribution<double> unif(lower_bound, upper_bound);
    default_random_engine re;

    vector<vector<double>> matrix1(1024, vector<double>(1024, 0));
    vector<vector<double>> matrix2(1024, vector<double>(1024, 0));

    #pragma omp parallel for collapse(2)
    for (int i = 0; i < 1024; i++) {
        for (int j = 0; j < 1024; j++) {
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
