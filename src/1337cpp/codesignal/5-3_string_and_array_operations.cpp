#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include <utility>
#include <cmath>

std::pair<std::string, std::vector<int>> solution(std::string inputString, std::vector<int> numbers) {
    std::string result = "";
    int sum_so_far = 0;
    size_t i = 0;
    while (i < inputString.size() && sum_so_far <= 20) {
        result += (inputString[i] == 'z' ? 'a' : inputString[i] + 1);
        int half_number = static_cast<int>(std::round(numbers[i] / 2.0));
        sum_so_far += half_number;
        i++;
    }
    std::reverse(result.begin(), result.end());
    return {result, std::vector<int>(numbers.begin() + i, numbers.end())};
}

int main() {
    std::pair<std::string, std::vector<int>> result = solution("books", {10, 20, 30, 50, 100});
    std::cout << result.first << std::endl;
    std::vector<int> numbers = result.second;
    for(int value : numbers) {
        std::cout << value << " ";
    }
    return 0;
}