module;

// Include all the standard library headers you need
#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <memory>
#include <algorithm>
// Add more as needed...

export module std;

// Export the types and functions you want to use
export using std::istream;
export using std::ostream;
export using std::iostream;
export using std::cin;
export using std::cout;
export using std::cerr;
export using std::string;
export using std::vector;
export using std::list;
export using std::shared_ptr;
export using std::unique_ptr;
// Add more as needed...

// You can also export entire namespaces if you prefer
export namespace std {
    using namespace std::string_literals;
}

// If you want to export everything from std, you could do:
// export namespace std;
// However, this is generally not recommended as it can lead to name conflicts
