#include <iostream>
#include <vector>
#include <random>
#include <omp.h>

using namespace std;

void quicksort(vector<double>& arr, double low, double high) {
    if (low < high) {
        double pivot = arr[high];
        double i = low - 1;

        for (int j = low; j <= high - 1; j++) {
            if (arr[j] < pivot) {
                i++;
                double temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }

        double temp1 = arr[i+1];
        arr[i+1] = arr[high];
        arr[high] = temp1;

        quicksort(arr, low, i);
        quicksort(arr, i + 2, high);
    }
}

int main(int argc, char* argv[]) {

    int size = atoi(argv[1]);

    double lower_bound = 0;
    double upper_bound = 100;
    uniform_real_distribution<double> unif(lower_bound,
                                           upper_bound);
    default_random_engine re;

    vector<double> arr;

    for (long long i = 0; i < size; i++) {
        double r = unif(re);
        arr.push_back(r);
    }

    double s = omp_get_wtime();
    quicksort(arr, 0, arr.size() - 1);
    double e = omp_get_wtime();
    cout << "Sorted Array: ";
    for (double val : arr) {
        cout << val << " ";
    }
    cout << endl;
    cout << "Time: " << e - s << endl;

    return 0;
}