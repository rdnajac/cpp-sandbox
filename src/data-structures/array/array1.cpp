#include <vector>
#include <unordered_set>

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
std::vector<int> solution(const std::vector<int>& arrayA, const std::vector<int>& arrayB) {
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
