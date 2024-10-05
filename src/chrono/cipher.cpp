#include <iostream>
#include <string>
// Simple text encryption using Caesar Cipher technique
// The Caesar Cipher for `shift = 3` cyclically shifts every letter of the word by 3 positions:
// a -> d, b -> e, c -> f, ..., x -> a, y -> b, z -> c

// Implement the encryption logic by shifting each alphabet character

std::string encrypt_text(const std::string &text) {
    std::string encrypted;
    for (char c : text) {
        if (isalpha(c)) {  // check if the character is an alphabet
            int shift = 3;
            // TODO: Use correct calculations to shift the character within the alphabet
            
            // Hint: 'A' = 65, 'a' = 97
            // Hint 2: You can use the modulo (%) operator to wrap around the alphabet
            encrypted += (c + shift - (isupper(c) ? 'A' : 'a')) % 26 + (isupper(c) ? 'A' : 'a');
        } else {
            encrypted += c;  // keep non-alphabet characters unchanged
        }
    }
    return encrypted;
}

// Example text to encrypt
int main() {
    std::string original_text = "Hello, C++!";
    // The encrypted_text function call and cout statement should remain the same as the solution
    std::string encrypted_text = encrypt_text(original_text);
    std::cout << encrypted_text << std::endl;  // Correct output after TODO should be 'Khoor, F++!'
    return 0;
}
