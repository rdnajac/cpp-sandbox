## Advanced Programming

Exercises and examples from the Advanced Programming course at Columbia
University. Originally written in C, rewritten in C++.

## References

- [Jae's class](https://www.cs.columbia.edu/~jae/3157/)
- [cppreference.com](https://en.cppreference.com/w/)
- [GeeksforGeeks](https://www.geeksforgeeks.org/)
- [Bitmask in C++](https://www.geeksforgeeks.org/bitmasking-in-cpp/)

## Quicksort

> The `qsort()` function is a modified partition-exchange sort, or quicksort.

```c
#include <stdlib.h>

void
qsort(void *base, size_t nel, size_t width,
    int (*compar)(const void *, const void *));
```

### `compar` function

The `compar` function is a user-supplied function that returns an integer less than, equal to, or greater than zero if the first argument is considered to be respectively less than, equal to, or greater than the second.

```c
int compar(const void *a, const void *b)
{
    return *(int *)a - *(int *)b;
}
```

Here, the `compar` function compares dereferenced pointers-to-integers
and returns the difference between the two values. If the difference is
negative, the first argument is considered less than the second. If the
difference is zero, the two arguments are considered equal.

### Time complexity

The time complexity of quicksort is O(n log n) on average, but O(n^2) in the
worst case.

The space complexity is O(log n) on average, but O(n) in the worst
case.

### Sorting in C++

The C++ standard library provides a `sort()` function that is implemented
using a hybrid sorting algorithm, which often includes quicksort as one of its components.

## Splitting strings

### `std::istringstream`

Use `istringstream` to split a whitespace-separated string into tokens.

```cpp
string s = "Hello, world!";
istringstream iss(s);
string token;
while (iss >> token) {
    cout << token << endl;
}
```

### `std::getline()`

Use `getline()` to split a string by a delimiter.

```cpp
string time = "12:34:56";
int seconds = 10;
stringstream ss(time);
string item;
vector<int> time_parts;

while (getline(ss, item, ':')) {
    time_parts.push_back(stoi(item));
}
```

## More string manipulation

Use an output string stream to concatenate strings.

```cpp
ostringstream oss;
os << setfill('0') << setw(2) << hours << ":" << setw(2) <<
minutes << ":" << setw(2) << seconds;
string result = os.str();
```

> [!NOTE]
> The `setfill()` and `setw()` manipulators from the `<iomanip>`
> header are used to set the fill character and the width of the output field.

## Trimming whitespace

Use the `std::string::find_first_not_of()` and `std::string::find_last_not_of()` functions to trim leading and trailing whitespace.

```cpp
// Trim any leading or trailing spaces
t1.erase(0, t1.find_first_not_of(' '));
t1.erase(t1.find_last_not_of(' ') + 1);
```

## Find and Replace

```cpp

std::string replace_substring(const std::string& text, const std::string& old, const std::string& newSubstr) {
    string result = text;
    size_t pos = 0;

    while ((pos = result.find(old, pos)) != std::string::npos) {
        result.replace(pos, old.length(), newSubstr);
        pos += newSubstr.length(); // Move past the new substring
    }

    return result;
}
```

## Reverse a string

```cpp
void reverse_string(string& s) {
    int n = s.size();
    for (int i = 0; i < n / 2; i++) {
        swap(s[i], s[n - i - 1]);
    }
}
```

Another example

```cpp
std::vector<std::string> solution(const std::vector<std::string>& sentences, const std::vector<std::string>& words) {
    vector<string> result = sentences;

    for (size_t i = 0; i < sentences.size(); ++i) {
        string& sentence = result[i];
        const string& word = words[i];

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
```

Another example

```cpp
#include <vector>
#include <string>
#include <algorithm> // for std::reverse
#include <cctype>    // for std::isupper and std::tolower
using namespace std;

std::vector<std::string> solution(const std::vector<std::string>& sentences, const std::vector<std::string>& words) {
    vector<string> result = sentences;

    for (size_t i = 0; i < sentences.size(); ++i) {
        string& sentence = result[i];
        const string& word = words[i];

        // Reverse the word
        string reversed_word = word;
        reverse(reversed_word.begin(), reversed_word.end());

        // Create a capitalized version of the word
        string capitalized_word = word;
        capitalized_word[0] = toupper(capitalized_word[0]);

        size_t pos = 0;
        while ((pos = sentence.find(word, pos)) != std::string::npos) {
            // Reset the first letter of the reversed word for each occurrence
            reversed_word[0] = std::isupper(sentence[pos]) ? std::toupper(reversed_word[0]) : std::tolower(reversed_word[0]);

            // Replace the word with its reversed version
            sentence.replace(pos, word.length(), reversed_word);
            pos += reversed_word.length(); // Move past the new substring
        }

        pos = 0;
        while ((pos = sentence.find(capitalized_word, pos)) != std::string::npos) {
            // Reset the first letter of the reversed word for each occurrence
            reversed_word[0] = std::isupper(sentence[pos]) ? std::toupper(reversed_word[0]) : std::tolower(reversed_word[0]);

            // Replace the word with its reversed version
            sentence.replace(pos, capitalized_word.length(), reversed_word);
            pos += reversed_word.length(); // Move past the new substring
        }
    }

    return result;
}
```

## Adding Large Numbers

```cpp
#include <algorithm>
#include <iostream>
#include <vector>

std::string addLargeNumbers(std::string num1, std::string num2) {
    int i = num1.size() - 1;
    int j = num2.size() - 1;
    int carry = 0;
    std::vector<char> result;

    while(i >= 0 || j >= 0 || carry) {
        int n1 = (i >= 0) ? num1[i] - '0' : 0;
        int n2 = (j >= 0) ? num2[j] - '0' : 0;
        int current = n1 + n2 + carry;
        carry = current / 10;
        current = current % 10;
        result.push_back('0' + current);
        i--;
        j--;
    }

    std::reverse(result.begin(),result.end());
    return std::string(result.begin(), result.end());
}

int main() {
    std::cout << addLargeNumbers("1454178195297", "8458263917502");
    return 0;
}
```

```cpp
// reverse a string and remove newly-leading zeroes
str = "123000";
reverse(str.begin(), str.end());
str.erase(0, str.find_first_not_of('0'));
// but dint let it
```

```cpp
#include <string>
#include <vector>
#include <iostream>
using namespace std;

std::string solution(const std::string &num1, const std::string &num2) {
std::vector<int> product(num1.size() + num2.size(), 0);

for (int i = num1.size() - 1; i >= 0; --i) {
    for (int j = num2.size() - 1; j >= 0; --j) {
        int n1 = num1[i] - '0';
        int n2 = num2[j] - '0';
        int sum = n1 * n2 + product[i + j + 1];

        product[i + j + 1] = sum % 10;
        product[i + j] += sum / 10;
    }
}
std::string result;
bool leadingZero = true;
for (int num : product) {
    if (num != 0 || !leadingZero) {
        result.push_back(num + '0');
        leadingZero = false;
    }
}

// If the result is still empty, it means the product is zero
if (result.empty()) {
    return "0";
}

    return result;
}
```

## Check if a key is in an `unordered_map`

```cpp
// Using find() to access a book's title
auto it = library_catalog.find("book1");
if (it != library_catalog.end())
    std::cout << it->second << std::endl; // Output: "A Tale of Two Cities"
else
    std::cout << "Key not found" << std::endl;

// Using find() to access a nonexistent key
auto it_nonexistent = library_catalog.find("book100");
if (it_nonexistent != library_catalog.end())
    std::cout << it_nonexistent->second << std::endl;
else
    std::cout << "Key not found" << std::endl; // Output: "Key not found"
```

## Lambda Functions

A lambda function is an anonymous function that can capture variables from its
surrounding scope. It is defined using the following syntax:

```cpp
[](const auto& a, const auto& b) {
    return a.second < b.second;
}
```

Here, the lambda function takes two arguments `a` and `b` and returns `true` if
the `second` member of `a` is less than the `second` member of `b`.
