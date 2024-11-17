include(AddGoogleTest)

add_executable(recordTest
recordTest.cpp 
)
target_link_libraries(recordTest PRIVATE RecordLib GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(recordTest)