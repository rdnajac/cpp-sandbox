#include <vector>
#include <iostream>
#include <iterator>            // For std::istream_iterator and std::ostream_iterator
#include <algorithm>           // For std::copy

int main() {
    std::vector<int> v;

    // Read integers from standard input until EOF
    std::copy(
        std::istream_iterator<int>(std::cin),  // Input iterator reading from std::cin
        std::istream_iterator<int>(),           // End of input iterator (default constructed)
        std::back_inserter(v)                   // Output iterator to insert into vector v
    );

    // Output the contents of the vector to standard output
    std::copy(
        v.begin(),                             // Beginning of the vector
        v.end(),                               // End of the vector
        std::ostream_iterator<int>(std::cout) // Output iterator writing to std::cout
    );

    return 0;
}
