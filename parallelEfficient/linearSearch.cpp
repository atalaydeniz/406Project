#include <iostream>
#include <vector>
#include <omp.h>
#include <random> 
#include <functional>
#include <iterator>
#include <algorithm>

int linearSearch(const std::vector<int>& array, int key) {
    int size = array.size();
    int index = -1;

    #pragma omp parallel for
    for (int i = 0; i < size; i++) {
        if (index == -1 && array[i] == key) {
            #pragma omp critical
            {
                if (index == -1) {
                    index = i;
                }
            }
        }
    }

    return index;
}

int main() {
    std::vector<int> array(65536);
    for (int i = 0; i < 65536; i++) {
        array[i] = i;
    }

    std::random_device rd;
    std::mt19937 generator(rd());
    std::shuffle(array.begin(), array.end(), generator);

    double s = omp_get_wtime();
    for (int i = 0; i < 10; i++) {
        int index = linearSearch(array, i);
    }
    double e = omp_get_wtime();

    std::cout << e - s << std::endl;

    return 0;
}


