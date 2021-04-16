# ModelLibrary/CMakeLists.txt

#define minimum CMake version
cmake_minimum_required( VERSION 2.8.11 )

project(library_testing)

#include CTest to allow test creation
include(CTest)

#include relevant CMakeLists files
include(../Inc/CMakeLists.txt)
include(../Src/CMakeLists.txt)

#define minimum C++ version
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

#include everything from current directory
set( CMAKE_INCLUDE_CURRENT_DIR ON )

# Make a library
add_library( model3DLib
${modelLib_includes}
${modelLib_sources})

LINK_DIRECTORIES(${CMAKE_BINARY_DIR})

# It also contains an executable
add_executable(vector3DtestProg vector3Dtest.cpp)

# The executable uses the library
target_link_libraries(vector3DtestProg model3Dlib)

add_test(vector3Dtest vector3DtestProg)


