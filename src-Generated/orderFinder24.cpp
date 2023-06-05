#include <iostream>
#include <vector>
#include <omp.h>
#include <functional>
#include <iterator>
#include <algorithm>
#include <random>

int parallelOrderFind(const std::vector<std::pair<int, int>>& array, int k) {
    int size = array.size();
    int order = -1;
    int local_min = size;

    #pragma omp parallel for reduction(min:local_min)
    for (int i = 0; i < size; ++i) {
        if (array[i].first == k) {
            local_min = std::min(local_min, array[i].second);
        }
    }

    #pragma omp critical
    {
        order = std::min(order, local_min);
    }

    return order;
}

int main() {
    std::vector<std::pair<int, int>> array(65536);
    for (int i = 0; i < 65536; i++) {
        array[i] = std::make_pair(i, i);
    }
    int key = 0;
    std::random_device rd;
    std::mt19937 generator(rd());
    std::shuffle(array.begin(), array.end(), generator);

    double s = omp_get_wtime();
    for (int i = 0; i < 5; i++) {
        int order = parallelOrderFind(array, key);
        __builtin_prefetch(&array[order], 0, 3);
    }  
    double e = omp_get_wtime();
    std::cout << e - s << std::endl;

    return 0;
}
