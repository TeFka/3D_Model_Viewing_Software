# CMakeLists.txt--------------------------------------------------------------
cmake_minimum_required(VERSION 3.3 FATAL_ERROR)


list(APPEND software_sources
    ${CMAKE_CURRENT_LIST_DIR}/main.cpp 
    ${CMAKE_CURRENT_LIST_DIR}/mainwindow.cpp
    ${CMAKE_CURRENT_LIST_DIR}/mainwindow.h
    ${CMAKE_CURRENT_LIST_DIR}/mainwindow.ui
    ${CMAKE_CURRENT_LIST_DIR}/apphelp.cpp
    ${CMAKE_CURRENT_LIST_DIR}/apphelp.h
    ${CMAKE_CURRENT_LIST_DIR}/apphelp.ui
    ${CMAKE_CURRENT_LIST_DIR}/newshapechoice.cpp
    ${CMAKE_CURRENT_LIST_DIR}/newshapechoice.h
    ${CMAKE_CURRENT_LIST_DIR}/newshapechoice.ui
    ${CMAKE_CURRENT_LIST_DIR}/Src/Pipeline.cpp
    ${CMAKE_CURRENT_LIST_DIR}/Inc/Pipeline.h
    ${CMAKE_CURRENT_LIST_DIR}/Src/VTKObject.cpp
    ${CMAKE_CURRENT_LIST_DIR}/Inc/VTKObject.h
    ${CMAKE_CURRENT_LIST_DIR}/Src/PipelineHandler.cpp
    ${CMAKE_CURRENT_LIST_DIR}/Inc/PipelinHandler.h
)


set( UIS ${CMAKE_CURRENT_LIST_DIR}/mainwindow.ui )

set( ICONS ${CMAKE_CURRENT_LIST_DIR}/images/resource.qrc )

# /CMakeLists.txt-------------------------------------------------------------
