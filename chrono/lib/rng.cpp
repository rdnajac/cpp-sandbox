#include "rng.hpp"

RandomNumberGenerator::RandomNumberGenerator() 
    : mt(std::random_device{}()),
      dist(std::numeric_limits<int>::min(), std::numeric_limits<int>::max()) {}

int RandomNumberGenerator::getRandomNumber() {
    return dist(mt);
}

size_t RandomNumberGenerator::getRandomIndex(size_t max) {
    return std::uniform_int_distribution<size_t>{0, max - 1}(mt);
}