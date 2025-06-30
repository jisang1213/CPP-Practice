# CMake version requirement
cmake_minimum_required(VERSION 3.14)

# Project name and version
project(MultiExecutableProject VERSION 1.0)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 20) # or 14, 17, 20 based on your requirements
set(CMAKE_CXX_STANDARD_REQUIRED True)

# add_executable(stl_algorithms src/stl_algorithms.cpp)
# add_executable(stl_iterators src/stl_iterators.cpp)
# add_executable(stl_containers src/stl_containers.cpp)
# add_executable(templates src/templates.cpp)
# add_executable(func src/functions.cpp)
# add_executable(memory src/memory.cpp)
# add_executable(vector src/implementation/better_vector.cpp)
# add_executable(ranges src/ranges.cpp)
# add_executable(spaceship src/spaceship.cpp)
# add_executable(tmp src/tmp.cpp)
# add_executable(virtual src/implementation/virtual.cpp)
# add_executable(fold src/implementation/fold.cpp)
# add_executable(string src/implementation/string.cpp)
# add_executable(threads src/threads.cpp)
add_executable(crtp src/crtp.cpp)


# # Specify the source files for each executable
# file(GLOB_RECURSE SOURCES "src/**/*.cpp") # Collect all .cpp files in the src directory
# # Loop through each source file and create an executable
# foreach(source_file ${SOURCES})
#     # Get the filename without the extension
#     get_filename_component(exec_name ${source_file} NAME_WE)

#     # Add an executable for each source file
#     add_executable(${exec_name} ${source_file})
# endforeach()