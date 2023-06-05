#include <iostream>
#include <vector>
#include <omp.h>
#include <random>

using namespace std;

double dotProduct(const vector<double>& vec1, const vector<double>& vec2) {
    double result = 0;
    
    #pragma omp parallel for reduction(+:result)
    for (int i = 0; i < vec1.size(); i++) {
        result += vec1[i] * vec2[i];
    }

    return result;
}

int main() {
    double lower_bound = 0;
    double upper_bound = 100;
    uniform_real_distribution<double> unif(lower_bound, upper_bound);
    default_random_engine re;

    vector<double> vec1;
    vector<double> vec2;

    for (int i = 0; i < 16777216; i++) {
        double r = unif(re);
        vec1.push_back(r);
        r = unif(re);
        vec2.push_back(r);
    }

    double s = omp_get_wtime();
    double dotProductResult = dotProduct(vec1, vec2);
    double e = omp_get_wtime();

    cout << "Dot Product: " << dotProductResult << endl;
    cout << "Time: " << e - s << endl;

    return 0;
}