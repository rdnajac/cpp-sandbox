#include <iostream>
#include <vector>

std::string solution(std::string sentence) {
    std::vector<std::string> words;
    std::string word = "";
    for (char c : sentence) {
        if (c == ' ') {
            words.push_back(word);
            word = "";
        } else {
            word += c;
        }
    }
    words.push_back(word); // add the last word

    std::string result;
    for (std::string word : words) {
        if (word.size() % 2 == 0) {                    // confirms if the length of the word is even
            for (int i = 1; i < word.size(); i += 2) { // loop over odd-indexed characters
                result += word[i];
            }
        }
    }
    return result;
}

int main() {
    std::cout << solution("Cplusplus is a high-level programming language.");
    return 0;
}