# CMake version requirement
cmake_minimum_required(VERSION 3.10)

# Project name and version
project(MultiExecutableProject VERSION 1.0)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 20) # or 14, 17, 20 based on your requirements
set(CMAKE_CXX_STANDARD_REQUIRED True)

# add_executable(inheritance src/inheritance.cpp)
# add_executable(casting src/casting.cpp)
# add_executable(classes src/classes.cpp)
# add_executable(smartpointers src/smartpointers.cpp)
# add_executable(exceptionhandling src/exceptionhandling.cpp)
# add_executable(lambdas src/lambdas.cpp)
# add_executable(initialization src/initialization.cpp)

# Specify the source files for each executable
file(GLOB SOURCES "src/*.cpp")  # Collect all .cpp files in the src directory
# Loop through each source file and create an executable
foreach(source_file ${SOURCES})
    # Get the filename without the extension
    get_filename_component(exec_name ${source_file} NAME_WE)

    # Add an executable for each source file
    add_executable(${exec_name} ${source_file})
endforeach()
