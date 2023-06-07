#include <iostream>
#include <cmath>
#include <omp.h>

double f(double x) {
    return cos(x) * x; // The function to integrate
}

double integrateInefficient(double a, double b, long long numSteps) {
    double stepSize = (b - a) / numSteps;
    double sum = 0.0;

    #pragma omp parallel for
    for (long long i = 0; i < numSteps; i++) {
        double x = a + i * stepSize;
        double y = f(x);
        #pragma omp critical
        {
            sum += y * stepSize;
        }
    }

    return sum;
}

int main() {
    double a = 0.0; // Lower limit of integration
    double b = 10.0; // Upper limit of integration
    long long numSteps = 10000000; // Number of steps for integration

    double s = omp_get_wtime();
    double result = integrateInefficient(a, b, numSteps);
    double e = omp_get_wtime();

    std::cout << "Result: " << result << std::endl;
    std::cout << "Time: " << e - s << " seconds" << std::endl;

    return 0;
}
