# ModelLibrary/CMakeLists.txt

#define minimum CMake version
cmake_minimum_required( VERSION 2.8.11 )

project(library_testing)

#include CTest to allow test creation
include(CTest)

#include relevant CMakeLists files
include(../Model_Library/CMakeLists.txt)

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

if( NOT BUILD_SHARED_LIBS )
add_definitions( -Dmodel3DLib_STATIC )
endif()

# It also contains an executable
add_executable(vector3DtestProg vector3Dtest.cpp)
add_executable(materialtestProg materialtest.cpp)
add_executable(celltestProg celltest.cpp)
add_executable(modeltestProg modeltest.cpp)

# The executable uses the library
target_link_libraries(vector3DtestProg model3DLib)
target_link_libraries(materialtestProg model3DLib)
target_link_libraries(celltestProg model3DLib)
target_link_libraries(modeltestProg model3DLib)

add_test(vector3Dtest vector3DtestProg)
add_test(materialtest materialtestProg)
add_test(celltest celltestProg)
add_test(modeltest modeltestProg)


