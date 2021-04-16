#CMakeLists.txt

# It also contains an executable
add_executable(vector3DtestProg test_sources/vector3Dtest.cpp)

# The executable uses the library
target_link_libraries(vector3DtestProg model3Dlib)

set_target_properties(vector3DtestProg PROPERTIES
         RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/test_programs)

add_test(vector3Dtest vector3DtestProg)


