#define CATCH_CONFIG_MAIN
#include <catch2/catch_test_macros.hpp>

int theAnswer() { return 6*9; } // function to be tested

TEST_CASE( "Life, the universe and everything", "[42][theAnswer]" ) {
REQUIRE(theAnswer() == 42);
}
