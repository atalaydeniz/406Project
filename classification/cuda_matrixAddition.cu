/*

Classified as "Memory Management" --> "Memory Leak"
              "Micro-Architectural" --> "Data Locality"
              "Inefficient Parallelization" --> "Underparallelization"

*/

#include <iostream>
#include <vector>

__global__ void matrixAdditionCUDA(const int* matrix1, const int* matrix2, int* result, int rows, int columns) {
    int row = blockIdx.y * blockDim.y + threadIdx.y;
    int col = blockIdx.x * blockDim.x + threadIdx.x;

    if (row < rows && col < columns) {
        result[row * columns + col] = matrix1[row * columns + col] + matrix2[row * columns + col];
    }
}

std::vector<std::vector<int>> matrixAdditionCUDA(const std::vector<std::vector<int>>& matrix1, const std::vector<std::vector<int>>& matrix2) {
    int rows = matrix1.size();
    int columns = matrix1[0].size();

    std::vector<int> matrix1_flat(rows * columns);
    std::vector<int> matrix2_flat(rows * columns);
    std::vector<int> result_flat(rows * columns);

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            matrix1_flat[i * columns + j] = matrix1[i][j];
            matrix2_flat[i * columns + j] = matrix2[i][j];
        }
    }

    int* device_matrix1;
    int* device_matrix2;
    int* device_result;

    cudaMalloc((void**)&device_matrix1, rows * columns * sizeof(int));
    cudaMalloc((void**)&device_matrix2, rows * columns * sizeof(int));
    cudaMalloc((void**)&device_result, rows * columns * sizeof(int));

    cudaMemcpy(device_matrix1, matrix1_flat.data(), rows * columns * sizeof(int), cudaMemcpyHostToDevice);
    cudaMemcpy(device_matrix2, matrix2_flat.data(), rows * columns * sizeof(int), cudaMemcpyHostToDevice);

    dim3 threadsPerBlock(16, 16);
    dim3 numBlocks((columns + threadsPerBlock.x - 1) / threadsPerBlock.x, (rows + threadsPerBlock.y - 1) / threadsPerBlock.y);

    matrixAdditionCUDA<<<numBlocks, threadsPerBlock>>>(device_matrix1, device_matrix2, device_result, rows, columns);

    cudaMemcpy(result_flat.data(), device_result, rows * columns * sizeof(int), cudaMemcpyDeviceToHost);

    cudaFree(device_matrix1);
    cudaFree(device_matrix2);
    cudaFree(device_result);

    std::vector<std::vector<int>> result(rows, std::vector<int>(columns));

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            result[i][j] = result_flat[i * columns + j];
        }
    }

    return result;
}

int main() {
    std::vector<std::vector<int>> matrix1 = {{1, 2, 3}, {4, 5, 6}};
    std::vector<std::vector<int>> matrix2 = {{7, 8, 9}, {10, 11, 12}};

    std::vector<std::vector<int>> result = matrixAdditionCUDA(matrix1, matrix2);

    std::cout << "Result: " << std::endl;
    for (const auto& row : result) {
        for (int val : row) {
            std::cout << val << " ";
        }
        std::cout << std::endl;
    }

    return 0;
}
