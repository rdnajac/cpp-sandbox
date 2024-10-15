#include <iostream>
#include <unordered_set>
#include <vector>

/**
 * @brief Demonstrates the use of std::unordered_set in C++.
 *
 * This program showcases various operations provided by the std::unordered_set container,
 * including insertion, removal, membership checking, and size retrieval.
 * It also illustrates how to find common elements between two vectors using unordered sets.
 */

/**
 * @brief Finds common elements between two vectors using unordered_set.
 *
 * This function takes two vectors of unique integers and returns a vector containing
 * the common elements found in both input vectors.
 *
 * @param list1 The first vector of integers.
 * @param list2 The second vector of integers.
 * @return A vector containing the common elements.
 */
std::vector<int> common_elements(const std::vector<int> &list1, const std::vector<int> &list2) {
    std::unordered_set<int> set1(list1.begin(), list1.end());
    std::vector<int> common;

    for (const int &num : list2) {
        if (set1.find(num) != set1.end()) {
            common.push_back(num);
        }
    }

    return common;
}

int main() {
    // Create an unordered_set and demonstrate its functionality
    std::unordered_set<int> my_set = {1, 2, 3, 4, 5};

    // Insertion
    my_set.insert(6); // Average time complexity: O(1)
    my_set.insert(3); // No effect, 3 is already present

    std::cout << "Contents of the unordered_set after insertions: ";
    for (const int &elem : my_set) {
        std::cout << elem << " "; // Order may vary
    }
    std::cout << std::endl;

    // Membership Check
    std::cout << "Does the set contain 3? " << (my_set.find(3) != my_set.end() ? "Yes" : "No")
              << std::endl; // O(1)
    std::cout << "Does the set contain 7? " << (my_set.find(7) != my_set.end() ? "Yes" : "No")
              << std::endl; // O(1)

    // Size
    std::cout << "Size of the unordered_set: " << my_set.size() << std::endl; // O(1)

    // Removal
    my_set.erase(2); // Average time complexity: O(1)
    std::cout << "Contents after removing 2: ";
    for (const int &elem : my_set) {
        std::cout << elem << " "; // Order may vary
    }
    std::cout << std::endl;

    // Clear the set
    my_set.clear(); // Average time complexity: O(n)
    std::cout << "Size after clearing the set: " << my_set.size() << std::endl; // O(1)

    // Example usage of common_elements function
    std::vector<int> list1 = {1, 2, 3, 5, 8, 13, 21, 34};
    std::vector<int> list2 = {2, 3, 5, 7, 13, 21, 31};
    std::vector<int> result = common_elements(list1, list2);

    std::cout << "Common elements between list1 and list2: ";
    for (const int &elm : result) {
        std::cout << elm << " "; // Output: 2 3 5 13 21
    }
    std::cout << std::endl;

    return 0;
}
