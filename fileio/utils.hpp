#ifndef UTILS_HPP
#define UTILS_HPP

#include <iostream>
#include <string>

#define die(msg)                                                                                   \
    do {                                                                                           \
        std::cerr << msg << std::endl;                                                             \
        return 1;                                                                                  \
    } while (0)

#endif // UTILS_HPP