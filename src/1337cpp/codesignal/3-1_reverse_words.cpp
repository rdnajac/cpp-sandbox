#include <algorithm> //for std::reverse
#include <iostream>  //for std::cout and std::endl
#include <sstream>   //for std::istringstream and std::ostringstream
#include <vector>    //for std::vector

std::string reverseWords(std::string input_str) {
    std::vector<std::string> words;
    std::istringstream iss(input_str);

    for (std::string s; iss >> s;)
        words.push_back(s);

    std::vector<std::string> reversed_words;

    for (auto &word : words) {
        std::reverse(word.begin(), word.end());
        reversed_words.push_back(word);
    }

    std::ostringstream oss;
    oss << reversed_words[0]; // add first word

    for (int i = 1; i < reversed_words.size(); i++)
        oss << " " << reversed_words[i]; // add the remaining words with space

    return oss.str();
}

int main() {
    // Call the function
    std::cout << reverseWords("Hello neat cpp_lovers_123")
              << std::endl; // prints: 'olleH taen 321_srevol_ppc'
    return 0;
}