#include <algorithm>
#include <iostream>
#include <vector>

int main() {
    std::vector<int> v = {10, 20, 30, 30, 20, 10, 10, 20};

    std::sort(v.begin(), v.end());

    // Use lower_bound to find the first position of 20
    auto low = std::lower_bound(v.begin(), v.end(), 20);
    // Use upper_bound to find the position just after the last occurrence of 20
    auto up = std::upper_bound(v.begin(), v.end(), 20);

    // Output the results
    std::cout << "Sorted vector: ";
    for (const auto &num : v) {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    std::cout << "lower_bound of 20 at position: " << (low - v.begin()) << std::endl;
    std::cout << "upper_bound of 20 at position: " << (up - v.begin()) << std::endl;

    return 0;
}
