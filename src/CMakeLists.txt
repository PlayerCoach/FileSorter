add_executable(FileSorter
main/main.cpp,
main/mainController.cpp)

#include const.h
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/constants)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/record)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/sorter)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/main)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/fileHandler)
