#include <algorithm>
#include <vector>
#include <map>
#include <string>
#include <iostream>

std::vector<int> character_frequency_encoding(std::string word) {
    // Step 1: Mapping each character to the next alphabetical character
    std::string next_string = "";
    for (char & letter : word) {
        next_string += (letter == 'z' ? 'a' : letter + 1);
    }

    // Step 2: Counting the frequency of characters in next_string
    std::map<char, int> frequency_map;
    for (const char & letter : next_string) {
        if (frequency_map.find(letter) != frequency_map.end()) {
            frequency_map[letter]++;
        } else {
            frequency_map[letter] = 1;
        }
    }

    // Step 3: Building the product list
    std::vector<int> combined_values;
    for (const auto & item : frequency_map) {
        combined_values.push_back(static_cast<int>(item.first) * item.second);
    }

    // Step 4: Sorting the final values in descending order
    std::sort(combined_values.begin(), combined_values.end(), std::greater<int>());

    // Return the sorted list
    return combined_values;
}

// Example
int main() {
    std::string word = "banana";
    std::vector<int> result = character_frequency_encoding(word);
    for(int value : result) {
        std::cout << value << " ";
    }
    return 0;
}