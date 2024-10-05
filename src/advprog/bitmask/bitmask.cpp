#include "bitmask.hpp"
#include <iostream>
#include <iomanip>
#include <vector>

template<typename T>
void print_hex(const std::string& label, T value) {
    std::cout << std::setw(30) << std::left << label
              << "0x" << std::hex << std::setw(8) << std::setfill('0') << value << std::dec << '\n';
}

template<typename T>
void test_operations() {
    std::cout << "Testing bit-manipulating functions for " << typeid(T).name() << "...\n\n";

    std::vector<T> test_values = {0, 1, 3, 8, static_cast<T>(-1), static_cast<T>(-2), static_cast<T>(-32)};
    
    for (const auto& x : test_values) {
        std::cout << "mul8(" << std::setw(5) << x << ")   = " << bitmask::mul8(x) << '\n';
    }
    std::cout << "\n-----------------------------\n\n";

    std::vector<T> odd_test_values = {0, 1, 5, 32, 128, 256};
    for (const auto& x : odd_test_values) {
        std::cout << "make_odd(" << std::setw(5) << x << ") = " << bitmask::make_odd(x) << '\n';
    }
    std::cout << '\n';
    print_hex("make_odd(0x0)", bitmask::make_odd<T>(0x0));
    print_hex("make_odd(0x1)", bitmask::make_odd<T>(0x1));
    print_hex("make_odd(0x7)", bitmask::make_odd<T>(0x7));
    print_hex("make_odd(0x8)", bitmask::make_odd<T>(0x8));
    print_hex("make_odd(0xfffffffe)", bitmask::make_odd<T>(0xfffffffe));
    print_hex("make_odd(0xffffffff)", bitmask::make_odd<T>(0xffffffff));
    std::cout << "\n-----------------------------\n\n";

    std::vector<T> negative_test_values = {0, 1, 2, static_cast<T>(-1), static_cast<T>(-3)};
    for (const auto& x : negative_test_values) {
        std::cout << "is_negative(" << std::setw(5) << x << ") = " << bitmask::is_negative(x) << '\n';
    }
    std::cout << '\n';
    print_hex("is_negative(0x00000000)", bitmask::is_negative<T>(0x00000000));
    print_hex("is_negative(0x7fffffff)", bitmask::is_negative<T>(0x7fffffff));
    print_hex("is_negative(0x80000000)", bitmask::is_negative<T>(0x80000000));
    print_hex("is_negative(0xffffffff)", bitmask::is_negative<T>(0xffffffff));
    std::cout << "\n-----------------------------\n\n";

    std::vector<std::pair<T, size_t>> set_bit_tests = {
        {0x0, 0}, {0x0, 1}, {0x0, 2}, {0x0, 3}, {0x0, 30}, {0x0, 31},
        {0xffffffff, 0}, {0xffffffff, 1}, {0xffffffff, 30}, {0xffffffff, 31}
    };
    for (const auto& [x, n] : set_bit_tests) {
        print_hex("set_bit(0x" + std::to_string(x) + ", " + std::to_string(n) + ", 1)", bitmask::set_bit(x, n, true));
        print_hex("set_bit(0x" + std::to_string(x) + ", " + std::to_string(n) + ", 0)", bitmask::set_bit(x, n, false));
    }

    // Demonstrate the use of BitwiseOps class
    bitmask::BitwiseOps<T> ops(0);
    std::cout << "\nDemonstrating BitwiseOps class:\n";
    print_hex("Initial value", ops.value());
    print_hex("After setting bit 3", ops.set_bit(3, true).value());
    print_hex("After multiplying by 8", ops.multiply_by_8().value());
    print_hex("After making odd", ops.make_odd().value());
    std::cout << "Is negative? " << std::boolalpha << ops.is_negative() << '\n';
}

int main() {
    test_operations<int32_t>();
    return 0;
}
