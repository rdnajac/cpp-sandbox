#include "solution.hpp"
#include <vector>
#include <unordered_set>
#include <algorithm>

int solution(const std::vector<int> &arrayA, const std::vector<int> &arrayB, const std::vector<int> &arrayC) {
    int maxB = 0;  // Maximum value encountered in arrayB
    int maxC = 0;  // Maximum value encountered in arrayC
    int indexA = 0;  // Start with index 0 in arrayA
    
    // Separate sets to track visited indices in each array
    std::unordered_set<int> visitedA, visitedB, visitedC;

    // print each array in a formatted line
    cout << "Array A = [";
    for (int i = 0; i < arrayA.size(); i++) {
        std::cout << arrayA[i] << ", ";
    }
    cout << "]\nArray B = [";
    std::cout << std::endl;
    for (int i = 0; i < arrayB.size(); i++) {
        std::cout << arrayB[i] << " ";
    }
    cout << "]\nArray C = [";
    std::cout << std::endl;
    for (int i = 0; i < arrayC.size(); i++) {
        std::cout << arrayC[i] << " ";
    }
    std::cout << std::endl;
    
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
