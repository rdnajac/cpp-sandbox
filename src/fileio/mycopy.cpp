/**
 * @file mycopy.cpp
 * @brief A simple file copy utility that copies data from a source file to a destination file.
 *
 * This program reads a binary source file and writes its contents to a destination file,
 * reporting the number of bytes copied and the time taken for the operation.
 *
 * Usage: mycopy <source-file> <destination-file>
 */

#include "timer.hpp"
#include "utils.hpp"
#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

int main(int argc, char **argv) {
    if (argc != 3) {
        die("Usage: mycopy <source-file> <destination-file>");
    }

    std::string src_name = argv[1];  // Source file name
    std::string dest_name = argv[2]; // Destination file name

    std::ifstream src(src_name, std::ios::binary); // Open source file in binary mode
    if (!src) {
        die("Error opening source file: " + src_name);
    }

    std::ofstream dest(dest_name, std::ios::binary); // Open destination file in binary mode
    if (!dest) {
        die("Error opening destination file: " + dest_name);
    }

    Timer timer;   // Create a Timer instance
    timer.start(); // Start timing the copy operation

    std::vector<char> buffer(128); // Buffer for reading data
    size_t total = 0;              // Total bytes copied

    // Read from source and write to destination
    while (src) {
        src.read(buffer.data(), buffer.size()); // Read data into buffer
        std::streamsize count = src.gcount();   // Get number of bytes read
        if (count > 0) {
            dest.write(buffer.data(), count); // Write data to destination
            if (!dest) {
                src.close();
                die("Error writing to destination file: " + dest_name);
            }
            total += count; // Accumulate total bytes
        }
    }

    if (src.bad()) {
        src.close();
        dest.close();
        die("Error reading source file: " + src_name);
    }

    dest.close(); // Close destination file
    src.close();  // Close source file

    timer.logTime("File copy", total);         // Log the duration with a label
    long long duration = timer.getDuration(0); // Get the duration of the first logged time
    std::cerr << "Read and wrote " << total << " bytes in " << duration << " ms" << std::endl;

    return 0;
}
