#include "rng.hpp"   // Include RNG library
#include "timer.hpp" // Include Timer library
#include <algorithm>
#include <iostream>
#include <map>
#include <string>
#include <vector>

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

    Timer timer;   // Create Timer instance
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

        Timer timer;   // Create Timer instance
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

#if 0
int main() {
    std::unordered_map<std::string, int> fruit_basket = {{"apples", 5}, {"bananas", 4}, {"oranges", 8}};
    // An unordered_map representing our fruit basket

    // Summing the values
    int total_fruits = 0;
    for (const auto& pair : fruit_basket) {
        total_fruits += pair.second;
    }

    // Finding the maximum value
    auto max_fruit = std::max_element(fruit_basket.begin(), fruit_basket.end(),
        [](const auto& a, const auto& b) {
            return a.second < b.second;
        })->first;
    
    std::cout << "The fruit with the most quantity is: " << max_fruit << std::endl;
    // It outputs: "The fruit with the most quantity is: oranges"

    // Finding the minimum value
    auto min_fruit = std::min_element(fruit_basket.begin(), fruit_basket.end(),
        [](const auto& a, const auto& b) {
            return a.second < b.second;
        })->first;

    std::cout << "The fruit with the least quantity is: " << min_fruit << std::endl;
    // It outputs: "The fruit with the least quantity is: bananas"
    // Calculating the average
    double average_fruits = static_cast<double>(total_fruits) / fruit_basket.size();
    std::cout << "The average number of each type of fruit in the basket is: " << average_fruits << std::endl;
    // It outputs: "The average number of each type of fruit in the basket is: 5.67"

    return 0;
}
#endif
