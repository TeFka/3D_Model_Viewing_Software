# ModelLibrary/CMakeLists.txt
cmake_minimum_required( VERSION 2.8 )
project( Model )
# This project contains a library
add_library( modelLib 
./Src/Vector3D.cpp ./Inc/Vector3D.h
./Src/Material.cpp ./Inc/Material.h
./Src/Cell.cpp ./Inc/Cell.h
./Src/Matrix.cpp ./Inc/Matrix.h
./Src/Model.cpp ./Inc/Model.h)
#add_library( maths STATIC adder.cpp )
#add_library( maths SHARED adder.cpp )
#if( NOT BUILD_SHARED_LIBS )

#add_definitions( -Dmaths_STATIC )

#endif()
# It also contains an executable
#add_executable( calc_prog calc_cmake_prog.cpp )
# The executable uses the library
# /ModelLibrary/CMakeLists.txt
