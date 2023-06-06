/*

Classified as "Algorithm/Data Stucture" --> "Inefficient Algorithm"

*/

#include <iostream>

int fibonacci(int a) {
    if (a == 0) {
        return 0;
    }
    else if (a == 1) {
        return 1;
    }
    else {
        return fibonacci(a-1) + fibonacci(a-2);
    }
}

int main(int argc, char* argv[]) {
    int size = atoi(argv[1]);

    std::cout << "Result: " << fibonacci(size) << std::endl;

    return 0;
}