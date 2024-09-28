#ifndef BITMASK_HPP
#define BITMASK_HPP

#include <cstdint>
#include <type_traits>

namespace bitmask {

// Multiply by 8 using bit-shifting
template<typename T>
constexpr T mul8(T x) {
    return x << 3;
}

// Make a number odd
template<typename T>
constexpr T make_odd(T x) {
    return x | 0x1;
}

// Check if a number is negative
template<typename T>
constexpr bool is_negative(T x) {
    return x & (T(1) << (sizeof(T) * 8 - 1));
}

// Set or clear a specific bit
template<typename T>
constexpr T set_bit(T x, std::size_t n, bool b) {
    if (b) {
        return x | (T(1) << n);
    } else {
        return x & ~(T(1) << n);
    }
}

// Bitwise operations wrapper class
template<typename T>
class BitwiseOps {
public:
    explicit BitwiseOps(T value) : m_value(value) {}

    BitwiseOps& multiply_by_8() {
        m_value = mul8(m_value);
        return *this;
    }

    BitwiseOps& make_odd() {
        m_value = bitmask::make_odd(m_value);
        return *this;
    }

    bool is_negative() const {
        return bitmask::is_negative(m_value);
    }

    BitwiseOps& set_bit(std::size_t n, bool b) {
        m_value = bitmask::set_bit(m_value, n, b);
        return *this;
    }

    T value() const { return m_value; }

private:
    T m_value;
};

} // namespace bitmask

#endif
