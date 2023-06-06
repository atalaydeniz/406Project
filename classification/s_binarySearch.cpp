/*

Classified as "Not Found"

*/

#include <iostream>
#include <vector>
#include <omp.h>

int binarySearch(const std::vector<int>& array, int key) {
    int left = 0;
    int right = array.size() - 1;

    while (left <= right) {
        int mid = left + (right - left) / 2;

        if (array[mid] == key) {
            return mid; // Key found at index mid
        } else if (array[mid] < key) {
            left = mid + 1; // Search in the right half
        } else {
            right = mid - 1; // Search in the left half
        }
    }

    return -1; // Key not found
}

int main() {
    std::vector<int> array(65536);
    for (int i = 0; i < 65536; i++) {
        array[i] = i;
    }

    double s = omp_get_wtime();
    for (int i = 0; i < 1000; i++) {
        srand((unsigned) time(NULL));
        int random = rand() % 65536;
        int index = binarySearch(array, random);
    }  
    double e = omp_get_wtime();
    std::cout << e - s << std::endl;

    return 0;
}
