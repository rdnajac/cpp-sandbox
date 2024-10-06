// Utility functions I don't want to write twice
#ifndef UTILS_HPP
#define UTILS_HPP


/* 
 * @brief Print a message to stderr and exit with status 1
 *
 * The syntax here ensures that the macro can be used as a statement
 * without needing a trailing semicolon. This is a common idiom in C.
 */
#define die(msg) \
    do { std::cerr << msg << std::endl; exit (1); } while (0)

#endif //UTILS_HPP
