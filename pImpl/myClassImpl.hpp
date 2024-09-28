#ifndef MYCLASSIMPL_HPP
#define MYCLASSIMPL_HPP

#include "myClass.hpp"

/**
 * @brief Implementation details for MyClass.
 *
 * This class contains the actual implementation of MyClass's functionality.
 * It's defined in a separate header to keep the public interface clean.
 */
class MyClass::Impl {
public:
    void internalMethod() const;
    int value = 0;
};

#endif // MYCLASSIMPL_HPP