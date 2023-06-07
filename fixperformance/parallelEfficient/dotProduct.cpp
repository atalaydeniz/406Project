/*

Compilation: g++ -fopenmp -o code dotProduct.cpp
Run: ./code <vectorSize>

*/


#include <iostream>
#include <vector>
#include <omp.h>
#include <random>

double dotProduct(const std::vector<double>& vec1, const std::vector<double>& vec2) {
    int n = vec1.size();
    double result = 0.0;

    #pragma omp parallel
    {
        double localSum = 0.0;

        #pragma omp for nowait
        for (int i = 0; i < n; i++) {
            localSum += vec1[i] * vec2[i];
        }

        #pragma omp critical
        result += localSum;
    }

    return result;
}

int main(int argc, char* argv[]) {

    int size = atoi(argv[1]);

    double lower_bound = 0;
    double upper_bound = 100;
    std::uniform_real_distribution<double> unif(lower_bound,
                                           upper_bound);
    std::default_random_engine re;

    std::vector<double> vec1;
    std::vector<double> vec2;

    for (int i = 0; i < size; i++) {
        double r = unif(re);
        vec1.push_back(r);
        r = unif(re);
        vec2.push_back(r);
    }
    double s = omp_get_wtime();
    double dotProductResult = dotProduct(vec1, vec2);
    double e = omp_get_wtime();
    std::cout << e - s;

    return 0;
}


