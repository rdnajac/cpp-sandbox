#ifndef RNG_HPP
#define RNG_HPP

#include <random>
#include <limits>

/**
 * @class RandomNumberGenerator
 * @brief A class for generating random numbers.
 *
 * This class provides functionality to generate random integers 
 * within a specified range or across the full range of integers.
 */
class RandomNumberGenerator {
private:
    std::mt19937 mt; ///< Mersenne Twister pseudo-random number generator
    std::uniform_int_distribution<int> dist; ///< Distribution for generating random integers

public:
    /**
     * @brief Default constructor.
     *
     * Initializes the random number generator to produce values
     * across the full range of integers.
     */
    RandomNumberGenerator();
    
    /**
     * @brief Constructor with a specified range.
     *
     * Initializes the random number generator to produce values
     * within the specified range [min, max].
     *
     * @param min The minimum value (inclusive).
     * @param max The maximum value (inclusive).
     */
    RandomNumberGenerator(int min, int max);
    
    /**
     * @brief Generates a random integer.
     *
     * @return A random integer within the configured range.
     */
    int getRandomNumber();

    /**
     * @brief Generates a random index.
     *
     * @param max The upper limit (exclusive) for the index.
     * @return A random index between 0 and max - 1.
     */
    size_t getRandomIndex(size_t max);
};

#endif // RNG_HPP
