# lib/CMakeLists.txt

macro(add_single_library lib_name)
    add_library(${lib_name} STATIC ${lib_name}.cpp)
    target_include_directories(${lib_name} PUBLIC ${CMAKE_SOURCE_DIR}/include)
endmacro()

add_single_library(rng)
add_single_library(timer)

