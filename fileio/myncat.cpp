#include "utils.hpp"
#include <fstream>
#include <iomanip>

int main(int argc, char **argv) {
    if (argc != 2)
        die("Usage: myncat <file-name>");

    std::string filename = argv[1];
    std::ifstream file(filename);
    if (!file)
        die("Error opening file: " + filename);

    std::string line;
    int lineno = 1;

    while (std::getline(file, line)) {
        std::cout << "[" << std::setw(4) << lineno++ << "]" << line << std::endl;
    }

    if (file.bad())
        die("Error reading file: " + filename);

    return 0;
}