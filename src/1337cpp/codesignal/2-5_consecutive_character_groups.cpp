#include <iostream>
#include <vector>
#include <cctype>

// Function to find consecutive character groups in a string
std::vector<std::pair<char, int>> solution(std::string s) {
    std::vector<std::pair<char, int>> groups;  // Vector to store the groups of characters
    char current_group_char = '\0';            // Variable to hold the current character group
    int current_group_length = 0;              // Variable to hold the length of the current character group
    
    for(char &c: s){
        if(isalnum(c)){                         // Check if the character is alphanumeric
            if(c == current_group_char){        // If the character is part of the current group
                current_group_length += 1;      // Increment the length of the current group
            } else {                            // If the character starts a new group
                if(current_group_char != '\0'){ // Push the previous group to groups if it exists
                    groups.push_back(std::make_pair(current_group_char, current_group_length));
                }
                current_group_char = c;         // Update the current character to the new group
                current_group_length = 1;       // Reset the length for the new group
            }
        }
    }
    if(current_group_char != '\0'){             // Add the last group if it exists
        groups.push_back(std::make_pair(current_group_char, current_group_length));
    }

    return groups;                              // Return the vector of groups
}