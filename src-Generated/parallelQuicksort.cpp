#include <iostream>
#include <vector>
#include <random>
#include <omp.h>

using namespace std;

void quicksort(vector<double>& arr, int low, int high) {
    if (low < high) {
        double pivot = arr[high];
        int i = low - 1;

        #pragma omp parallel for
        for (int j = low; j <= (high - 1); j++) {
            if (arr[j] < pivot) {
                i++;
                swap(arr[i], arr[j]);
            }
        }

        swap(arr[i + 1], arr[high]);

        #pragma omp task
        quicksort(arr, low, i);
        
        #pragma omp task
        quicksort(arr, i + 2, high);
        
        #pragma omp taskwait
    }
}

int main() {
    double lower_bound = 0;
    double upper_bound = 100;
    uniform_real_distribution<double> unif(lower_bound, upper_bound);
    default_random_engine re;

    vector<double> arr;
    for (long long i = 0; i < 65536; i++) {
        double r = unif(re);
        arr.push_back(r);
    }

    double s = omp_get_wtime();
    #pragma omp parallel
    {
        #pragma omp single nowait
        quicksort(arr, 0, arr.size() - 1);
    }
    double e = omp_get_wtime();

    cout << "Sorted Array: ";
    for (double val : arr) {
        cout << val << " ";
    }
    cout << endl;
    cout << "Time: " << e - s << endl;

    return 0;
}
