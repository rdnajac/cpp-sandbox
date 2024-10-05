# chrono/CMakeLists.txt
add_executable(loops loops.cpp)
target_link_libraries(loops PRIVATE timer rng)

add_executable(vectors vectors.cpp)
target_link_libraries(vectors PRIVATE timer rng)
