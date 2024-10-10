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