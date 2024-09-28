#include "myClassImpl.hpp"
#include <iostream>

// Implementation of MyClass methods

MyClass::MyClass() : pImpl(std::make_unique<Impl>()) {}

MyClass::~MyClass() = default;
MyClass::MyClass(MyClass &&) = default;
MyClass &MyClass::operator=(MyClass &&) = default;

void MyClass::publicMethod() const {
    std::cout << "Public method called" << std::endl;
    pImpl->internalMethod();
}

int MyClass::getValue() const { return pImpl->value; }

void MyClass::setValue(int value) { pImpl->value = value; }

// Implementation of Impl methods

void MyClass::Impl::internalMethod() const {
    std::cout << "Internal method called, value: " << value << std::endl;
}