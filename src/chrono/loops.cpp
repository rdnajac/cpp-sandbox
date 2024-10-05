#include <algorithm>
#include <iomanip>
#include <iostream>
#include <numeric>
#include <vector>

#include "rng.hpp"
#include "timer.hpp"

#include <vector>

/**
 * @brief Solution to the problem
 * @param vec1 First vector
 * @param vec2 Second vector
 * @return A vector of pairs
 */
std::vector<std::pair<int,int>> solution(std::vector<int> vec1, std::vector<int> vec2) {
    std::vector<std::pair<int,int>> result;
    for(auto i : vec1){
        for(auto j : vec2){
            // Our logic goes here
        }
    }
    return result;
}

int main() {
    const int SIZE = 100'000'000;
    std::vector<int> v;
    RandomNumberGenerator rng;

    std::cout << "Generating random numbers..." << std::endl;
    for (int i = 0; i < SIZE; i++) {
        v.push_back(rng.getRandomNumber());
    }

    Timer timer;
    long long sum1 = 0, sum2 = 0, sum3 = 0, sum4 = 0, sum5 = 0;

    timer.start();
    for (int i = 0; i < SIZE; i++) {
        sum1 += v[i];
    }
    timer.logTime("C-style for-loop");

    timer.start();
    for (int i = 0; i < v.size(); i++) {
        sum2 += v[i];
    }
    timer.logTime("C-style for-loop (unsigned)");

    timer.start();
    for (int n : v) {
        sum3 += n;
    }
    timer.logTime("ranged for-loop");

    timer.start();
    std::for_each(v.begin(), v.end(), [&sum4](int n) { sum4 += n; });
    timer.logTime("for_each() with a lambda");

    timer.start();
    sum5 = std::accumulate(v.begin(), v.end(), static_cast<long long>(0));
    timer.logTime("std::accumulate()");

    // Print results
    std::cout << std::left << std::setw(16) << sum1 << std::setw(32)
              << " C-style for-loop:" << timer.getDuration(0) << " ms\n"
              << std::setw(16) << sum2 << std::setw(32)
              << " C-style for-loop (unsigned):" << timer.getDuration(1) << " ms\n"
              << std::setw(16) << sum3 << std::setw(32) << " ranged for-loop "
              << timer.getDuration(2) << " ms\n"
              << std::setw(16) << sum4 << std::setw(32) << " for_each() with a lambda"
              << timer.getDuration(3) << " ms\n"
              << std::setw(16) << sum5 << std::setw(32) << " std::accumulate()"
              << timer.getDuration(4) << " ms\n";

    return 0;
}

// You are provided with two vectors of unique integers, with their lengths ranging from 1 to 100, inclusive. The task is to identify elements that appear in both vectors and return them in a vector, maintaining the order from the first provided vector.

// Each vector's element ranges from -100 to 100, inclusive.

// In your function common_elements(std::vector<int> vecA, std::vector<int> vecB), vecA and vecB represent the two input vectors. The function should return a vector that includes the common elements found in both vecA and vecB, while preserving the order of elements as they appear in vecA.

// You are provided with two vectors of unique integers, with their lengths ranging from 1 to 100, inclusive. The task is to identify elements that appear in both vectors and return them in a vector, maintaining the order from the first provided vector.

// Each vector's element ranges from -100 to 100, inclusive.

// In your function common_elements(std::vector<int> vecA, std::vector<int> vecB), vecA and vecB represent the two input vectors. The function should return a vector that includes the common elements found in both vecA and vecB, while preserving the order of elements as they appear in vecA.
#include <vector>

std::vector<int> common_elements(const std::vector<int>& vecA, const std::vector<int>& vecB) {
    std::vector<int> result;
    for (auto i : vecA) {
        for (auto j : vecB) {
            if (i == j) {
                result.push_back(i);
                break;
            }
        }
    }
    return result;
}

// You are given two arrays: sourceArray and searchArray, consisting of n and m pairs respectively, where n is an integer such that 1 ≤ n ≤ 100 and m is an integer such that 1 ≤ m ≤ 500. Each pair in both arrays consists of an integer identifier and a string. The identifiers in both arrays range from 1 to 100, inclusive. The strings in sourceArray consist of alphanumeric characters with lengths ranging from 1 to 100, inclusive. The strings in searchArray have lengths ranging from 1 to 500, inclusive.
// Your task is to implement a function stringSearch(sourceArray, searchArray) that takes these two arrays as input and returns an array that includes all pairs from sourceArray for which its string is a substring of at least one string in any pair from searchArray and the identifier of the source pair is less than or equal to the identifier of the search pair.



#include "solution.hpp"

std::vector<std::pair<int, std::string>> stringSearch(const std::vector<std::pair<int, std::string>> &sourceArray, const std::vector<std::pair<int, std::string>> &searchArray) {
    std::vector<std::pair<int, std::string>> result;
    for (auto source : sourceArray) {
        for (auto search : searchArray) {
            if (search.second.find(source.second) != std::string::npos && source.first <= search.first) {
                result.push_back(source);
                break;
            }
        }
    }
    return result;
}

#include <utility>

std::vector<std::pair<int, int>> solution(const std::vector<int>& vectorA, const std::vector<int>& vectorB) {
    // TODO: Find the pairs of integers a, b where a belongs to vectorA and b belongs to vectorB such that a is greater than b
    std::vector<std::pair<int, int>> result;
    for (auto i : vectorA)
        for (auto j : vectorB)
            if (i > j) { 
                result.push_back(std::make_pair(i, j));
    return result;
}}

//the first element of each pair comes from the first array
//the second element of each pair comes from the second array,
//such that the sum of the two elements of the pair is a perfect square
std::vector<std::pair<int, int>> solution(const std::vector<int>& arr1, const std::vector<int>& arr2) {
    vector<pair<int, int>> result;
    for (auto i : arr1) {
        for(auto j : arr2) {
            if (sqrt(i + j) == floor(sqrt(i + j))) {
                result.push_back(make_pair(i, j));
            }
        }
    }

    return result;
}

#include <iostream>
#include <vector>

std::vector<std::string>> string2words(std::string sentence) {
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
    words.push_back(word);
    return words;
}

std::string solution(std::string sentence) {
    // sentence builder
    std::vector<std::string> words; // initialize an empty vector of strings
                                    // this definition implicitly zero-initializes the vector
    std::string word = "";          // initialize an empty string
    for (char c : sentence) {       // iterate over each character in the sentence
        if (c == ' ') {
            words.push_back(word);  // add the word to the vector if a space is encountered
            word = "";              // reset the word
        } else {
            word += c;             // otherwise append the character to the word to construct it
        }
    }
    words.push_back(word);  // add the last word

    std::string result;
    for (std::string word : words) {
        if (word.size() % 2 == 0) {  // confirms if the length of the word is even
            for (int i = 1; i < word.size(); i += 2) {  // loop over odd-indexed characters
                result += word[i];
            }
        }
    }
    return result;
}

#inclide <string>
#include <vector>
std::vector<std::string> string2words(std::string sentence) {
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
    words.push_back(word);
    return words;
}

std::string solution(const std::string& sentence) {
    // TODO: implement the solution here
    std::string result;
    std::vector<std::string> words = string2words(sentence);
    for (std::string word : words) {
        if (word.size() % 2 == 0) {
            for (int i = 1; i < word.size(); i += 2) {
                result += word[i];
            }
        }
    }
    /*
     * return a reversed version of the result
     */
    return std::string(result.rbegin(), result.rend());
}
#include <string>
#include <vector>
#include <array>
#include <cctype>

std::vector<std::string> string2words(const std::string& sentence) {
    std::vector<std::string> words;
    std::string word;
    for (char c : sentence) {
        if (c == ' ') {
            if (!word.empty()) {
                words.push_back(word);
                word.clear();
            }
        } else {
            word += c;
        }
    }
    if (!word.empty()) {
        words.push_back(word);
    }
    return words;
}

char modechar(const std::string& str) {
    std::array<int, 26> freq = {0};
    int max_freq = 0;
    char mode = '\0';

    for (char c : str) {
        if (std::isalpha(c)) {
            int index = std::tolower(c) - 'a';
            freq[index]++;
            
            if (freq[index] > max_freq || (freq[index] == max_freq && mode == '\0')) {
                max_freq = freq[index];
                mode = std::tolower(c);
            }
        }
    }

    return mode;
}

std::string solution(const std::string &sentence) {
    std::string result;
    auto words = string2words(sentence);
    
    for (const auto& word : words) {
        if (word.length() % 2 == 1) {  // Check if word length is odd
            char mode = modechar(word);
            if (mode != '\0') {
                result += mode;
            }
        }
    }
    
    return result;
}

#include <vector>
using namespace std;
vector<string> string2words(const string& sentence) {
    vector<string> words;
    string word;
    for (char c : sentence) {
        if (c == ' ') {
            if (!word.empty()) {
                words.push_back(word);
                word.clear();
            }
        } else {
            word += c;
        }
    }
    // handle the last word
    if (!word.empty())
        words.push_back(word);

    return words;
}

/*
 * Section: array traversal
 */
#include <iostream>
#include <climits> // For INT_MIN
#include <vector>

int solution(std::vector<int> arrayA, std::vector<int> arrayB, int sizeA, int sizeB) {
    int indexA = 0;
    int indexB = -1;
    bool in_arrayA = true;
    int max_value = INT_MIN;

    while (true) {
        if (in_arrayA) {
            indexB = arrayA[indexA];
            if (arrayB[indexB] > max_value) {
                max_value = arrayB[indexB];
            }
        } else {
            indexA = arrayB[indexB];
            if (indexA == 0) {
                return max_value;
            }
        }
        in_arrayA = !in_arrayA;
    }
}

int main() {
    std::vector<int> arrayA = {2, 4, 3, 1, 6};
    std::vector<int> arrayB = {4, 0, 3, 2, 0};
    int sizeA = arrayA.size();
    int sizeB = arrayB.size();

    std::cout << "Maximum value encountered in arrayB: " << solution(arrayA, arrayB, sizeA, sizeB) << std::endl;

    return 0;
}

/*
 * You're assisting in the creation of an algorithm for a novel game where a character hops between two arrays following certain rules. The game starts at the first index (1-based) of an array, arrayA.
 * The value at the character's current position in arrayA determines the index it jumps to on the second array, arrayB. Upon landing on arrayB, it does the same thing: the value at the current position specifies the index it jumps to in arrayA. This iteration continues until the character lands on an index in arrayA that it has already visited, at which point the game concludes.
 * Your task is to develop a C++ function simulating this gameplay. The function receives two equal-length arrays of integers, arrayA and arrayB, each containing n elements (1 ≤ n ≤ 100). It should return an array consisting of the 1-based indices on arrayB that the character visited before a position on arrayA was repeated.

Each element in the input arrays ranges from 1 to n, indicating the next 1-based index that the character will jump to in the other array. The function guarantees that each jump always results in a valid position within the same-length arrays, and a position in arrayA will inevitably be revisited.
*/
#include <vector>
#include <climits>


std::vector<int> solution(const std::vector<int>& arrayA, const std::vector<int>& arrayB) {
    std::vector<int> visited;
    std::vector<bool> visitedA(arrayA.size(), false);
    int indexA = 0;
    int indexB = -1;
    bool in_arrayA = true;
    int max_value = INT_MIN;

    while (true) {
        if (in_arrayA) {
            indexB = arrayA[indexA];
            if (visitedA[indexA]) {
                break;
            }
            visitedA[indexA] = true;
            visited.push_back(indexB);
        } else {
            indexA = arrayB[indexB];
            if (indexA == 0) {
                break;
            }
        }
        in_arrayA = !in_arrayA;
    }

    return visited;
}
#include <iostream>
using namespace std;

// Array of temperatures throughout the day
int temperatures[] = {16, 14, 20, 22, 19, 13};

int main() {
    // TODO: Loop through the temperatures to suggest clothing
    for(int i = 0; i < 6; i++) {
        int temp = temperatures[i];
        if (temp < 15) {
            cout << "Wear warm clothes." << endl;
            // TODO: If it's cold outside, we stop checking the temperatures. Add the needed line to interrupt the loop.
            if (temp < 15) {
                break;
            }
        } else if (temp >= 20) {
            // TODO: Print a suggestion to wear light clothes.
            // TODO: Add a line here that will skip the final cout statement when it's warm enough for light clothes.
            cout << "Wear light clothes." << endl;
            continue;
        }
        cout << "Consider a light jacket." << endl; // Suggestion for in-between temperatures
    }
    return 0;
}
