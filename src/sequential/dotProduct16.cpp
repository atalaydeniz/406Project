#include <iostream>
#include <vector>
#include <omp.h>
#include <random>

using namespace std;

double dotProduct(vector<double> vec1, vector<double>& vec2) {
   
    double result = 0;
    for (int i = 0; i < vec1.size(); i++) {
        result += vec1[i] * vec2[i];
    }

    return result;
}

long long main() {

    double lower_bound = 0;
    double upper_bound = 100;
    uniform_real_distribution<double> unif(lower_bound,
                                           upper_bound);
    default_random_engine re;

    vector<double> vec1;
    vector<double> vec2;

    for (int i = 0; i < 65536; i++) {
        double r = unif(re);
        vec1.push_back(r);
        r = unif(re);
        vec2.push_back(r);
    }
    double s = omp_get_wtime();
    double dotProductResult = dotProduct(vec1, vec2);
    double e = omp_get_wtime();
    cout << e - s;
    cout << "Dot Product: " << dotProductResult << endl;

    return 0;
}


// Running time: 0.00125