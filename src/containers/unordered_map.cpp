#include <iostream>
#include <vector>
#include <unordered_map>
#include <limits>

/**
 * @brief Demonstrates the use of std::unordered_map in C++.
 *
 * This program showcases the efficiency of unordered maps for tracking element occurrences
 * and calculating maximum block sizes in a vector.
 * It includes both a brute force and an optimized approach to solving the problem of
 * minimizing the maximum block size after removing a specified integer from the vector.
 */

/**
 * @brief Finds the integer that, when removed, minimizes the maximum length of contiguous blocks.
 *
 * This function iterates over the vector to calculate the size of blocks formed when removing
 * each distinct integer and returns the integer that results in the smallest maximum block size.
 *
 * @param vec The vector of integers.
 * @return The integer that minimizes the maximum block size when removed.
 */
int minimal_max_block(const std::vector<int>& vec) {
    std::unordered_map<int, int> last_occurrence;
    std::unordered_map<int, int> max_block_sizes;

    // Traverse the vector
    for (size_t i = 0; i < vec.size(); ++i) {
        int num = vec[i];

        // If it's the first occurrence, consider the block from the start to current position
        if (last_occurrence.find(num) == last_occurrence.end()) {
            max_block_sizes[num] = i; // Initial block size
        } else {
            // Calculate block size excluding the number itself
            int block_size = i - last_occurrence[num] - 1;
            max_block_sizes[num] = std::max(max_block_sizes[num], block_size);
        }

        // Update the last occurrence index
        last_occurrence[num] = i;
    }

    // Handle tail blocks
    for (const auto& entry : last_occurrence) {
        int num = entry.first;
        int pos = entry.second;
        int block_size = vec.size() - pos - 1; // Tail block size
        max_block_sizes[num] = std::max(max_block_sizes[num], block_size);
    }

    // Find the number with the smallest maximum block size
    int min_num = -1;
    int min_block_size = std::numeric_limits<int>::max();
    for (const auto& entry : max_block_sizes) {
        if (entry.second < min_block_size) {
            min_block_size = entry.second;
            min_num = entry.first;
        }
    }

    return min_num;
}

/**
 * @brief A brute force approach to find the integer that minimizes the maximum block size.
 *
 * This function examines every unique integer in the vector and calculates the maximum
 * size of blocks formed by removing that integer.
 *
 * @param vec The vector of integers.
 * @return The integer that minimizes the maximum block size when removed.
 */
int minimal_max_block_bruteforce(const std::vector<int>& vec) {
    int min_max_block_size = std::numeric_limits<int>::max();
    int min_num = -1;

    std::unordered_map<int, int> unique_elements;
    for (int num : vec) {
        unique_elements[num]++;
    }

    for (const auto& entry : unique_elements) {
        int num = entry.first;
        std::vector<int> indices;
        
        // Collect indices of the current number
        for (size_t i = 0; i < vec.size(); ++i) {
            if (vec[i] == num) {
                indices.push_back(i);
            }
        }

        indices.insert(indices.begin(), -1);
        indices.push_back(vec.size());

        int max_block_size = 0;
        for (size_t i = 1; i < indices.size(); ++i) {
            max_block_size = std::max(max_block_size, indices[i] - indices[i - 1] - 1);
        }

        if (max_block_size < min_max_block_size) {
            min_max_block_size = max_block_size;
            min_num = num;
        }
    }

    return min_num;
}

int main() {
    std::vector<int> vec = {1, 2, 2, 3, 1, 4, 4, 4, 1, 2, 5};

    std::cout << "Brute Force Result: " << minimal_max_block_bruteforce(vec) << std::endl;
    std::cout << "Optimized Result: " << minimal_max_block(vec) << std::endl;

    return 0;
}
