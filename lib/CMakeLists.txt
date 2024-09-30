# lib/CMakeLists.txt
add_library(timer STATIC
        timer.cpp
        ${CMAKE_SOURCE_DIR}/include/timer.hpp
)

add_library(rng STATIC
        rng.cpp
        ${CMAKE_SOURCE_DIR}/include/rng.hpp
)

target_include_directories(timer PUBLIC ${CMAKE_SOURCE_DIR}/include)
target_include_directories(rng PUBLIC ${CMAKE_SOURCE_DIR}/include)
