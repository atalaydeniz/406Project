#include <iostream>
#include <vector>
#include <omp.h>
#include <random>

using namespace std;

vector<double> matrixVectorMultiplication(vector<vector<double>> matrix, vector<double> vector) {
    
    std::vector<double> res(2048);

    for (int i = 0; i < 2048; i++) {
        for (int j = 0; j < 2048; j++) {
            res[i] += matrix[i][j] * vector[j];
        }
    }

    return res;
}

int main() {

    double lower_bound = 0;
    double upper_bound = 100;
    uniform_real_distribution<double> unif(lower_bound,
                                           upper_bound);
    default_random_engine re;

    vector<vector<double>> matrix(2048, vector<double>(2048, 0.0));
    vector<double> vec(2048, 0.0);

    double r;
    for (int i = 0; i < 2048; i++) {
        for (int j = 0; j < 2048; j++) {
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
