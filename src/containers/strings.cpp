#include <algorithm>
#include <cctype>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

// Define a struct to represent a sea creature
struct SeaCreature {
    std::string name;
    int appendages;
};

/**
 * @brief Splits a string into a vector of substrings using a specified delimiter
 *
 * This function uses std::istringstream to efficiently split the string.
 *
 * @param s The input string to split
 * @param delimiter The character to use as a delimiter
 * @return std::vector<std::string> A vector containing the split substrings
 */
std::vector<std::string> split(const std::string &s, char delimiter) {
    std::vector<std::string> tokens;
    std::istringstream tokenStream(s);
    std::string token;
    while (std::getline(tokenStream, token, delimiter)) {
        tokens.push_back(token);
    }
    return tokens;
}

/**
 * @brief Processes sea creature data and outputs their names and appendages
 *
 * This function demonstrates the use of std::vector, std::string, and string-to-integer conversion.
 *
 * @param data A string containing sea creature data in the format
 * "name,appendages;name,appendages;..."
 */
void processSeaCreatures(const std::string &data) {
    std::vector<SeaCreature> creatures;
    auto entries = split(data, ';'); // Split by semicolon to get each creature's data
    for (const auto &entry : entries) {
        auto details = split(entry, ','); // Split by comma to get name and appendages
        if (details.size() == 2) {
            SeaCreature creature;
            creature.name = details[0];
            creature.appendages = std::stoi(details[1]); // Convert string to int
            creatures.push_back(creature);               // Add to vector
        }
    }
    // Output the sea creatures and their appendages
    for (const auto &creature : creatures) {
        std::cout << "Creature: " << creature.name << ", Appendages: " << creature.appendages
                  << std::endl;
    }
}

/**
 * @brief Transforms a character to its "opposite" in the alphabet
 *
 * For lowercase letters, it transforms 'a' to 'z', 'b' to 'y', etc.
 * For uppercase letters, it transforms 'A' to 'Z', 'B' to 'Y', etc.
 *
 * @param c The character to transform (passed by reference)
 */
void transform_to_opposite(char &c) {
    if (std::islower(c))
        c = 'z' - c + 'a'; // 122 - (int)c + 97
    else if (std::isupper(c))
        c = 'Z' - c + 'A'; // 90 - (int)c + 65
}

/**
 * @brief Transforms each word in the input string by applying transform_to_opposite to each
 * character
 *
 * This function demonstrates the use of std::istringstream for string splitting,
 * std::for_each for applying a function to each element of a container,
 * and string manipulation.
 *
 * @param str The input string to transform
 * @return std::string The transformed string
 */
std::string test1(const std::string &str) {
    std::string result;
    std::istringstream iss(str);
    std::string word;
    while (iss >> word) {
        std::for_each(word.begin(), word.end(), transform_to_opposite);
        result += word + " ";
    }
    if (!result.empty()) {
        result.pop_back();
    }
    return result;
}

int main() {
    // Test processSeaCreatures function
    std::string seaCreatureData = "Octopus,8;Starfish,5;Crab,10;Squid,10";
    std::cout << "Processing sea creature data:\n";
    processSeaCreatures(seaCreatureData);

    std::cout << "\nTesting string transformation:\n";
    std::cout << "Input: \"abc 123 def 456\"\n";
    std::cout << "Output: \"" << test1("abc 123 def 456") << "\"\n";

    return 0;
}