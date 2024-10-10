#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

// Function to add two large numbers represented as strings
std::string addLargeNumbers(const std::string& num1, const std::string& num2) {
    int i = num1.size() - 1;
    int j = num2.size() - 1;
    int carry = 0;
    std::vector<char> result;

    while (i >= 0 || j >= 0 || carry) {
        int n1 = (i >= 0) ? num1[i] - '0' : 0;
        int n2 = (j >= 0) ? num2[j] - '0' : 0;
        int current = n1 + n2 + carry;
        carry = current / 10;
        current = current % 10;
        result.push_back('0' + current);
        i--;
        j--;
    }

    std::reverse(result.begin(), result.end());
    return std::string(result.begin(), result.end());
}

// Function to subtract two large numbers represented as strings
std::string subtractLargeNumbers(const std::string& num1, const std::string& num2) {
    // Assume num1 >= num2 for simplicity
    int i = num1.size() - 1;
    int j = num2.size() - 1;
    int borrow = 0;
    std::vector<char> result;

    while (i >= 0 || j >= 0) {
        int n1 = (i >= 0) ? num1[i] - '0' : 0;
        int n2 = (j >= 0) ? num2[j] - '0' : 0;

        if (n1 < n2 + borrow) {
            n1 += 10;
            borrow = 1;
        } else {
            borrow = 0;
        }
        int current = n1 - n2 - borrow;
        result.push_back('0' + current);
        i--;
        j--;
    }

    // Remove leading zeros and reverse result
    while (result.size() > 1 && result.back() == '0') {
        result.pop_back();
    }

    std::reverse(result.begin(), result.end());
    return std::string(result.begin(), result.end());
}

// Function to multiply two large numbers represented as strings
std::string multiplyLargeNumbers(const std::string& num1, const std::string& num2) {
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

int main() {
    std::string num1 = "1454178195297";
    std::string num2 = "8458263917502";

    // Adding large numbers
    std::string sum = addLargeNumbers(num1, num2);
    std::cout << "Sum: " << sum << std::endl;

    // Subtracting large numbers
    std::string difference = subtractLargeNumbers(num2, num1); // num2 - num1
    std::cout << "Difference: " << difference << std::endl;

    // Multiplying large numbers
    std::string product = multiplyLargeNumbers(num1, num2);
    std::cout << "Product: " << product << std::endl;

    return 0;
}

