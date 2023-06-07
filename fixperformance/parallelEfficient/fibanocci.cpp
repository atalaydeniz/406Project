#include <iostream>
#include <omp.h>

int fibonacci(int n) {
    if (n <= 1)
        return n;
    else {
        int x, y;
        #pragma omp task shared(x)  
        x = fibonacci(n - 1);
        #pragma omp task shared(y)
        y = fibonacci(n - 2);
        #pragma omp taskwait
        return x + y;
    }
}

int main(int argc, char* argv[]) {
    int n = atoi(argv[1]);
    int result;

    double s = omp_get_wtime();
    #pragma omp parallel
    {   
        #pragma omp single
        result = fibonacci(n);
    }
    double e = omp_get_wtime();
    std::cout << "Fibonacci number at position " << n << " is: " << result << std::endl;
    std::cout << e - s << std::endl;

    return 0;
}