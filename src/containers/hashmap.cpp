#include <iostream>
#include <unordered_map>
#include <string>

int main() {
    // Creating an unordered_map to store HTTP status codes and their meanings
    std::unordered_map<int, std::string> http_status_codes = {
        {200, "OK"},
        {404, "Not Found"},
        {500, "Internal Server Error"},
        {301, "Moved Permanently"},
        {403, "Forbidden"}
    };

    // Using find() to access a specific HTTP status message
    int code_to_find = 200;
    auto it = http_status_codes.find(code_to_find);
    if (it != http_status_codes.end()) {
        std::cout << "HTTP Status " << code_to_find << ": " << it->second << std::endl; // Output: "OK"
    } else {
        std::cout << "HTTP Status code not found" << std::endl;
    }

    // Using find() to access a nonexistent HTTP status code
    int nonexistent_code = 999;
    auto it_nonexistent = http_status_codes.find(nonexistent_code);
    if (it_nonexistent != http_status_codes.end()) {
        std::cout << "HTTP Status " << nonexistent_code << ": " << it_nonexistent->second << std::endl;
    } else {
        std::cout << "HTTP Status code not found" << std::endl; // Output: "HTTP Status code not found"
    }

    // Looping over the unordered_map to display all HTTP status codes and their meanings
    std::cout << "\nAll HTTP Status Codes:\n";
    for (const auto& pair : http_status_codes) {
        std::cout << "HTTP Status " << pair.first << ": " << pair.second << std::endl;
    }

    // Additional member functions and operations
    // Checking the size of the unordered_map
    std::cout << "\nTotal number of HTTP status codes: " << http_status_codes.size() << std::endl;

    // Checking if a particular key exists
    int check_code = 403;
    if (http_status_codes.count(check_code)) {
        std::cout << "HTTP Status " << check_code << " exists." << std::endl;
    } else {
        std::cout << "HTTP Status " << check_code << " does not exist." << std::endl;
    }

    // Inserting a new HTTP status code
    http_status_codes[418] = "I'm a teapot"; // Adding an HTTP status code for fun
    std::cout << "Added HTTP Status 418: " << http_status_codes[418] << std::endl;

    // Erasing an HTTP status code
    http_status_codes.erase(404);
    std::cout << "Erased HTTP Status 404." << std::endl;

    return 0;
}

