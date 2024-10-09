/**
 * @file myncat.cpp
 * @brief A simple utility to print the contents of a file with line numbers.
 * 
 * This program reads a text file and prints its contents to standard output,
 * prepending each line with its line number.
 * 
 * Usage: myncat <file-name>
 */

#include "utils.hpp"
#include <fstream>
#include <iomanip>
#include <iostream>
#include "timer.hpp"

using namespace std;

int main(int argc, char **argv) {
    if (argc != 2) {
        die("Usage: myncat <file-name>");
    }

    std::string filename = argv[1]; // File name to read
    std::ifstream file(filename); // Open file
    if (!file) {
        die("Error opening file: " + filename);
    }

    Timer timer; // Create a Timer instance
    timer.start(); // Start timing the file read

    std::string line;
    int lineno = 1;

    // Read each line and print it
    while (std::getline(file, line)) {
        std::cout << "[" << std::setw(4) << lineno++ << "] " << line << std::endl;
    }

    if (file.bad()) {
        die("Error reading file: " + filename);
    }

    file.close(); // Close the file

    timer.logTime("File read", lineno - 1); // Log the duration with the number of lines read
    long long duration = timer.getDuration(0); // Get the duration of the first logged time
    std::cerr << "Read " << (lineno - 1) << " lines in " << duration << " ms" << std::endl;

    return 0;
}
