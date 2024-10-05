#include <map>
#include <string>

std::map<char, int> solution(const std::string &s) {
    std::map<char, int> result;
    std::map<char, int> frequency;

    // Count frequency of each character
    for (char c : s) {
        frequency[c]++;
    }

    // Calculate the numerical representation for each character
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

    return result;
}
