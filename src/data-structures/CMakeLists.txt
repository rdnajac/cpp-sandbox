# data-structures/CMakeLists.txt
add_executable(myvector myvector.cpp)
target_link_libraries(myvector PRIVATE timer rng)

add_executable(mybst mybst.cpp)
target_link_libraries(mybst PRIVATE timer rng)
