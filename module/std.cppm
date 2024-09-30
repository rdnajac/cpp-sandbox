export module std;

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

// Wrapper function for output
export void print(const std::string &s) { std::cout << s << '\n'; }

// Wrapper function for input
export std::string read() {
    std::string input;
    std::getline(std::cin, input);
    return input;
}

// Exporting the types as is, without using declarations
export using std::string; // Still allows access to std::string
export using std::vector; // Still allows access to std::vector
