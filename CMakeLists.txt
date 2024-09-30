# /CMakeLists.txt
cmake_minimum_required(VERSION 3.28)
project(cpp_sandbox)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(${CMAKE_SOURCE_DIR}/include)

add_subdirectory(lib)
add_subdirectory(chrono)
