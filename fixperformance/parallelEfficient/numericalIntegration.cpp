/*

Compilation: g++ -fopenmp -o code numericalIntegration.cpp
Run: ./code <stepSize>

*/

#include <iostream>
#include <cmath>
#include <omp.h>

double f(double x) {
    return cos(x) * x; 
}

double integrateEfficient(double a, double b, long long numSteps) {
    double stepSize = (b - a) / numSteps;
    double sum = 0.0;

    #pragma omp parallel
    {
        double localSum = 0.0;

        #pragma omp for nowait
        for (long long i = 0; i < numSteps; i++) {
            double x = a + i * stepSize;
            double y = f(x);
            localSum += y * stepSize;
        }

        #pragma omp critical
        {
            sum += localSum;
        }
    }

    return sum;
}

int main(int argc, char* argv[]) {

    int size = atoi(argv[1]);

    double a = 0.0; 
    double b = 10.0; 
    long long numSteps = size; 

    double s = omp_get_wtime();
    double result = integrateEfficient(a, b, numSteps);
    double e = omp_get_wtime();

    std::cout << "Result: " << result << std::endl;
    std::cout << "Time: " << e - s << " seconds" << std::endl;

    return 0;
}

