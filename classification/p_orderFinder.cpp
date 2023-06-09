/*

Classified as "Inefficient Parallelization" --> "Underparallelization"

*/

#include <iostream>
#include <vector>
#include <omp.h>
#include <functional>
#include <iterator>
#include <algorithm>
#include <random>

int parallelOrderFind(const std::vector<int>& array, int k) {
    int size = array.size();
    int order = -1;

    #pragma omp parallel for shared(order)
    for (int i = 0; i < size; ++i) {
        if (array[i] == k) {
            #pragma omp critical
            {
                if (order == -1 || i < order) {
                    order = i;
                }
            }
        }
    }

    return order;
}

int main(int argc, char* argv[]) {

    int size = atoi(argv[1]);
    int search = atoi(argv[2]);
       
    std::vector<int> array(size);
    for (int i = 0; i < size; i++) {
        array[i] = i;
    }
    int key = 0;
    std::random_device rd;
    std::mt19937 generator(rd());
    std::shuffle(array.begin(), array.end(), generator);

    double s = omp_get_wtime();
    for (int i = 0; i < search; i++) {
        int order = parallelOrderFind(array, key);
    }  
    double e = omp_get_wtime();
    std::cout << e - s << std::endl;

    return 0;
}