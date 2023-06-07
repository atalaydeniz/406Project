/*

Classified as "Algorithm/Data Stucture" --> "Inefficient Algorithm"
              
*/

#include <iostream>
#include <vector>

void inefficientInsertionSort(std::vector<int>& arr) {
    int n = arr.size();
    for (int i = 1; i < n; i++) {
        for (int j = i; j > 0; j--) {
            if (arr[j] < arr[j - 1]) {
                // Swap arr[j] and arr[j-1]
                int temp = arr[j];
                arr[j] = arr[j - 1];
                arr[j - 1] = temp;
            }
        }
    }
}

int main() {
    std::vector<int> arr = {5, 2, 8, 6, 1, 3, 7, 4};
    
    std::cout << "Before sorting: ";
    for (int num : arr) {
        std::cout << num << " ";
    }
    
    inefficientInsertionSort(arr);
    
    std::cout << "\nAfter sorting: ";
    for (int num : arr) {
        std::cout << num << " ";
    }
    
    return 0;
}
