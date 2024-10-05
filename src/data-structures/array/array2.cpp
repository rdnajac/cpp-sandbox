#include "solution.hpp"
#include <vector>
#include <unordered_set>
#include <algorithm>

int solution(const std::vector<int> &arrayA, const std::vector<int> &arrayB, const std::vector<int> &arrayC) {
    int maxB = 0;  // Maximum value encountered in arrayB
    int maxC = 0;  // Maximum value encountered in arrayC
    int index = 0;  // Current index in arrayA
    std::unordered_set<int> visitedIndices;  // Set to track visited indices in arrayA
    bool isB = true;  // Flag to alternate between arrayB and arrayC

    while (true) {
        // Check if we've visited this index in arrayA before or if it's out of bounds
        if (index < 0 || index >= arrayA.size() || visitedIndices.find(index) != visitedIndices.end()) {
            break;  // Exit the loop if we're in a cycle or out of bounds
        }

        visitedIndices.insert(index);  // Mark this index as visited

        int nextIndex = arrayA[index] - 1;  // Get the next index from arrayA (convert to 0-based)

        // Update maxB or maxC based on which array we're visiting
        if (isB) {
            if (nextIndex >= 0 && nextIndex < arrayB.size()) {
                maxB = std::max(maxB, arrayB[nextIndex]);
            } else {
                break;  // Exit if we're out of bounds in arrayB
            }
        } else {
            if (nextIndex >= 0 && nextIndex < arrayC.size()) {
                maxC = std::max(maxC, arrayC[nextIndex]);
            } else {
                break;  // Exit if we're out of bounds in arrayC
            }
        }

        index = nextIndex;  // Move to the next index in arrayA
        isB = !isB;  // Toggle between arrayB and arrayC
    }

    return maxB + maxC;  // Return the sum of maximum values from arrayB and arrayC
}
