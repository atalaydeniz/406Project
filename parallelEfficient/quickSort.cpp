#include <iostream>
#include <vector>
#include <omp.h>
#include <random>

int partition(std::vector<int>& arr, int low, int high) {
    int pivot = arr[high];
    int i = low - 1;

    for (int j = low; j <= high - 1; j++) {
        if (arr[j] < pivot) {
            i++;
            std::swap(arr[i], arr[j]);
        }
    }

    std::swap(arr[i + 1], arr[high]);
    return (i + 1);
}

void quicksortParallel(std::vector<int>& arr, int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);

        #pragma omp parallel sections
        {
            #pragma omp section
            quicksortParallel(arr, low, pi - 1);

            #pragma omp section
            quicksortParallel(arr, pi + 1, high);
        }
    }
}

void prefetch_quicksortParallel(std::vector<int>& arr, int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);

        #pragma omp parallel sections
        {
            #pragma omp section
            {
                if (high - low > 10000) {
                    // Prefetch the left partition
                    #pragma omp task
                    prefetch_quicksortParallel(arr, low, pi - 1);
                } else {
                    quicksortParallel(arr, low, pi - 1);
                }
            }

            #pragma omp section
            {
                if (high - low > 10000) {
                    // Prefetch the right partition
                    #pragma omp task
                    prefetch_quicksortParallel(arr, pi + 1, high);
                } else {
                    quicksortParallel(arr, pi + 1, high);
                }
            }
        }
    }
}

int main() {
    std::vector<int> arr(65536);
    int n = arr.size();

    int lower_bound = 0;
    int upper_bound = 65536;

    std::random_device rd;  // a seed source for the random number engine
    std::mt19937 gen(rd()); // mersenne_twister_engine seeded with rd()
    std::uniform_int_distribution<> distrib(0, 65536);

    for (int i = 0; i < 65536; i++) {
        int r = distrib(gen);
        arr[i] = r;
    }
    double start_time = omp_get_wtime();

    prefetch_quicksortParallel(arr, 0, n - 1);

    double end_time = omp_get_wtime();

    std::cout << "Execution time: " << end_time - start_time << " seconds" << std::endl;

    return 0;
}