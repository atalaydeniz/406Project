/*

Classified as "Inefficient Parallelization" --> "Inefficient Thread Mapping"
              "Micro-Architectural" --> "Data Locality"

*/

#include <iostream>
#include <vector>

__global__ void matrixMatrixMultiplication_cuda(const int* matrix1, const int* matrix2, int* result, int matrix1Rows, int matrix1Columns, int matrix2Columns) {
    int row = blockIdx.y * blockDim.y + threadIdx.y;
    int col = blockIdx.x * blockDim.x + threadIdx.x;

    if (row < matrix1Rows && col < matrix2Columns) {
        int value = 0;
        for (int i = 0; i < matrix1Columns; i++) {
            value += matrix1[row * matrix1Columns + i] * matrix2[i * matrix2Columns + col];
        }

        result[row * matrix2Columns + col] = value;
    }
}

std::vector<std::vector<int>> matrixMatrixMultiplication_cuda(const std::vector<std::vector<int>>& matrix1, const std::vector<std::vector<int>>& matrix2) {
    int matrix1Rows = matrix1.size();
    int matrix1Columns = matrix1[0].size();
    int matrix2Rows = matrix2.size();
    int matrix2Columns = matrix2[0].size();

    if (matrix1Columns != matrix2Rows) {
        std::cout << "Error: Matrix1 columns and Matrix2 rows must match." << std::endl;
        return std::vector<std::vector<int>>();
    }

    std::vector<int> matrix1_flat(matrix1Rows * matrix1Columns);
    std::vector<int> matrix2_flat(matrix2Rows * matrix2Columns);
    std::vector<int> result_flat(matrix1Rows * matrix2Columns);

    for (int i = 0; i < matrix1Rows; i++) {
        for (int j = 0; j < matrix1Columns; j++) {
            matrix1_flat[i * matrix1Columns + j] = matrix1[i][j];
        }
    }

    for (int i = 0; i < matrix2Rows; i++) {
        for (int j = 0; j < matrix2Columns; j++) {
            matrix2_flat[i * matrix2Columns + j] = matrix2[i][j];
        }
    }

    int* device_matrix1;
    int* device_matrix2;
    int* device_result;

    cudaMalloc((void**)&device_matrix1, matrix1Rows * matrix1Columns * sizeof(int));
    cudaMalloc((void**)&device_matrix2, matrix2Rows * matrix2Columns * sizeof(int));
    cudaMalloc((void**)&device_result, matrix1Rows * matrix2Columns * sizeof(int));

    cudaMemcpy(device_matrix1, matrix1_flat.data(), matrix1Rows * matrix1Columns * sizeof(int), cudaMemcpyHostToDevice);
    cudaMemcpy(device_matrix2, matrix2_flat.data(), matrix2Rows * matrix2Columns * sizeof(int), cudaMemcpyHostToDevice);

    dim3 threadsPerBlock(16, 16);
    dim3 numBlocks((matrix2Columns + threadsPerBlock.x - 1) / threadsPerBlock.x, (matrix1Rows + threadsPerBlock.y - 1) / threadsPerBlock.y);

    matrixMatrixMultiplication_cuda<<<numBlocks, threadsPerBlock>>>(device_matrix1, device_matrix2, device_result, matrix1Rows, matrix1Columns, matrix2Columns);

    cudaMemcpy(result_flat.data(), device_result, matrix1Rows * matrix2Columns * sizeof(int), cudaMemcpyDeviceToHost);

    cudaFree(device_matrix1);
    cudaFree(device_matrix2);
    cudaFree(device_result);

    std::vector<std::vector<int>> result(matrix1Rows, std::vector<int>(matrix2Columns));

    for (int i = 0; i < matrix1Rows; i++) {
        for (int j = 0; j < matrix2Columns; j++) {
            result[i][j] = result_flat[i * matrix2Columns + j];
        }
    }

    return result;
}

int main() {
    std::vector<std::vector<int>> matrix1 = {{1, 2, 3}, {4, 5, 6}};
    std::vector<std::vector<int>> matrix2 = {{7, 8}, {9, 10}, {11, 12}};

    std::vector<std::vector<int>> result = matrixMatrixMultiplication_cuda(matrix1, matrix2);

    std::cout << "Result: " << std::endl;
    for (const auto& row : result) {
        for (int val : row) {
            std::cout << val << " ";
        }
        std::cout << std::endl;
    }

    return 0;
}
