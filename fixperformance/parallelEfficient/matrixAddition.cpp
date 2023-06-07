#include <iostream>
#include <vector>
#include <omp.h>
#include <random>

void matrixAddition(std::vector<std::vector<double>>& matrix1, const std::vector<std::vector<double>>& matrix2) {
    int rows = matrix1.size();
    int cols = matrix1[0].size();

    #pragma omp parallel for
    for (int i = 0; i < rows; i++) {
        #pragma omp simd
        for (int j = 0; j < cols; j++) {
            matrix1[i][j] += matrix2[i][j];
        }
    }
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
    matrixAddition(matrix1, matrix2);
    double e = omp_get_wtime();

    std::cout << e - s << std::endl;


    return 0;
}



