#include <iostream>
#include <map>
#include <string>
#include <algorithm>
#include <vector>
#include "rng.hpp"  // Include RNG library
#include "timer.hpp" // Include Timer library

/**
 * @brief Processes a string and creates a map of characters to integers.
 * 
 * This function uses the following STL containers:
 * - std::map<char, int>: Associative container to store character frequencies and results
 * - std::string: Sequence container to store and process characters
 * 
 * @param s Input string.
 * @return Map of characters to integers.
 */
std::map<char, int> solution2(const std::string &s) {
    std::map<char, int> result;
    std::map<char, int> frequency;

    Timer timer; // Create Timer instance
    timer.start(); // Start timing

    // Step 1: Count frequency of each character
    for (char c : s) {
        frequency[c]++;
    }

    // Step 2 & 3: Calculate numerical representation and store results
    for (const auto &pair : frequency) {
        char original = pair.first;
        int freq = pair.second;

        // Shift the character 3 positions back
        char shifted = original - 3;
        if (shifted < 'a') {
            shifted = 'z' - ('a' - shifted) + 1;
        }

        // Calculate the numerical representation
        int value = static_cast<int>(shifted) * freq;

        // Store the result for the original character
        result[original] = value;
    }

    timer.logTime("Solution2 Processing Time"); // Log the processing time
    return result;
}

/**
 * @brief A class representing a simple map usage for frequency counting.
 */
class CharacterFrequencyMap {
public:
    /**
     * @brief Inserts characters from a string into a frequency map.
     * 
     * @param str The input string.
     * @return A map of character frequencies.
     */
    std::map<char, int> createFrequencyMap(const std::string &str) {
        std::map<char, int> freqMap;

        Timer timer; // Create Timer instance
        timer.start(); // Start timing

        for (char c : str) {
            freqMap[c]++;
        }

        timer.logTime("Create Frequency Map Time"); // Log the processing time
        return freqMap;
    }
};

/**
 * @brief Tests the CharacterFrequencyMap class.
 */
void testCharacterFrequencyMap() {
    CharacterFrequencyMap freqMap;
    std::string input = "hello world";
    
    auto result = freqMap.createFrequencyMap(input);
    std::cout << "Character Frequency Map Test:\nInput: " << input << "\nOutput:\n";
    for (const auto &pair : result) {
        std::cout << pair.first << ": " << pair.second << "\n";
    }
    std::cout << "\n";
}

/**
 * @brief Main function for testing.
 */
int main() {
    testCharacterFrequencyMap();

    // Example usage of solution2
    std::string exampleInput = "aabbccddeeffgghh";
    auto exampleOutput = solution2(exampleInput);
    std::cout << "Example Solution 2 Test:\nInput: " << exampleInput << "\nOutput:\n";
    for (const auto &pair : exampleOutput) {
        std::cout << pair.first << ": " << pair.second << "\n";
    }
    
    return 0;
}
