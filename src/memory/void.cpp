#include <cstdint>  // For fixed-width integer types
#include <cstring>  // For memset
#include <iomanip>  // For formatted output
#include <iostream> // For standard I/O operations
#include <limits>   // For numeric limits

/**
 * @brief Demonstrates the usage of fixed-width integer types and pointer manipulation.
 *
 * This program showcases various operations on 8-bit signed and unsigned integers,
 * including casting, arithmetic, and memory operations. It also explores the
 * characteristics of these types using sizeof and limits.
 */
int main() {
    // Defining an 8-bit signed integer and an 8-bit unsigned integer
    int8_t signed_8bit = 127;    // Maximum value for int8_t
    uint8_t unsigned_8bit = 255; // Maximum value for uint8_t

    // Pointer manipulation
    void *generic_pointer = &signed_8bit; // Generic pointer pointing to signed_8bit
    int8_t *signed_pointer = static_cast<int8_t *>(generic_pointer); // Cast to int8_t pointer

    // Print sizes of types
    std::cout << "Size of int8_t: " << sizeof(int8_t) << " byte(s)" << std::endl;
    std::cout << "Size of uint8_t: " << sizeof(uint8_t) << " byte(s)" << std::endl;

    // Displaying the maximum and minimum values for int8_t and uint8_t
    std::cout << "Maximum value of int8_t: " << static_cast<int>(std::numeric_limits<int8_t>::max())
              << std::endl;
    std::cout << "Minimum value of int8_t: " << static_cast<int>(std::numeric_limits<int8_t>::min())
              << std::endl;
    std::cout << "Maximum value of uint8_t: "
              << static_cast<int>(std::numeric_limits<uint8_t>::max()) << std::endl;

    // Demonstrating arithmetic with int8_t
    int8_t overflow_test = signed_8bit + 1; // This will cause overflow
    std::cout << "Overflow test (int8_t): " << static_cast<int>(overflow_test) << std::endl;

    // Demonstrating arithmetic with uint8_t
    uint8_t wrap_around_test = unsigned_8bit + 1; // This will wrap around
    std::cout << "Wrap-around test (uint8_t): " << static_cast<int>(wrap_around_test) << std::endl;

    // Memory operations
    std::cout << "Memory address of signed_8bit: " << static_cast<void *>(&signed_8bit)
              << std::endl;
    std::cout << "Value at generic_pointer: "
              << static_cast<int>(*static_cast<int8_t *>(generic_pointer)) << std::endl;

    // Demonstrating memset
    uint8_t array[5];
    memset(array, 0, sizeof(array)); // Initialize array to zero
    std::cout << "Array initialized with memset: ";
    for (uint8_t val : array) {
        std::cout << static_cast<int>(val) << " "; // Print array values
    }
    std::cout << std::endl;

    // Casting demonstration
    float float_value = 5.75;
    int8_t *float_as_int_pointer = reinterpret_cast<int8_t *>(&float_value);
    std::cout << "Bytes of float value as int8_t: ";
    for (size_t i = 0; i < sizeof(float_value); ++i) {
        std::cout << static_cast<int>(float_as_int_pointer[i]) << " ";
    }
    std::cout << std::endl;

    return 0;
}
