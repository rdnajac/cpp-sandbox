#define CATCH_CONFIG_MAIN
#include <catch2/catch_test_macros.hpp>
#include <iostream>
#include <thread>
#include "timer.hpp"

TEST_CASE("Timer functionality", "[timer]") {
    Timer timer;
    
    timer.logTime("Initial Log"); // Log the initial time

    // Simulate some work
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    timer.logTime("After 100ms sleep");

    // Simulate more work
    std::this_thread::sleep_for(std::chrono::milliseconds(200));
    timer.logTime("After 200ms sleep");

    // Check the durations
    REQUIRE(timer.getDuration(0) >= 0);
    REQUIRE(timer.getDuration(1) >= 100); // Should be at least 100ms
    REQUIRE(timer.getDuration(2) >= 200); // Should be at least 200ms
}

TEST_CASE("Timer print functions", "[timer]") {
    Timer timer;

    // Redirecting output to a string stream to test printLogs and printResults
    std::ostringstream output;
    std::streambuf *originalCoutBuffer = std::cout.rdbuf(output.rdbuf());

    timer.logTime("Test Log");
    timer.printLogs();

    std::cout.rdbuf(originalCoutBuffer); // Restore original buffer

    std::string logs = output.str();
    REQUIRE(logs.find("Description") != std::string::npos);
    REQUIRE(logs.find("Duration (ms)") != std::string::npos);
    REQUIRE(logs.find("Test Log") != std::string::npos);
}
