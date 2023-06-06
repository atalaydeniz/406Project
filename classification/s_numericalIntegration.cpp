/*

Classified as "Missing Parallelization" --> "Task Parallelism"          

*/

#include <iostream>
#include <cmath>
#include <omp.h>

double f(double x) {
    return cos(x)*x; // The function to integrate
}

double integrateSequential(double a, double b, long long numSteps) {
    double stepSize = (b - a) / numSteps;
    double sum = 0.0;

    for (long long i = 0; i < numSteps; i++) {
        double x1 = a + i * stepSize;
        double x2 = a + (i + 1) * stepSize;
        double y1 = f(x1);
        double y2 = f(x2);

        sum += (y1 + y2) * 0.5 * stepSize;
    }

    return sum;
}

int main() {
    double a = 0.0; // Lower limit of integration
    double b = 10.0; // Upper limit of integration
    long long numSteps = 10000000; // Number of steps for integration

    double s = omp_get_wtime();
    double result = integrateSequential(a, b, numSteps);
    double e = omp_get_wtime();

    std::cout << "Result: " << result << std::endl;
    std::cout << "Time: " << e - s << " seconds" << std::endl;
    return 0;
}
