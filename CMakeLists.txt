# /CMakeLists.txt
cmake_minimum_required(VERSION 3.28)
project(cpp_sandbox)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(${CMAKE_SOURCE_DIR}/include)

add_subdirectory(lib)

add_subdirectory(src)

# Testing with Catch2
include(FetchContent)
FetchContent_Declare(
  Catch2
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  GIT_TAG        v3.7.1 # latest stable release
)
FetchContent_MakeAvailable(Catch2)
add_subdirectory(tests)
