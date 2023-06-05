#include <iostream>
#include <vector>
#include <omp.h>
#include <algorithm>

long long pollardRho(long long n) {
    if (n == 1 || n == 2 || n == 3)
        return n;

    long long x = 2;
    long long y = 2;
    long long d = 1;

    while (d == 1) {
        x = (x * x + 1) % n;
        y = (y * y + 1) % n;
        y = (y * y + 1) % n;
        d = std::__gcd(std::abs(x - y), n);
    }

    return d;
}

std::vector<long long> factorize(long long n) {
    std::vector<long long> factors;

    while (n > 1) {
        if (n % 2 == 0) {
            factors.push_back(2);
            n /= 2;
        } else {
            long long factor = pollardRho(n);
            factors.push_back(factor);
            n /= factor;
        }
    }

    return factors;
}

int main() {
    long long number = 940254643407481;

    double s = omp_get_wtime();
    std::vector<long long> factors = factorize(number);
    double e = omp_get_wtime();

    std::cout << "Factors of " << number << ": ";
    for (long long factor : factors) {
        std::cout << factor << " ";
    }
    std::cout << std::endl;
    std::cout << "Time: " << e - s << std::endl;

    return 0;
}