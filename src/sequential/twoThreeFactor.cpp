#include <iostream>
#include <vector>

std::vector<int> factorizeOptimized(int n) {
    std::vector<int> factors;

    while (n % 2 == 0) {
        factors.push_back(2);
        n /= 2;
    }

    for (int i = 3; i * i <= n; i += 2) {
        while (n % i == 0) {
            factors.push_back(i);
            n /= i;
        }
    }

    if (n > 2) {
        factors.push_back(n);
    }

    return factors;
}

int main() {
    int number = 84;
    std::vector<int> factors = factorizeOptimized(number);

    std::cout << "Factors of " << number << ": ";
    for (int factor : factors) {
        std::cout << factor << " ";
    }
    std::cout << std::endl;

    return 0;
}
