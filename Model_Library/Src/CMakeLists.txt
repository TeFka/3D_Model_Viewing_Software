
#create a list of all source files for the library
list(APPEND modelLib_sources
    ${CMAKE_CURRENT_LIST_DIR}/Vector3D.cpp
    ${CMAKE_CURRENT_LIST_DIR}/Material.cpp
	${CMAKE_CURRENT_LIST_DIR}/Cell.cpp
    ${CMAKE_CURRENT_LIST_DIR}/Model.cpp
	${CMAKE_CURRENT_LIST_DIR}/Matrix3x3.cpp
)