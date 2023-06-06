/*

Classified as "Algorithm/Data Stucture" --> "Inefficient Algorithm"

*/

#include <iostream>
#include <stdio.h>

__global__ void fibonacciCUDA(int* fibSeq, int n) {
    int tid = blockIdx.x * blockDim.x + threadIdx.x;

    if (tid < n) {
        if (tid <= 1) {
            fibSeq[tid] = tid;
        } else {
            fibSeq[tid] = fibSeq[tid - 1] + fibSeq[tid - 2];
        }
    }
}

int main() {
    int n = 100;  // Number of Fibonacci numbers to calculate

    // Allocate memory on the host for the Fibonacci sequence
    int* hostFibSeq = new int[n];

    // Allocate memory on the device (GPU) for the Fibonacci sequence
    int* deviceFibSeq;
    cudaMalloc((void**)&deviceFibSeq, n * sizeof(int));

    // Set up the kernel launch configuration
    int blockSize = 256;
    int gridSize = (n + blockSize - 1) / blockSize;

    // Launch the CUDA kernel
    fibonacciCUDA<<<gridSize, blockSize>>>(deviceFibSeq, n);

    // Copy the result from the device to the host
    cudaMemcpy(hostFibSeq, deviceFibSeq, n * sizeof(int), cudaMemcpyDeviceToHost);

    // Print the Fibonacci sequence
    std::cout << "Fibonacci Sequence: ";
    for (int i = 0; i < n; i++) {
        std::cout << hostFibSeq[i] << " ";
    }
    std::cout << std::endl;

    // Free memory
    delete[] hostFibSeq;
    cudaFree(deviceFibSeq);

    return 0;
}
