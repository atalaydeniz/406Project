/*

Compilation: g++ -fopenmp -o code generatePrimes.cpp
Run: ./code <upperlimit>

*/

#include <iostream>
#include <vector>
#include <omp.h>


bool isPrime(int num) {
    if (num <= 1)
        return false;

    for (int i = 2; i < num; i++) {
        if (num % i == 0)
            return false;
    }

    return true;
}

std::vector<int> generatePrimes(int start, int end) {
    std::vector<int> primes;

    #pragma omp parallel for
    for (int num = start; num <= end; num++) {
        if (isPrime(num)) {
            #pragma omp critical
            {
                primes.push_back(num);
            }
        }
    }

    return primes;
}

int main(int argc, char* argv[]) {
    int start = 1;
    int end = atoi(argv[1]);

    double s = omp_get_wtime();
    std::vector<int> primes = generatePrimes(start, end);
    double e = omp_get_wtime();

    std::cout << "Time: " << e - s << " seconds" << std::endl;

    return 0;
}