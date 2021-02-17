# CMakeLists.txt--------------------------------------------------------------
cmake_minimum_required(VERSION 3.3 FATAL_ERROR)


list(APPEND software_sources
    ${CMAKE_CURRENT_LIST_DIR}/main.cpp 
    ${CMAKE_CURRENT_LIST_DIR}/mainwindow.cpp
	${CMAKE_CURRENT_LIST_DIR}/mainwindow.h
    ${CMAKE_CURRENT_LIST_DIR}/mainwindow.ui
)

set( UIS ${CMAKE_CURRENT_LIST_DIR}/mainwindow.ui )

set( ICONS ${CMAKE_CURRENT_LIST_DIR}/images/resource.qrc )

# /CMakeLists.txt-------------------------------------------------------------
