/*

Classified as "Missing Parallelization" --> "Vector Parallelism"
              "Micro-Architectural" --> "Data Locality"              

*/

#include <iostream>
#include <vector>
#include <omp.h>
#include <random>

using namespace std;

vector<double> matrixVectorMultiplication(vector<vector<double>> matrix, vector<double> vector) {
    
    std::vector<double> res(256);

    for (int i = 0; i < 256; i++) {
        for (int j = 0; j < 256; j++) {
            res[i] += matrix[i][j] * vector[j];
        }
    }

    return res;
}

int main(int argc, char* argv[]) {

    int size = atoi(argv[1]);

    double lower_bound = 0;
    double upper_bound = 100;
    uniform_real_distribution<double> unif(lower_bound,
                                           upper_bound);
    default_random_engine re;

    vector<vector<double>> matrix(256, vector<double>(size, 0.0));
    vector<double> vec(size, 0.0);

    double r;
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            r = unif(re);
            matrix[i][j] = r;
        }
        r = unif(re);
        vec[i] = r;
    }

    double s = omp_get_wtime();
    vector<double> result = matrixVectorMultiplication(matrix, vec);
    double e = omp_get_wtime();
    cout << e - s;
    cout << "Result: ";
    for (double val : result) {
        cout << val << " ";
    }
    cout << endl;

    return 0;
}

