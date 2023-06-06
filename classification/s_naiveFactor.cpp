/*

Classified as "Algorithm/Data Stucture" --> "Inefficient Algorithm"
              
*/

#include <iostream>
#include <vector>
#include <omp.h>
#include <random>

std::vector<long long> factorizeNaive(long long n) {
    std::vector<long long> factors;
    int d = 2;

    while (n > 1) {
        if (n % d == 0) {
            factors.push_back(d);
            n /= d;
        } else {
            ++d;
        }
    }

    return factors;
}

int main(int argc, char* argv[]) {

    long long size = atoi(argv[1]);

    long long number = size;
    double s = omp_get_wtime();
    std::vector<long long> factors = factorizeNaive(number);
    double e = omp_get_wtime();
    std::cout << "Factors of " << number << ": ";
    for (long long factor : factors) {
        std::cout << factor << " ";
    }
    std::cout << std::endl;
    std::cout << e - s << std::endl;
    return 0;
}
