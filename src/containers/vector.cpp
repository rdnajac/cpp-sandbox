#include "rng.hpp"   // Include RNG library
#include "timer.hpp" // Include Timer library
#include <algorithm>
#include <cmath>
#include <iostream>
#include <map>
#include <string>
#include <vector>

/**
 * @brief Checks if a character is alphanumeric.
 *
 * @param c The character to check.
 * @return true if the character is alphanumeric, false otherwise.
 */
bool isAlphaNumeric(char c) {
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9');
}

/**
 * @brief Encodes a character by shifting it back by one, with wraparound.
 *
 * @param c The character to encode.
 * @return The encoded character.
 */
char encode(char c) {
    if (!isAlphaNumeric(c))
        return c;
    if (c == 'a')
        return 'z';
    if (c == 'A')
        return 'Z';
    if (c == '0')
        return '9';
    return c - 1;
}

/**
 * @brief Processes a vector of integers according to specific rules.
 *
 * This function uses the following STL containers and algorithms:
 * - std::vector<int>: Dynamic array to store integers
 * - std::map<int, int>: Associative container to store frequency of numbers
 *
 * @param numbers Input vector of integers.
 * @return Processed vector of integers.
 */
std::vector<int> solution1(const std::vector<int> &numbers) {
    std::vector<int> result;
    std::vector<int> firstpass;

    Timer timer;   // Create Timer instance
    timer.start(); // Start timing

    // Step 1: Modify input numbers
    for (auto i : numbers) {
        if (i % 10 == 0)
            firstpass.push_back(1);
        else
            firstpass.push_back(i + 1);
    }

    // Step 2: Count frequency of each number
    std::map<int, int> freq;
    for (auto i : firstpass)
        freq[i]++;

    // Step 3: Create result vector
    for (const auto &pair : freq)
        result.push_back(pair.first * pair.second);

    timer.logTime("Solution1 Processing Time"); // Log the processing time
    return result;
}

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
 * @brief Processes a sentence and returns a vector of integers.
 *
 * This function uses the following STL containers and algorithms:
 * - std::string: Sequence container to store and process characters
 * - std::map<char, int>: Associative container to store character frequencies
 * - std::vector<int>: Dynamic array to store result integers
 * - std::sort: Algorithm to sort the result vector
 *
 * @param sentence Input string (sentence).
 * @return Vector of integers representing processed data.
 */
std::vector<int> solution3(const std::string &sentence) {
    std::string encoded_str = "";
    std::map<char, int> freq;

    Timer timer;   // Create Timer instance
    timer.start(); // Start timing

    // Step 1: Encode the string
    for (char c : sentence) {
        char encoded_char = encode(c);
        encoded_str += encoded_char;
    }

    // Step 2: Count frequencies of alphanumeric characters
    for (char c : encoded_str) {
        if (isAlphaNumeric(c)) {
            freq[c]++;
        }
    }

    // Step 3: Compute absolute differences
    std::vector<int> result;
    for (const auto &pair : freq) {
        char c = pair.first;
        int frequency = pair.second;
        int ascii_value = static_cast<int>(c);
        result.push_back(std::abs(ascii_value - frequency));
    }

    // Step 4: Sort the differences in ascending order
    std::sort(result.begin(), result.end());

    timer.logTime("Solution3 Processing Time"); // Log the processing time
    return result;
}

/**
 * @brief Tests solution1 function.
 */
void test_solution1() {
    RandomNumberGenerator rng; // Create RNG instance
    std::vector<int> input;

    // Generate random input values
    for (int i = 0; i < 10; ++i) {
        input.push_back(rng.getRandomNumber() % 100); // Limit values for simplicity
    }

    std::vector<int> output = solution1(input);
    std::cout << "Solution 1 Test:\nInput: ";
    for (int i : input)
        std::cout << i << " ";
    std::cout << "\nOutput: ";
    for (int i : output)
        std::cout << i << " ";
    std::cout << "\n\n";
}

/**
 * @brief Tests solution2 function.
 */
void test_solution2() {
    std::string input = "hello world";
    std::map<char, int> output = solution2(input);
    std::cout << "Solution 2 Test:\nInput: " << input << "\nOutput:\n";
    for (const auto &pair : output) {
        std::cout << pair.first << ": " << pair.second << "\n";
    }
    std::cout << "\n";
}

/**
 * @brief Tests solution3 function.
 */
void test_solution3() {
    std::string input = "Hello, World! 123";
    std::vector<int> output = solution3(input);
    std::cout << "Solution 3 Test:\nInput: " << input << "\nOutput: ";
    for (int i : output)
        std::cout << i << " ";
    std::cout << "\n\n";
}

// Main function for testing
int main() {
    test_solution1();
    test_solution2();
    test_solution3();
    return 0;
}
