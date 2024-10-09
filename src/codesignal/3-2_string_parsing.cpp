#include <vector>
#include <iostream>

int ParseAndMultiplyNumbers (std::string inputString) {
    std::string num;
    std::vector<int> numbers;
    for (char ch: inputString) {
        if(isdigit(ch)) {
            num += ch;
        } else if (!num.empty()) {
            numbers.push_back(stoi(num));
            num = "";
        }
    }
    if (!num.empty()) {
        numbers.push_back(stoi(num));
    }
    
    int result = 1;
    for(int number: numbers) {
        result *= number;
    }
    return result;
}

int main() {
    // Call the function
    std::cout << ParseAndMultiplyNumbers("I have 2 apples and 5 oranges") << std::endl;
    return 0;
}