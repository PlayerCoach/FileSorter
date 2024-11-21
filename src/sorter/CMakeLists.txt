include_directories(sortingAlgorithms)
add_library(SorterLib
 sorter.cpp
 sortingAlgorithms/naturalMergeSort.cpp)
target_include_directories(SorterLib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}) 
target_include_directories(SorterLib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} ../const)
target_link_libraries(SorterLib FileHandlerLib)