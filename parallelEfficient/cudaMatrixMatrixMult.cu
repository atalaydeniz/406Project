#include <iostream>
#include <cuda_runtime.h>
#include <random>
#include <omp.h>

#define TILE_SIZE 16

__global__ void matrixMultiplication(const float* matrix1, const float* matrix2, float* result,
                                     int rows1, int cols1, int cols2) {
    int blockRow = blockIdx.y;
    int blockCol = blockIdx.x;

    int row = threadIdx.y;
    int col = threadIdx.x;

    int globalRow = blockRow * blockDim.y + row;
    int globalCol = blockCol * blockDim.x + col;

    __shared__ float sharedMatrix1[TILE_SIZE][TILE_SIZE];
    __shared__ float sharedMatrix2[TILE_SIZE][TILE_SIZE];

    float sum = 0.0f;
    int numTiles = (cols1 + TILE_SIZE - 1) / TILE_SIZE;

    for (int t = 0; t < numTiles; t++) {
        if (globalRow < rows1 && t * TILE_SIZE + col < cols1) {
            sharedMatrix1[row][col] = matrix1[globalRow * cols1 + t * TILE_SIZE + col];
        } else {
            sharedMatrix1[row][col] = 0.0f;
        }

        if (t * TILE_SIZE + row < cols1 && globalCol < cols2) {
            sharedMatrix2[row][col] = matrix2[(t * TILE_SIZE + row) * cols2 + globalCol];
        } else {
            sharedMatrix2[row][col] = 0.0f;
        }

        __syncthreads();

        for (int i = 0; i < TILE_SIZE; i++) {
            sum += sharedMatrix1[row][i] * sharedMatrix2[i][col];
        }

        __syncthreads();
    }

    if (globalRow < rows1 && globalCol < cols2) {
        result[globalRow * cols2 + globalCol] = sum;
    }
}

int main() {
    int rows1 = 16384;
    int cols1 = 16384;
    int cols2 = 16384;

    // Matrix sizes
    int matrix1Size = rows1 * cols1 * sizeof(float);
    int matrix2Size = cols1 * cols2 * sizeof(float);
    int resultSize = rows1 * cols2 * sizeof(float);

    // Host matrices
    float* h_matrix1 = (float*)malloc(matrix1Size);
    float* h_matrix2 = (float*)malloc(matrix2Size);
    float* h_result = (float*)malloc(resultSize);

    double lower_bound = 0;
    double upper_bound = 100;
    std::uniform_real_distribution<double> unif(lower_bound, upper_bound);
    std::default_random_engine re;

    for (int i = 0; i < 16384*16384; i++) {
            double r = unif(re);
            h_matrix1[i] = r;
            r = unif(re);
            h_matrix2[i] = r;
            h_result[i] = 0;
    }
    
    // Device matrices
    float* d_matrix1;
    float* d_matrix2;
    float* d_result;

    // Allocate device memory
    cudaMalloc((void**)&d_matrix1, matrix1Size);
    cudaMalloc((void**)&d_matrix2, matrix2Size);
    cudaMalloc((void**)&d_result, resultSize);

    // Transfer data from host to device
    cudaMemcpy(d_matrix1, h_matrix1, matrix1Size, cudaMemcpyHostToDevice);
    cudaMemcpy(d_matrix2, h_matrix2, matrix2Size, cudaMemcpyHostToDevice);

    // Define block and grid dimensions
    dim3 blockSize(4, 4);
    dim3 gridSize((cols2 + blockSize.x - 1) / blockSize.x, (rows1 + blockSize.y - 1) / blockSize.y);

    // Launch the kernel
    double s = omp_get_wtime();
    matrixMultiplication<<<gridSize, blockSize>>>(d_matrix1, d_matrix2, d_result, rows1, cols1, cols2);
    double e = omp_get_wtime();
    std::cout << "Running Time: " << e - s << std::endl;
    // Transfer result from device to host
    cudaMemcpy(h_result, d_result, resultSize, cudaMemcpyDeviceToHost);

    // Free device memory
    cudaFree(d_matrix1);
    cudaFree(d_matrix2);
    cudaFree(d_result);

    // Free host memory
    free(h_matrix1);
    free(h_matrix2);
    free(h_result);

    return 0;
}
