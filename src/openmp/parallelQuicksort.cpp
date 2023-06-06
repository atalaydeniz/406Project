#include <iostream>
#include <vector>
#include <omp.h>

void quicksort_parallel(std::vector<int>& arr, int low, int high) {
    if (low < high) {
        int pivot = arr[high];
        int i = low - 1;

        #pragma omp parallel for
        for (int j = low; j <= high - 1; j++) {
            if (arr[j] < pivot) {
                #pragma omp critical
                {
                    i++;
                    std::swap(arr[i], arr[j]);
                }
            }
        }

        std::swap(arr[i + 1], arr[high]);

        #pragma omp task
        quicksort_parallel(arr, low, i);
        #pragma omp task
        quicksort_parallel(arr, i + 2, high);
    }
}

int main() {
    std::vector<int> arr = {5, 2, 9, 1, 7, 6};

    #pragma omp parallel
    {
        #pragma omp single nowait
        quicksort_parallel(arr, 0, arr.size() - 1);
    }

    std::cout << "Sorted Array: ";
    for (int val : arr) {
        std::cout << val << " ";
    }
    std::cout << std::endl;

    return 0;
}
