add_library(SorterLib
sorter.cpp
sortingAlgorithms/mergeWithLargeBuffersSort.cpp)
include_directories(sortingAlgorithms)
target_include_directories(SorterLib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}) 
target_include_directories(SorterLib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} ../const)
target_include_directories(SorterLib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} sortingAlgorithms)
target_link_libraries(SorterLib FileHandlerLib)