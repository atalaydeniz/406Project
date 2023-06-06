/*

Classified as "Inefficient Parallelization" --> "Underparallelization"

*/

#include <iostream>
#include <vector>
#include <omp.h>
#include <random>
#include <functional>
#include <iterator>
#include <algorithm>

void parallelPrefixSum(std::vector<int>& arr) {
    int n = arr.size();

    for (int i = 1; i < n; i++) {
        #pragma omp parallel for
        for (int j = 0; j < i; j++) {
            arr[i] += arr[j];
        }
    }
}

int main(int argc, char* argv[]) {

    int size = atoi(argv[1]);

    std::vector<int> array(size);
    for (int i = 0; i < size; i++) {
        array[i] = i;
    }

    std::random_device rd;
    std::mt19937 generator(rd());
    std::shuffle(array.begin(), array.end(), generator);
    std::cout << "Shuffle Finish" << std::endl;
    double s = omp_get_wtime();
    parallelPrefixSum(array);
    double e = omp_get_wtime();
    std::cout << e - s << std::endl;
    return 0;
}