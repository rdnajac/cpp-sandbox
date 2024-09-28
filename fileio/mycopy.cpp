#include "utils.hpp"
#include <fstream>
#include <vector>

int main(int argc, char **argv) {
    if (argc != 3)
        die("Usage: mycopy <source-file> <destination-file>");

    std::string src_name = argv[1];
    std::string dest_name = argv[2];

    std::ifstream src(src_name, std::ios::binary);
    if (!src)
        die("Error opening source file: " + src_name);

    std::ofstream dest(dest_name, std::ios::binary);
    if (!dest)
        die("Error opening destination file: " + dest_name);

    std::vector<char> buffer(128);
    size_t total = 0;

    while (src) {
        src.read(buffer.data(), buffer.size());
        std::streamsize count = src.gcount();
        if (count > 0) {
            dest.write(buffer.data(), count);
            if (!dest) {
                src.close();
                die("Error writing to destination file: " + dest_name);
            }
            total += count;
        }
    }

    if (src.bad()) {
        src.close();
        dest.close();
        die("Error reading source file: " + src_name);
    }

    std::cerr << "Read and wrote " << total << " bytes" << std::endl;

    return 0;
}