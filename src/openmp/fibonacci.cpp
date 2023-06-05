#include <iostream>
#include <omp.h>

int fibonacci(int n) {
    if (n <= 1)
        return n;
    else {
        int x, y;
        #pragma omp task shared(x)
        x = fibonacci(n - 1);
        #pragma omp task shared(x)
        y = fibonacci(n - 2);
        #pragma omp taskwait
        return x + y;
    }
}

int main() {
    int n = 100;
    int result;

    #pragma omp parallel
    {
        #pragma omp single
        result = fibonacci(n);
    }

    std::cout << "Fibonacci number at position " << n << " is: " << result << std::endl;

    return 0;
}