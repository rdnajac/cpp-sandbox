# src/memory/CMakeLists.txt
file(GLOB source_files *.cpp)
foreach(source_file IN LISTS source_files)
    get_filename_component(target_name ${source_file} NAME_WE)
    add_executable(${target_name} ${source_file})
endforeach()

