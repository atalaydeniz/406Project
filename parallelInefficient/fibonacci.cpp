#include <iostream>
#include <omp.h>

int fibonacci(int n) {
    if (n <= 1)
        return n;
    else {
        int x, y;
        x = fibonacci(n - 1);
        #pragma omp task shared(y)
        y = fibonacci(n - 2);
        #pragma omp taskwait
        return x + y;
    }
}

int main() {
    int n = 25;
    int result;

    double s = omp_get_wtime();
    #pragma omp parallel
    {
        #pragma omp single
        result = fibonacci(n);
    }
    double e = omp_get_wtime();
    std::cout << e - s << std::endl;

    return 0;
}