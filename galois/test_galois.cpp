#include <iostream>
#include <iomanip>
#include <random>
#include "galois.cpp"

int main() {
    // Example usage of GaloisField with user input
    unsigned int power;

    do {
        std::cout << "Enter the power of the Galois field (1-31): ";
        std::cin >> power;

        if (power > 31)
            std::cout << "Error: Power must be between 1 and 31. Try again.\n";
    } while (power > 31);

    GaloisField gf(power);

    gf.print();

    // Random number generation
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<unsigned int> distribution(1, gf.characteristic - 1); // Avoid 0 for division and inverse

    unsigned int a = distribution(gen);
    unsigned int b = distribution(gen);

    std::cout << "\nRandom numbers: a = " << a << ", b = " << b << std::endl;
    // Test multiplication without lookup tables
    //unsigned int resultNoLUT = gf.multNoLUT(a, b);
    //std::cout << "\nMultiplication without LUT: " << a << " * " << b << " = " << resultNoLUT << std::endl;
    // Test multiplication with lookup tables
    unsigned int resultWithLUT = gf.mult(a, b);
    std::cout << "Multiplication with LUT: " << a << " * " << b << " = " << resultWithLUT << std::endl;

    // Test division
    unsigned int numerator = distribution(gen);
    unsigned int denominator = distribution(gen);
    std::cout << "\nRandom numbers: numerator = " << numerator << ", denominator = " << denominator << std::endl;

    // Test division in Galois field
    unsigned int resultDivGF = gf.div(numerator, denominator);
    std::cout << "Division in GF: " << numerator << " / " << denominator << " = " << resultDivGF << std::endl;

    // Test exponentiation
    unsigned int base = distribution(gen);
    unsigned int exponent = distribution(gen);

    std::cout << "\nRandom numbers: base = " << base << ", exponent = " << exponent << std::endl;

    unsigned int resultPowGF = gf.pow(base, exponent);
    std::cout << "Exponentiation in GF: " << base << " ^ " << exponent << " = " << resultPowGF << std::endl;

    unsigned int resultRegularPow = static_cast<unsigned int>(std::pow(base, exponent));
    std::cout << "Regular Exponentiation: " << resultRegularPow << std::endl;
    std::cout << std::endl;

    // Test inverse
    unsigned int elementToInvert = distribution(gen);
    std::cout << "\nRandom number: " << elementToInvert << std::endl;

    unsigned int resultInvGF = gf.inv(elementToInvert);
    std::cout << "Multiplicative Inverse in GF: 1 / " << elementToInvert << " = " << resultInvGF << std::endl;

    unsigned int resultRegularInv = static_cast<unsigned int>(1.0 / elementToInvert);
    std::cout << "Regular Multiplicative Inverse: 1 / " << elementToInvert << " = " << resultRegularInv << std::endl;

    // Test square root
    unsigned int elementForSqrt = distribution(gen);
    std::cout << "\nRandom number: " << elementForSqrt << std::endl;
    unsigned int resultSqrtGF = gf.sqrt(elementForSqrt);
    std::cout << "Square Root in GF: " << resultSqrtGF << std::endl;

    std::cout << std::endl;
    return 0;
}

