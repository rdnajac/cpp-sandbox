# tests/CMakeLists.txt

# Find all test files in the current directory
file(GLOB TEST_SOURCES "test_*.cpp")

# Create and link each test executable
foreach(TEST_SOURCE ${TEST_SOURCES})
    get_filename_component(TEST_NAME ${TEST_SOURCE} NAME_WE)
    add_executable(${TEST_NAME} ${TEST_SOURCE})
    target_link_libraries(${TEST_NAME} PRIVATE Catch2::Catch2WithMain)

    # Link against the corresponding library based on the test name
    if(${TEST_NAME} STREQUAL "test_rng")
        target_link_libraries(${TEST_NAME} PRIVATE rng)
    elseif(${TEST_NAME} STREQUAL "test_timer")
        target_link_libraries(${TEST_NAME} PRIVATE timer)
    endif()
endforeach()

# Optional: Add a custom target to run all tests
add_custom_target(run_all_tests
    COMMAND ${CMAKE_CTEST_COMMAND} --output-on-failure
    DEPENDS ${TEST_SOURCES}
)