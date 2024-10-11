#include <algorithm> // for std::transform
#include <iostream>
#include <utility> // for std::pair
#include <vector>

/**
 * @brief Demonstrates move and copy operations with vectors in C++.
 *
 * This program creates a vector of integers, then generates a new vector of pairs
 * consisting of original and transformed values (squared). It also prints out memory
 * addresses to illustrate the move and copy behavior of vectors.
 */
int main() {
    // Original vector
    std::vector<int> original = {1, 2, 3, 4, 5};

    // Print original vector's memory address
    std::cout << "Original vector memory address: " << &original << std::endl;

    // Transformed vector: squaring the original vector
    std::vector<int> transformed;
    std::transform(original.begin(), original.end(), std::back_inserter(transformed),
                   [](int x) { return x * x; });

    // Print transformed vector's memory address
    std::cout << "Transformed vector memory address: " << &transformed << std::endl;

    // Create a vector of pairs from original and transformed vectors
    std::vector<std::pair<int, int>> pairs;
    for (size_t i = 0; i < original.size(); ++i) {
        pairs.emplace_back(original[i], transformed[i]);
    }

    // Print pairs and their memory addresses
    std::cout << "Pairs (original, transformed):" << std::endl;
    for (const auto &p : pairs) {
        std::cout << "Original: " << p.first << ", Transformed: " << p.second << std::endl;
    }

    // Print memory addresses of the pairs vector
    std::cout << "Pairs vector memory address: " << &pairs << std::endl;

    // Demonstrate move operation
    std::vector<std::pair<int, int>> moved_pairs = std::move(pairs);

    // Show that the pairs vector is now empty after the move
    std::cout << "After move operation, original pairs vector size: " << pairs.size() << std::endl;
    std::cout << "Moved pairs vector size: " << moved_pairs.size() << std::endl;

    // Print moved pairs
    std::cout << "Moved pairs (original, transformed):" << std::endl;
    for (const auto &p : moved_pairs) {
        std::cout << "Original: " << p.first << ", Transformed: " << p.second << std::endl;
    }

    return 0;
}
