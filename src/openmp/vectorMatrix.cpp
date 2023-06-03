#include <iostream>
#include <vector>
#include <omp.h>

std::vector<int> matrixVectorMultiplication_parallel(const std::vector<std::vector<int>>& matrix, const std::vector<int>& vector) {
    size_t matrixRows = matrix.size();
    size_t matrixColumns = matrix[0].size();
    size_t vectorSize = vector.size();

    if (matrixColumns != vectorSize) {
        std::cout << "Error: Matrix columns and vector size must match." << std::endl;
        return std::vector<int>();
    }

    std::vector<int> result(matrixRows, 0);

    #pragma omp parallel for
    for (size_t i = 0; i < matrixRows; i++) {
        for (size_t j = 0; j < matrixColumns; j++) {
            result[i] += matrix[i][j] * vector[j];
        }
    }

    return result;
}

int main() {
    std::vector<std::vector<int>> matrix = {{1, 2, 3}, {4, 5, 6}};
    std::vector<int> vector = {1, 2, 3};

    std::vector<int> result = matrixVectorMultiplication_parallel(matrix, vector);

    std::cout << "Result: ";
    for (int val : result) {
        std::cout << val << " ";
    }
    std::cout << std::endl;

    return 0;
}
