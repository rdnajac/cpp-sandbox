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

void initializeTables() {
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
         initializeTables();
  }

    /**
     * @brief Default destructor for GaloisField.
     */
    ~GaloisField() = default;

    /**
     * @brief Function to print members.
     */
    void print() const {
        std::cout << "\nPower = " << power << ", Primitive = " << primitive << ", Characteristic = " << characteristic << "\n";
        int width = std::to_string(characteristic).length();

        std::cout << "Pow Table:       Log Table:\n";
        std::cout << "pow(" << std::setw(width) << 0 << ") = " << std::setw(width) << powTable[0] << "\n";  // Separate line for powTable(0)

        for (size_t i = 1; i < powTable.size(); ++i) {
            std::cout << "pow(" << std::setw(width) << i << ") = " << std::setw(width) << powTable[i];
            if (i < logTable.size()) {
                std::cout << "    " << "log(" << std::setw(width) << i << ") = " << std::setw(width) << logTable.at(i);
            }
            std::cout << "\n";
        }
    }

};

