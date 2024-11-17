


# creates a library from the record class
add_library(RecordLib record.cpp)
# gives access to the header files in the include directory
target_include_directories(RecordLib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}) 
target_include_directories(RecordLib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} ../const)
