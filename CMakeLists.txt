# ModelLibrary/CMakeLists.txt
cmake_minimum_required( VERSION 2.8.11 )
project(Model_library)

set( CMAKE_INCLUDE_CURRENT_DIR ON )

file(MAKE_DIRECTORY ./build/lib)

# Make a library
add_library( /model3DLib 
./Src/Vector3D.cpp ./Inc/Vector3D.h
./Src/Material.cpp ./Inc/Material.h
./Src/Cell.cpp ./Inc/Cell.h
./Src/Matrix3x3.cpp ./Inc/Matrix3x3.h
./Src/Model.cpp ./Inc/Model.h)

# Make an executable
add_executable( test_program 
../Src/Vector3D.cpp ../Inc/Vector3D.h
../Src/Material.cpp ../Inc/Material.h
../Src/Cell.cpp ../Inc/Cell.h
../Src/Matrix3x3.cpp ../Inc/Matrix3x3.h
../Src/Model.cpp ../Inc/Model.h
../Test_programs/Model_test.cpp)
# The executable uses the library
# /ModelLibrary/CMakeLists.txt
