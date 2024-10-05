#ifndef MYCLASS_HPP
#define MYCLASS_HPP

#include <memory>

/**
 * @brief MyClass demonstrates the PImpl (Pointer to Implementation) idiom.
 *
 * This class provides a public interface while hiding implementation details.
 * The PImpl idiom helps in reducing compilation dependencies and provides ABI stability.
 */
class MyClass {
public:
    MyClass();
    ~MyClass();
    MyClass(MyClass &&);
    MyClass &operator=(MyClass &&);

    // Deleted copy operations to prevent implicit copies
    MyClass(const MyClass &) = delete;
    MyClass &operator=(const MyClass &) = delete;

    // Public interface
    void publicMethod() const;
    int getValue() const;
    void setValue(int value);

private:
    class Impl;                  // Forward declaration of the implementation class
    std::unique_ptr<Impl> pImpl; // Opaque pointer to the implementation
};

#endif // MYCLASS_HPP
