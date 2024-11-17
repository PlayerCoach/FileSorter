add_library(FileHandlerLib
 fileHandler.cpp
 inputHandler.cpp
 outputHandler.cpp)
target_include_directories(RecordLib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}) 
target_include_directories(RecordLib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} ../const)
target_link_libraries(FileHandlerLib RecordLib)