#include <iostream>
#include <cctype>
#include <string>

// TODO: Define a function to encrypt the text using a shift cipher
// The function should take two parameters: a string reference to the text and the integer shift value

void encrypt(std::string &text, int shift) {
    // Loop through each character in the string
    for (char &c : text) {
        // If the character is alphabetic, shift it by the given value
        if (std::isalpha(c)) {
            // Determine the range of the character
            char start = std::isupper(c) ? 'A' : 'a';
            // Shift the character
            c = start + (c - start + shift) % 26;
        }
    }
}

// TODO: Implement a loop that goes through each character in the string



    // TODO: If the character is alphabetic, shift it by the given value
    // Make sure to maintain the case (upper or lower) of the original letter

    // TODO: If the character is not alphabetic, add it as is to the encrypted string

// TODO: After defining the function, call it in the main function with a sample string and a shift value
// Yes, you'll need to write your main function to test your encryption function.


int main() {
    std::string text = "Hello, World!";
    int shift = 3;

    encrypt(text, shift);

    std::cout << "Encrypted text: " << text << std::endl;

    return 0;
}
