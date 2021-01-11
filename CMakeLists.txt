# ModelLibrary/CMakeLists.txt

#define minimum CMake version
cmake_minimum_required( VERSION 2.8.11 )
project(Model_library)

#include relevant CMakeLists files
include(Inc/CMakeLists.txt)
include(Src/CMakeLists.txt)
include(Test_programs/CMakeLists.txt)

#define minimum C++ version
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

#include everything from current directory
set( CMAKE_INCLUDE_CURRENT_DIR ON )

#create folders for the library and test program
file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/demo)

#set created folder for library as an output for library creation
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

# Make a library
add_library( /model3DLib 
${modelLib_includes}
${modelLib_sources})

# Make an executable for library testing
add_executable(model_test_program 
${test_sources})

#set created folder for executable as an output for executable creation
set_target_properties(model_test_program PROPERTIES
         RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/demo)

#link the created library to the created executable
target_link_libraries(model_test_program ${PROJECT_BINARY_DIR}/lib/model3Dlib.a)

