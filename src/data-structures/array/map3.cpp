#include "solution.hpp"
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <cmath>

bool isAlphaNumeric(char c) {
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9');
}

char encode(char c) {
    if (!isAlphaNumeric(c))
        return c;
    if (c == 'a') return 'z';
    if (c == 'A') return 'Z';
    if (c == '0') return '9';
    return c - 1;
}

std::vector<int> solution(const std::string& sentence) {
    std::string encoded_str = "";
    std::map<char, int> freq;

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
    for (const auto& pair : freq) {
        char c = pair.first;
        int frequency = pair.second;
        int ascii_value = static_cast<int>(c);
        result.push_back(std::abs(ascii_value - frequency));
    }

    // Step 4: Sort the differences in ascending order
    std::sort(result.begin(), result.end());

    return result;
}
