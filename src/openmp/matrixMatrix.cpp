#include <iostream>
#include <vector>
#include <omp.h>

std::vector<std::vector<int>> matrixMatrixMultiplication_parallel(const std::vector<std::vector<int>>& matrix1, const std::vector<std::vector<int>>& matrix2) {
    size_t matrix1Rows = matrix1.size();
    size_t matrix1Columns = matrix1[0].size();
    size_t matrix2Rows = matrix2.size();
    size_t matrix2Columns = matrix2[0].size();

    if (matrix1Columns != matrix2Rows) {
        std::cout << "Error: Matrix1 columns and Matrix2 rows must match." << std::endl;
        return std::vector<std::vector<int>>();
    }

    std::vector<std::vector<int>> result(matrix1Rows, std::vector<int>(matrix2Columns, 0));

    #pragma omp parallel for
    for (size_t i = 0; i < matrix1Rows; i++) {
        for (size_t j = 0; j < matrix2Columns; j++) {
            for (size_t k = 0; k < matrix1Columns; k++) {
                result[i][j] += matrix1[i][k] * matrix2[k][j];
            }
        }
    }

    return result;
}

int main() {
    std::vector<std::vector<int>> matrix1 = {{1, 2, 3}, {4, 5, 6}};
    std::vector<std::vector<int>> matrix2 = {{7, 8}, {9, 10}, {11, 12}};

    std::vector<std::vector<int>> result = matrixMatrixMultiplication_parallel(matrix1, matrix2);

    std::cout << "Result: " << std::endl;
    for (const auto& row : result) {
        for (int val : row) {
            std::cout << val << " ";
        }
        std::cout << std::endl;
    }

    return 0;
}
