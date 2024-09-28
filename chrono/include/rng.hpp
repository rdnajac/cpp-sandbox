#ifndef RNG_HPP
#define RNG_HPP

#include <random>
#include <limits>

class RandomNumberGenerator {
private:
    std::mt19937 mt;
    std::uniform_int_distribution<int> dist;

public:
    RandomNumberGenerator();
    int getRandomNumber();
    size_t getRandomIndex(size_t max);
};

#endif // RNG_HPP