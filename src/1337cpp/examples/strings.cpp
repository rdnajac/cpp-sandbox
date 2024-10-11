#include <algorithm> // for std::reverse
#include <cctype>    // for std::isupper and std::tolower
#include <iostream>
#include <string>
#include <vector>

using namespace std;

// Function to reverse specified words in the sentences
std::vector<std::string> reverseWords(const std::vector<std::string> &sentences,
                                      const std::vector<std::string> &words) {
    vector<string> result = sentences;

    for (size_t i = 0; i < sentences.size(); ++i) {
        string &sentence = result[i];
        const string &word = words[i];

        // Reverse the word
        string reversed_word = word;
        reverse(reversed_word.begin(), reversed_word.end());

        size_t pos = 0;
        while ((pos = sentence.find(word, pos)) != std::string::npos) {
            // Replace the word with its reversed version
            sentence.replace(pos, word.length(), reversed_word);
            pos += reversed_word.length(); // Move past the new substring
        }
    }

    return result;
}

// Function to reverse words and handle capitalization
std::vector<std::string> reverseWordsWithCapitalization(const std::vector<std::string> &sentences,
                                                        const std::vector<std::string> &words) {
    vector<string> result = sentences;

    for (size_t i = 0; i < sentences.size(); ++i) {
        string &sentence = result[i];
        const string &word = words[i];

        // Reverse the word
        string reversed_word = word;
        reverse(reversed_word.begin(), reversed_word.end());

        // Create a capitalized version of the word
        string capitalized_word = word;
        capitalized_word[0] = toupper(capitalized_word[0]);

        size_t pos = 0;
        while ((pos = sentence.find(word, pos)) != std::string::npos) {
            // Reset the first letter of the reversed word for each occurrence
            reversed_word[0] = std::isupper(sentence[pos]) ? std::toupper(reversed_word[0])
                                                           : std::tolower(reversed_word[0]);

            // Replace the word with its reversed version
            sentence.replace(pos, word.length(), reversed_word);
            pos += reversed_word.length(); // Move past the new substring
        }

        pos = 0;
        while ((pos = sentence.find(capitalized_word, pos)) != std::string::npos) {
            // Reset the first letter of the reversed word for each occurrence
            reversed_word[0] = std::isupper(sentence[pos]) ? std::toupper(reversed_word[0])
                                                           : std::tolower(reversed_word[0]);

            // Replace the word with its reversed version
            sentence.replace(pos, capitalized_word.length(), reversed_word);
            pos += reversed_word.length(); // Move past the new substring
        }
    }

    return result;
}

int main() {
    // Example sentences and words
    vector<string> sentences = {"Hello world", "C++ is fun"};
    vector<string> words = {"world", "fun"};

    // Call the first function
    vector<string> reversed_sentences = reverseWords(sentences, words);
    cout << "Reversed words output:\n";
    for (const auto &sentence : reversed_sentences) {
        cout << sentence << endl;
    }

    // Call the second function
    vector<string> capitalized_reversed_sentences =
        reverseWordsWithCapitalization(sentences, words);
    cout << "\nCapitalized reversed words output:\n";
    for (const auto &sentence : capitalized_reversed_sentences) {
        cout << sentence << endl;
    }

    return 0;
}
