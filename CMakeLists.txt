# ModelLibrary/CMakeLists.txt

#define minimum CMake version
cmake_minimum_required( VERSION 2.8.11 )
foreach(p
CMP0071 # 3.10: Let AUTOMOC and AUTOUIC process GENERATED files
)
if(POLICY ${p})
cmake_policy(SET ${p} NEW)
endif()
endforeach()
PROJECT( 3D_Modeling_Software )

set( CMAKE_AUTOMOC ON )
set( CMAKE_AUTOUIC ON )

#include relevant CMakeLists files
include(Inc/CMakeLists.txt)
include(Src/CMakeLists.txt)
include(GUI_source/CMakeLists.txt)
include(Test_programs/CMakeLists.txt)

set_property(SOURCE ${modelLib_includes} PROPERTY SKIP_AUTOMOC ON)
set_property(SOURCE ${modelLib_includes} PROPERTY SKIP_AUTOUIC ON)
set_property(SOURCE ${modelLib_sources} PROPERTY SKIP_AUTOMOC ON)
set_property(SOURCE ${modelLib_sources} PROPERTY SKIP_AUTOUIC ON)

#define minimum C++ version
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

#include everything from current directory
set( CMAKE_INCLUDE_CURRENT_DIR ON )

# This allows CMake to run one of Qt's build tools called moc
# if it is needed. moc.exe can be found in Qt's bin directory.
# We'll look at what moc does later.
set( CMAKE_AUTOMOC ON )
set( CMAKE_AUTOUIC ON )

find_package( Qt5Widgets )

qt5_wrap_ui( UI_Srcs ${UIS} )

# Also link to VTK
find_package( VTK REQUIRED )
include( ${VTK_USE_FILE} )

qt5_add_resources( QRC_Srcs ${ICONS} )

#create folders for the library and the program
file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/application)

#set created folder for library as an output for library creation
#set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

# Make a library
add_library( model3DLib
${modelLib_includes}
${modelLib_sources})

# Make an executable for library testing
add_executable(3D_software MACOSX_BUNDLE 
${software_sources}
${UI_Srcs}
${QRC_Srcs})

qt5_add_binary_resources(resources ${ICONS} OPTIONS -no-compress)
add_dependencies(3D_software resources)

#set created folder for executable as an output for executable creation
set_target_properties(3D_software PROPERTIES
         RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/application)

# Tell CMake that the executable depends on the Qt::Widget libraries.
target_link_libraries( 3D_software Qt5::Widgets )
# Tell CMake that the executable depends on the VTK libraries
target_link_libraries( 3D_software ${VTK_LIBRARIES})

#link the created library to the created executable
target_link_libraries(3D_software ${PROJECT_BINARY_DIR}/libmodel3Dlib.a)

