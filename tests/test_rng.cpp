#define CATCH_CONFIG_MAIN
#include <catch2/catch_test_macros.hpp>
#include "rng.hpp"

TEST_CASE("RandomNumberGenerator Default Constructor") {
    RandomNumberGenerator rng;
    
    // Test if the random number is within the full range of int
    int randomNumber = rng.getRandomNumber();
    REQUIRE(randomNumber >= std::numeric_limits<int>::min());
    REQUIRE(randomNumber <= std::numeric_limits<int>::max());
}

TEST_CASE("RandomNumberGenerator Range Constructor") {
    int min = 10;
    int max = 50;
    RandomNumberGenerator rng(min, max);
    
    // Test if the random number is within the specified range
    for (int i = 0; i < 100; ++i) {
        int randomNumber = rng.getRandomNumber();
        REQUIRE(randomNumber >= min);
        REQUIRE(randomNumber <= max);
    }
}

TEST_CASE("RandomNumberGenerator Random Index") {
    RandomNumberGenerator rng;
    size_t max = 100;
    
    // Test if the random index is within the specified range
    for (int i = 0; i < 100; ++i) {
        size_t randomIndex = rng.getRandomIndex(max);
        REQUIRE(randomIndex >= 0);
        REQUIRE(randomIndex < max);
    }
}
