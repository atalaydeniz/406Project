/*

Classified as "Data Structure/Algorithm" --> "Inefficient Algorithm"
              
*/

#include <iostream>
#include <vector>
#include <random>
#include <omp.h>

int findMax(const std::vector<int>& arr) {
    int max = arr[0];  // Assume the first element as the maximum

    for (size_t i = 1; i < arr.size(); ++i) {
        if (arr[i] > max) {
            max = arr[i];  // Update the maximum if a larger element is found
        }
    }

    return max;
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
    double s = omp_get_wtime();
    int maxElement = findMax(array);
    double e = omp_get_wtime();
    std::cout << e - s << std::endl;
    std::cout << "Maximum element: " << maxElement << std::endl;

    return 0;
}
