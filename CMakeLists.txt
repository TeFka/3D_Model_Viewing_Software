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
${QRC_Srcs} ${CMAKE_CURRENT_SOURCE_DIR}/Resources/GUI_Icons/exeIcon.rc)

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

set(CPACK_GENERATOR "NSIS")

#install 3D software target-------------------------
install(TARGETS VTKView
RUNTIME DESTINATION bin
COMPONENT application)
#-----------------------------------------------------
install (TARGETS model3DLib
LIBRARY DESTINATION lib
ARCHIVE DESTINATION lib/static
COMPONENT library)
#install VTK---------------------------------------
file( GLOB VTK_DLLS ${VTK_RUNTIME_LIBRARY_DIRS}/*.dll )
if( VTK_DLLS )
    foreach( Vtk_library ${VTK_DLLS} )
        # Add it to the list of 'desired' vtk-libraries for later installation
        list( APPEND Vtk_Install_Libraries ${Vtk_library} )
    endforeach( Vtk_library ${VTK_DLLS} )
    list( REMOVE_DUPLICATES Vtk_Install_Libraries )
    install( FILES ${Vtk_Install_Libraries} 
DESTINATION bin 
COMPONENT VTK  )
endif( VTK_DLLS )
#install Qt (doesnt work)-----------------------------------------------------------------------
# If Qt-4 was used, add the 'found' Qt-libraries to the Install-target.
find_package( Qt5_Widgets )
    foreach( Qt_library ${QT_LIBRARIES} )
        # With QT_USE_IMPORTED_TARGETS, we should extract the dll info 
        # from the target properties
        get_target_property( Qt_lib_name ${Qt_library} IMPORTED_LOCATION )
        get_target_property( Qt_lib_name_debug ${Qt_library} IMPORTED_LOCATION_DEBUG )
        get_target_property( Qt_lib_name_release ${Qt_library} IMPORTED_LOCATION_RELEASE )

        # Initially assume the release dlls should be installed, but 
        # fall back to debug if necessary
        if ( Qt_lib_name_release AND EXISTS ${Qt_lib_name_release} )
            set( Qt_library_location ${Qt_lib_name_release} )
        elseif ( Qt_lib_name_debug AND EXISTS ${Qt_lib_name_debug} AND ENVIRONMENT_DEBUG )
            set( Qt_library_location ${Qt_lib_name_debug} )
        elseif ( Qt_lib_name AND EXISTS ${Qt_lib_name} )
            set( Qt_library_location ${Qt_lib_name} )
        endif ( Qt_lib_name_release AND EXISTS ${Qt_lib_name_release} )

        # Extract the filename part, without the lib-prefix or the .a or ..lib suffix
        get_filename_component( Qt_library_name ${Qt_library_location} NAME_WE )
        string( REGEX REPLACE "^lib(.*)" "\\1" Qt_library_name ${Qt_library_name} )

        set( Qt_shared_library ${QT_BINARY_DIR}/${Qt_library_name}.dll )
          if ( EXISTS ${Qt_shared_library} )
            # Add it to the list of 'desired' qt-libraries for later installation
            list( APPEND Qt_Install_Libraries ${Qt_shared_library} )
        else ( EXISTS ${Qt_shared_library} )
            message( WARNING "    could not find ${Qt_shared_library}" )
        endif ( EXISTS ${Qt_shared_library} )
    endforeach( Qt_library ${QT_LIBRARIES} )
    # When building against a static Qt, the list of Qt_Install_Libraries can be empty
   # if ( Qt_Install_Libraries )
        list( REMOVE_DUPLICATES Qt_Install_Libraries )
        install( FILES ${Qt_Install_Libraries} 
                DESTINATION bin 
                COMPONENT Qt )
   # endif ( Qt_Install_Libraries )    
#----------------------------------------------------------------------------------
#set and define components
set(CPACK_RPM_COMPONENT_INSTALL ON)
set(CPACK_COMPONENTS_ALL application library VTK Qt)
#-------------------------------------------------------------------
#--------------adding description, glitches and doesnt work for unknown reason--------------
set(CPACK_COMPONENT_APPLICATION_DESCRIPTION 
"Installs the programme's executable (required)")
set(CPACK_COMPONENT_LIBRARY_DESCRIPTION 
"Installs the programmes .LIB file (required)")
set(CPACK_COMPONENT_VTK_DESCRIPTION 
"Installs all VTK dll's (required if VTK not already installed)")
set(CPACK_COMPONENT_Qt_DESCRIPTION 
"Installs all VTK dll's (required if Qt not already installed)")
#----------------------------------------------------------------
#--------------Connect executable and uninstaller to startmenu--------------------
set(CPACK_PACKAGE_EXECUTABLES "uninstall;uninstall")
set(CPACK_CREATE_DESKTOP_LINKS "uninstall")
set(CPACK_PACKAGE_EXECUTABLES "VTKView;VTKView")
set(CPACK_CREATE_DESKTOP_LINKS "VTKView")
#--------------------------------------------------------------------
#-------------changing display names if wanted----------------------
#set(CPACK_COMPONENT_APPLICATION_DISPLAY_NAME "")
#set(CPACK_COMPONENT_LIBRARY_DISPLAY_NAME "")
#set(CPACK_COMPONENT_HEADERS_DISPLAY_NAME "")




include(CPack)

