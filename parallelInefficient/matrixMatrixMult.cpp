#include <iostream>
#include <vector>
#include <omp.h>
#include <random>

std::vector<std::vector<int>> matrixMatrixMultiplication(const std::vector<std::vector<int>>& matrix1, const std::vector<std::vector<int>>& matrix2) {
    int matrix1Rows = matrix1.size();
    int matrix1Columns = matrix1[0].size();
    int matrix2Rows = matrix2.size();
    int matrix2Columns = matrix2[0].size();

    std::vector<std::vector<int>> result(matrix1Rows, std::vector<int>(matrix2Columns, 0));

    #pragma omp parallel for
    for (int i = 0; i < matrix1Rows; i++) {
        for (int k = 0; k < matrix1Columns; k++) {
            int matrix1Value = matrix1[i][k];
            for (int j = 0; j < matrix2Columns; j++) {
                int matrix2Value = matrix2[k][j];
                result[i][j] += matrix1Value * matrix2Value;
                __builtin_prefetch(&matrix2[k+1][j], 0, 1);
            }
        }
    }

    return result;
}

int main() {
    double lower_bound = 0;
    double upper_bound = 100;
    std::uniform_real_distribution<double> unif(lower_bound, upper_bound);
    std::default_random_engine re;

    std::vector<std::vector<double>> matrix1(2048, std::vector<double>(2048, 0));
    std::vector<std::vector<double>> matrix2(2048, std::vector<double>(2048, 0));

    #pragma omp parallel for collapse(2)
    for (int i = 0; i < 2048; i++) {
        for (int j = 0; j < 2048; j++) {
            double r = unif(re);
            matrix1[i][j] = r;
            r = unif(re);
            matrix2[i][j] = r;
        }
    }

    double s = omp_get_wtime();
    std::vector<std::vector<double>> result = matrixMatrixMultiplication(matrix1, matrix2);
    double e = omp_get_wtime();

    std::cout << e - s << std::endl;
    return 0;
}

