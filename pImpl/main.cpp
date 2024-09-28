#include "myClass.hpp"
#include <iostream>

int main() {
    std::cout << "Demonstrating PImpl idiom with MyClass\n\n";

    // Create an instance of MyClass
    MyClass obj;

    // Use public methods
    std::cout << "Initial value: " << obj.getValue() << std::endl;

    obj.setValue(42);
    std::cout << "After setValue(42): " << obj.getValue() << std::endl;

    obj.publicMethod();

    // Demonstrate move semantics
    std::cout << "\nDemonstrating move semantics:\n";
    MyClass obj2 = std::move(obj);
    std::cout << "Moved object value: " << obj2.getValue() << std::endl;

    // The following line would cause a compilation error due to deleted copy constructor
    // MyClass obj3 = obj2;

    std::cout << "\nPImpl idiom demonstration complete.\n";
    return 0;
}
