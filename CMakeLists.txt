# ModelLibrary/CMakeLists.txt
cmake_minimum_required( VERSION 2.8.11 )
project(Model_library)

include(Inc/CMakeLists.txt)
include(Src/CMakeLists.txt)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set( CMAKE_INCLUDE_CURRENT_DIR ON )

file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/demo)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

# Make a library
add_library( /model3DLib 
${modelLib_includes}
${modelLib_sources})

#set_target_properties(Model_library PROPERTIES
       # LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

# Make an executable for Model code test
add_executable(model_test_program 
./Test_programs/demo.cpp)

set_target_properties(model_test_program PROPERTIES
         RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/demo)

target_link_libraries(model_test_program ${PROJECT_BINARY_DIR}/lib/model3Dlib.a)

