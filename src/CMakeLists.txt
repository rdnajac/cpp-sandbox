# src/CMakeLists.txt

macro(add_all_subdirectories)
    file(GLOB subdirs LIST_DIRECTORIES true *)
    foreach(subdir IN LISTS subdirs)
        if(EXISTS "${subdir}/CMakeLists.txt")
            add_subdirectory(${subdir})
        endif()
    endforeach()
endmacro()

add_all_subdirectories()

add_executable(${PROJECT_NAME} main.cpp)
add_executable(qsort qsort.cpp)
