# CMakeLists.txt--------------------------------------------------------------
cmake_minimum_required(VERSION 3.3 FATAL_ERROR)


list(APPEND software_sources
    ${CMAKE_CURRENT_LIST_DIR}/main.cpp 
    ${CMAKE_CURRENT_LIST_DIR}/UI/mainwindow.cpp
    ${CMAKE_CURRENT_LIST_DIR}/UI/mainwindow.h
    ${CMAKE_CURRENT_LIST_DIR}/UI/mainwindow.ui
    ${CMAKE_CURRENT_LIST_DIR}/UI/apphelp.cpp
    ${CMAKE_CURRENT_LIST_DIR}/UI/apphelp.h
    ${CMAKE_CURRENT_LIST_DIR}/UI/apphelp.ui
    ${CMAKE_CURRENT_LIST_DIR}/UI/newshapechoice.cpp
    ${CMAKE_CURRENT_LIST_DIR}/UI/newshapechoice.h
    ${CMAKE_CURRENT_LIST_DIR}/UI/newshapechoice.ui
    ${CMAKE_CURRENT_LIST_DIR}/Src/Pipeline.cpp
    ${CMAKE_CURRENT_LIST_DIR}/Inc/Pipeline.h
    ${CMAKE_CURRENT_LIST_DIR}/Src/DataPipeline.cpp
    ${CMAKE_CURRENT_LIST_DIR}/Inc/DataPipeline.h
    ${CMAKE_CURRENT_LIST_DIR}/Src/PolyPipeline.cpp
    ${CMAKE_CURRENT_LIST_DIR}/Inc/PolyPipeline.h
    ${CMAKE_CURRENT_LIST_DIR}/Src/VTKObjectHandler.cpp
    ${CMAKE_CURRENT_LIST_DIR}/Inc/VTKObjectHandler.h
    ${CMAKE_CURRENT_LIST_DIR}/Src/ViewerHandler.cpp
    ${CMAKE_CURRENT_LIST_DIR}/Inc/ViewerHandler.h
)


set( UIS ${CMAKE_CURRENT_LIST_DIR}/UI/mainwindow.ui )

# /CMakeLists.txt-------------------------------------------------------------
