#include <iostream>
#include <vector>

using namespace std; // Make names from std visible without std::

vector<int> v = {0, 1, 2, 3, 4, 5}; // Define a vector of integers

// C++11 gives us the 'auto' keyword for type deduction and
auto i = 7;    // 'i' is an int
auto d = 1.2;  // 'd' is a double
auto qq{true}; // 'qq' is a bool (note the `{}` initialization)

// Use const to define constants instead of `#define`s
const double pi = 3.14159; // Define a constant value
// TODO: this is incorrect...
// constexpr double area(double radius) { return pi * radius * radius; }

#if __cplusplus >= 201703L /* C++17 */
#include <any>
#include <optional>
#include <variant>
std::variant<int, float> var = 42; // can hold either int or float
std::optional<int> o = 17;         // can hold an int or nothing (`std::nullopt`)
std::any a = 3.14;                 // can hold any type (similar to `void*`)
#endif

#if __cplusplus >= 202002L /* C++20 */
#include <span>
std::span<int> sp(v); // Non-owning reference to a contiguous sequence of ints
#endif

int main() {
    // C++11 also gives us range-based for loops
    for (auto x : v)
        cout << x << " ";

#if __cplusplus >= 201402L  /* C++14 */
    for (auto radius : v) { // C++14 generic lambda expressions
        cout << "radius: " << radius << ", area: " << [radius]() { return pi * radius * radius; }()
             << endl;
    }
#endif

#if __cplusplus >= 202002L /* C++20 */
    cout << "Span: ";
    for (auto x : sp)
        cout << x << " ";
#endif
    return 0;
}
