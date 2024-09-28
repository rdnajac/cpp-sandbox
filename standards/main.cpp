#include <iostream>

#ifndef __cplusplus
#error "This is not a C++ compiler"
#elif __cplusplus < 201103L
#error "This compiler does not support C++11 or later"
#endif

// C++11 feature: auto
void cpp11_feature() {
  auto x = 5;
  std::cout << "C++11 feature (auto): " << x << std::endl;
}

#if __cplusplus >= 201402L
// C++14 feature: generic lambda
void cpp14_feature() {
  auto lambda = [](auto x, auto y) { return x + y; };
  std::cout << "C++14 feature (generic lambda): " << lambda(3, 4.5)
            << std::endl;
}
#endif

#if __cplusplus >= 201703L
#include <any>
#include <optional>
#include <variant>

// C++17 feature: variant, optional, and any
void cpp17_feature() {
  std::variant<int, float> v = 42;
  std::optional<int> o = 17;
  std::any a = 3.14;

  std::cout << "C++17 features:\n";
  std::cout << "  variant: " << std::get<int>(v) << std::endl;
  std::cout << "  optional: " << *o << std::endl;
  std::cout << "  any: " << std::any_cast<double>(a) << std::endl;
}
#endif

#if __cplusplus >= 202002L
#include <array>
#include <span>

// C++20 feature: span
void cpp20_feature() {
  std::array<int, 5> arr = {1, 2, 3, 4, 5};
  std::span<int> sp(arr);

  std::cout << "C++20 feature (span): ";
  for (int i : sp) {
    std::cout << i << " ";
  }
  std::cout << std::endl;
}
#endif

int main() {
  cpp11_feature();

#if __cplusplus >= 201402L
  cpp14_feature();
#endif

#if __cplusplus >= 201703L
  cpp17_feature();
#endif

#if __cplusplus >= 202002L
  cpp20_feature();
#endif

  return 0;
}
