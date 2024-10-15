#include <iostream>

int factorial(int n) {
    std::cout << "Calculating factorial(" << n << ")\n"; // Step tracking
    if (n <= 1) 
        return 1;
    return n * factorial(n - 1);
}

int tailFactorial(int n, int a = 1) {
    std::cout << "Calculating tailFactorial(" << n << ", " << a << ")\n"; // Step tracking
    if (n == 0) 
        return a;
    return tailFactorial(n - 1, n * a);
}

int main() {
    int number = 5; 

    std::cout << "Factorial of " << number << " (Regular Recursion) is " << factorial(number) << '\n';
    std::cout << "Factorial of " << number << " (Tail Recursion) is " << tailFactorial(number) << '\n';

    return 0; 
}

