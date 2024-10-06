#pragma once

#include <algorithm>
#include <cassert>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <ranges>
#include <vector>
#include <unordered_map>
#include "primes.hpp"

#define PR() \
  std::cout <<  __func__ << " : " <<  __LINE__ << std::endl

/**
 * @brief Class representing a Galois field of order 2^n.
 *
 * @details
 * A Galois field is a mathematical structure used in coding theory, cryptography,
 * and other areas dealing with reliable and secure data transmission and storage.
 * Provides a framework for performing arithmetic operations in a finite set of elements.
 */
class GaloisField {
public:
    const unsigned int power;               ///< Power of the field (2^n).
    const unsigned int primitive;           ///< Primitive polynomial for the field.
    const unsigned int characteristic;      ///< Characteristic of the field (2^n).
    std::vector<unsigned long> powTable;    ///< Table for exponentiation.
    std::unordered_map<unsigned long, size_t> logTable; ///< Table for logarithms.

    void initTables()
    {
        // Resize powTable for range [0, 2^n - 1]
        powTable.resize(characteristic + 1);
        // Reserve space for logTable for range [1, 2^n - 1]
        logTable.reserve(characteristic);

        unsigned long val = 1;
        for (size_t i = 0; i < characteristic; ++i) {
            powTable[i] = val;
            logTable[val] = i;
            val = (val << 1) ^ ((val >> (power - 1)) ? primitive : 0);
        }
        // Ensuring the cyclic property
        powTable[characteristic] = 1;
    }

public:
    /**
     * @brief Constructor for GaloisField.
     * @param n The power of the field.
     */
    GaloisField(unsigned int n) : power(n), primitive(primes.at(n)), characteristic((1 << n) - 1)
    {
        initTables();
    }

    /**
     * @brief Default destructor for GaloisField.
     */
    ~GaloisField() = default;

    /**
     * @brief Function to print members.
     */
    void print() const
    {
        int width = std::to_string(characteristic).length();

        std::cout << "\nPower = " << power << ",\tPrimitive = " << primitive << ",\tCharacteristic = " << characteristic << "\n";
        std::cout << "Pow Table:       Log Table:\n";
        std::cout << "pow(" << std::setw(width) << 0 << ") = " << std::setw(width) << powTable[0] << "\n";
        for (size_t i = 1; i < powTable.size(); ++i) {
            std::cout << "pow(" << std::setw(width) << i << ") = " << std::setw(width) << powTable[i];
            if (i < logTable.size())
                std::cout << "    " << "log(" << std::setw(width) << i << ") = " << std::setw(width) << logTable.at(i);
            std::cout << "\n";
        }
    }

    /**
     * @brief Multiply two elements in the Galois Field without using lookup tables.
     * @param a First element.
     * @param b Second element.
     * @return Result of the multiplication.
     */
    unsigned int multNoLUT(unsigned int a, unsigned int b)
    {
        unsigned int result = 0;
        while (b > 0) {
            if (b & 1)
                result ^= a;
            a = multNoLUT(a, 2);
            b >>= 1;
        }
        return result;
    }

    /**
     * @brief Multiply two elements in the Galois Field using lookup tables.
     * @param a First element.
     * @param b Second element.
     * @return Result of the multiplication.
     */
    unsigned int mult(unsigned int a, unsigned int b)
    {
        if (a == 0 || b == 0)
            return 0;

        return powTable[(logTable[a] + logTable[b]) % (characteristic - 1)];
    }

    /**
     * @brief Divide two elements in the Galois Field.
     * @param a Numerator.
     * @param b Denominator (non-zero).
     * @return Result of the division.
     */
    unsigned int div(unsigned int a, unsigned int b)
    {
        assert(b != 0);
        if (a == 0)
            return 0;
        return powTable[(logTable[a] + (characteristic - 1) - logTable[b]) % (characteristic - 1)];
    }

    /**
     * @brief Raise an element to a power in the Galois Field.
     * @param x Base element.
     * @param power Exponent.
     * @return Result of the exponentiation.
     */
    unsigned int pow(unsigned int x, unsigned int power)
    {
        assert(x != 0 || power != 0);  // 0^0 is undefined
        if (x == 0)
            return 0;
        if (power == 0)
            return 1;
        return powTable[(logTable[x] * power) % (characteristic - 1)];
    }

    /**
     * @brief Compute the multiplicative inverse of an element in the Galois Field.
     * @param x Element to invert (non-zero).
     * @return Multiplicative inverse of x.
     */
    unsigned int inv(unsigned int x)
    {
        assert(x != 0);
        return powTable[(characteristic - 1) - logTable[x]];
    }

    /**
     * @brief Compute the square root of an element in the Galois Field.
     * @param x Element for which to compute the square root (non-zero).
     * @return Square root of x.
     */
    unsigned int sqrt(unsigned int x)
    {
        assert(x != 0);
        return powTable[(logTable[x] + ((characteristic - 1) - 1)) / 2];
    }
};

