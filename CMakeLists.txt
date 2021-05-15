# ModelLibrary/CMakeLists.txt

#define minimum CMake version
cmake_minimum_required( VERSION 2.8.11 )

# Apply AUTOMOC and AUTOUIC policies
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

#include CTest to allow test creation
include(CTest)

#include relevant CMakeLists files
include(Model_Library/CMakeLists.txt)
include(Software_GUI/CMakeLists.txt)

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

set( ICONS ${CMAKE_CURRENT_LIST_DIR}/Resources/GUI_Icons/resource.qrc )

qt5_add_resources( QRC_Srcs ${ICONS} )

# Make a library
add_library( model3DLib
${modelLib_includes}
${modelLib_sources})

if( NOT BUILD_SHARED_LIBS )
add_definitions( -Dmodel3DLib_STATIC )
endif()

LINK_DIRECTORIES(${CMAKE_BINARY_DIR})

# Make an executable
add_executable(VTKView MACOSX_BUNDLE 
${software_sources}
${UI_Srcs}
${QRC_Srcs})

qt5_add_binary_resources(resources ${ICONS} OPTIONS -no-compress)
add_dependencies(VTKView resources)

#set created folder for executable as an output for executable creation
set_target_properties(VTKView PROPERTIES
         RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/application)

#link the created library to the created executable
target_link_libraries(VTKView model3DLib)

# Tell CMake that the executable depends on the Qt::Widget libraries.
target_link_libraries( VTKView Qt5::Widgets )

# Tell CMake that the executable depends on the VTK libraries
target_link_libraries( VTKView ${VTK_LIBRARIES})




