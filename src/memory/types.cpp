#include <string>
#include <sstream>
#include <vector>
#include <cctype>
#include <iostream>

/**
 * @brief Transforms a given string based on certain rules.
 * 
 * This function takes a string containing words and numbers separated by dashes ('-').
 * - If a segment is a number between 1 and 26, it is converted to the corresponding
 *   lowercase letter (1 -> 'a', 2 -> 'b', ..., 26 -> 'z').
 * - If a segment is a single lowercase letter, it is converted to its position in the
 *   alphabet (e.g., 'a' -> "1", 'b' -> "2").
 * 
 * The segments are then combined back into a string, with segments separated by dashes.
 * 
 * @param s The input string to be transformed.
 * @return A new string with the transformations applied.
 */
std::string solution(const std::string& s) {
    std::stringstream ss(s); ///< String stream to parse the input string
    std::string word; ///< Variable to hold each segment
    std::vector<std::string> new_words; ///< Vector to store transformed segments

    // Process each segment of the input string
    while (std::getline(ss, word, '-')) {
        if (!word.empty() && std::all_of(word.begin(), word.end(), ::isdigit)) {
            // Convert valid number segments (1-26) to corresponding letters
            int num = std::stoi(word);
            if (num >= 1 && num <= 26) {
                new_words.push_back(std::string(1, 'a' + num - 1)); // char to string
            }
        } else if (word.length() == 1 && std::islower(word[0])) {
            // Convert single lowercase letters to their position in the alphabet
            new_words.push_back(std::to_string(word[0] - 'a' + 1)); // char to string conversion
        }
    }

    // Construct the resulting string from transformed segments
    std::string result;
    for (size_t i = 0; i < new_words.size(); ++i) {
        result += new_words[i]; // Concatenate transformed segments
        if (i + 1 < new_words.size()) {
            result += "-"; // Add dash between segments
        }
    }
    
    return result; // Return the transformed string
}

int main() {
    std::string input = "1-2-3-4";
    std::string output = solution(input);
    std::cout << "Input: " << input << std::endl;
    std::cout << "Output: " << output << std::endl;
}
