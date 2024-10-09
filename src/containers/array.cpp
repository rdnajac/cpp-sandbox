#include <iostream>
#include <vector>
#include <unordered_set>
#include <algorithm>

/**
 * @brief Traverses two arrays based on their values and returns the path taken.
 * 
 * This function performs a traversal through arrayA and arrayB, where each value
 * in the arrays represents an index to jump to in the other array. The traversal
 * continues until a cycle is detected (i.e., we revisit an index in arrayA).
 * 
 * @param arrayA The first array of integers (1-based indexing)
 * @param arrayB The second array of integers (1-based indexing)
 * @return std::vector<int> The sequence of indices visited in arrayB (1-based indexing)
 */
std::vector<int> solution1(const std::vector<int>& arrayA, const std::vector<int>& arrayB) {
    std::vector<int> result;  // Stores the sequence of visited indices in arrayB
    std::unordered_set<int> visitedA;  // Keeps track of visited indices in arrayA
    int index = 0;  // Starting index for arrayA (0-based)

    // Continue traversal until we revisit an index in arrayA
    while (visitedA.find(index) == visitedA.end()) {
        // Mark current index in arrayA as visited
        visitedA.insert(index);

        // Get the value from arrayA and convert to 0-based index for arrayB
        int indexB = arrayA[index] - 1;

        // Store the 1-based index of arrayB in the result
        result.push_back(indexB + 1);

        // Get the next index for arrayA from arrayB (convert to 0-based)
        index = arrayB[indexB] - 1;
    }

    return result;
}

/**
 * @brief Traverses three arrays alternately and returns the sum of maximum values from arrayB and arrayC.
 * 
 * This function alternates between arrayB and arrayC based on indices from arrayA.
 * It keeps track of the maximum values encountered in arrayB and arrayC during the traversal.
 * The traversal stops when a cycle is detected or an out-of-bounds index is encountered.
 * 
 * @param arrayA The first array of integers (1-based indexing)
 * @param arrayB The second array of integers
 * @param arrayC The third array of integers
 * @return int The sum of maximum values encountered in arrayB and arrayC
 */
int solution2(const std::vector<int> &arrayA, const std::vector<int> &arrayB, const std::vector<int> &arrayC) {
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

/**
 * @brief Traverses three arrays in a specific pattern and returns the sum of maximum values from arrayB and arrayC.
 * 
 * This function follows a pattern of arrayA -> arrayB -> arrayA -> arrayC, repeating until a cycle is detected
 * or an out-of-bounds index is encountered. It keeps track of the maximum values in arrayB and arrayC.
 * 
 * @param arrayA The first array of integers (0-based indexing)
 * @param arrayB The second array of integers
 * @param arrayC The third array of integers
 * @return int The sum of maximum values encountered in arrayB and arrayC
 */
int solution3(const std::vector<int> &arrayA, const std::vector<int> &arrayB, const std::vector<int> &arrayC) {
    int maxB = 0;  // Maximum value encountered in arrayB
    int maxC = 0;  // Maximum value encountered in arrayC
    int indexA = 0;  // Start with index 0 in arrayA
    
    // Separate sets to track visited indices in each array
    std::unordered_set<int> visitedA, visitedB, visitedC;

    while (true) {
        // Check arrayA
        if (indexA < 0 || indexA >= arrayA.size() || visitedA.find(indexA) != visitedA.end()) {
            break;
        }
        visitedA.insert(indexA);
        int valueA = arrayA[indexA];

        // Move to arrayB
        if (valueA < 0 || valueA >= arrayB.size() || visitedB.find(valueA) != visitedB.end()) {
            break;
        }
        visitedB.insert(valueA);
        maxB = std::max(maxB, arrayB[valueA]);
        indexA = arrayB[valueA];

        // Check arrayA again
        if (indexA < 0 || indexA >= arrayA.size() || visitedA.find(indexA) != visitedA.end()) {
            break;
        }
        visitedA.insert(indexA);
        valueA = arrayA[indexA];

        // Move to arrayC
        if (valueA < 0 || valueA >= arrayC.size() || visitedC.find(valueA) != visitedC.end()) {
            break;
        }
        visitedC.insert(valueA);
        maxC = std::max(maxC, arrayC[valueA]);
        indexA = arrayC[valueA];
    }

    return maxB + maxC;  // Return the sum of maximum values from arrayB and arrayC
}

// Helper function to print a vector
void printVector(const std::vector<int>& vec, const std::string& name) {
    std::cout << name << " = [";
    for (size_t i = 0; i < vec.size(); ++i) {
        std::cout << vec[i];
        if (i < vec.size() - 1) std::cout << ", ";
    }
    std::cout << "]\n";
}

int main() {
    // Test cases
    std::vector<int> arrayA1 = {2, 1};
    std::vector<int> arrayB1 = {1, 2};
    
    std::vector<int> arrayA2 = {1, 3, 4, 2, 5};
    std::vector<int> arrayB2 = {5, 3, 2, 4, 1};
    std::vector<int> arrayC2 = {1, 5, 3, 2, 4};

    // Test solution1
    std::cout << "Testing solution1:\n";
    printVector(arrayA1, "Array A");
    printVector(arrayB1, "Array B");
    std::vector<int> result1 = solution1(arrayA1, arrayB1);
    printVector(result1, "Result");
    std::cout << "\n";

    // Test solution2
    std::cout << "Testing solution2:\n";
    printVector(arrayA2, "Array A");
    printVector(arrayB2, "Array B");
    printVector(arrayC2, "Array C");
    int result2 = solution2(arrayA2, arrayB2, arrayC2);
    std::cout << "Result: " << result2 << "\n\n";

    // Test solution3
    std::cout << "Testing solution3:\n";
    printVector(arrayA2, "Array A");
    printVector(arrayB2, "Array B");
    printVector(arrayC2, "Array C");
    int result3 = solution3(arrayA2, arrayB2, arrayC2);
    std::cout << "Result: " << result3 << "\n";

    return 0;
}