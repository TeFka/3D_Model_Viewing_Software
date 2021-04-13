#CMakeLists.txt

cmake_minimum_required(VERSION 2.8.0)
project(Vector3D)

include(CTest)

add_library( Vector3D ../Src/Vector3D.cpp )

if( NOT BUILD_SHARED_LIBS )
# if static libs are compiled we need
# to somehow communicate that to the
# source code. The definition will be
# used to determine how MATHSLIB_API
# is defined in adder.h
add_definitions( -Dmaths_STATIC )
endif()

# It also contains an executable
add_executable(Vector3Dtest Vector3Dtest.cpp)
# The executable uses the library
target_link_libraries(Vector3Dtest Vector3D)

add_test(Vector3Dtest Vector3Dtest)


