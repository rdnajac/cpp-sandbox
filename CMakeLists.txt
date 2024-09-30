# Root CMakeLists.txt
cmake_minimum_required(VERSION 3.28)
project(cpp_sandbox)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add include directory
include_directories(${CMAKE_SOURCE_DIR}/include)

# Add subdirectories
add_subdirectory(lib)
add_subdirectory(chrono)
