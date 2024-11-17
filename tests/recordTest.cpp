#include "gtest/gtest.h"
#include "record.h"
#include <iostream>

TEST(RecordTest, RecordConstructor)
{
    Record record;
    std::cout << record << std::endl;

    Record record2;
    std::cout << record2 << std::endl;

    int testSeries[RECORD_SERIES_LENGTH] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15};
    Record record3(testSeries);
    std::cout << record3 << std::endl;
}

TEST(RecordTest, RecordSetters)
{
    Record record;
    record[0] = 1;
    record[1] = 2;
    record[2] = 3;
    std::cout << record<< std::endl;
    EXPECT_EQ(record[0], 1);
    EXPECT_EQ(record[1], 2);
    EXPECT_EQ(record[2], 3);

}

TEST(RecordTest, RecordComparison)
{
    int testSeriesA[RECORD_SERIES_LENGTH] = {15,15,15,15,15,15,15,15,15,15,15,15,15,15,15};
    int testSeriesB[RECORD_SERIES_LENGTH] = {15,15,15,15,15,15,15,15,15,15,15,15,15,15,14};
    Record recordA(testSeriesA);
    Record recordB(testSeriesB);
    EXPECT_EQ(recordA>recordB, false);
    EXPECT_EQ(recordA<recordB, true);
    EXPECT_EQ(recordA==recordB, false);
    EXPECT_EQ(recordA!=recordB, true);
    EXPECT_EQ(recordA>=recordB, false);
    EXPECT_EQ(recordA<=recordB, true);


}

TEST(RecordTest, RecordComparison2)
{
    int A[RECORD_SERIES_LENGTH] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15};
    int B[RECORD_SERIES_LENGTH] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15};
    Record recordA(A);
    Record recordB(B);
    EXPECT_EQ(recordA>recordB, false);
    EXPECT_EQ(recordA<recordB, false);
    EXPECT_EQ(recordA==recordB, true);
    EXPECT_EQ(recordA!=recordB, false);
    EXPECT_EQ(recordA>=recordB, true);
    EXPECT_EQ(recordA<=recordB, true);

}

TEST(RecordTest, RecordComparison3)
{
    int A[RECORD_SERIES_LENGTH] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15};
    int B[RECORD_SERIES_LENGTH] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,14};
    Record recordA(A);
    Record recordB(B);
    EXPECT_EQ(recordA>recordB, true);
    EXPECT_EQ(recordA<recordB, false);
    EXPECT_EQ(recordA==recordB, false);
    EXPECT_EQ(recordA!=recordB, true);
    EXPECT_EQ(recordA>=recordB, true);
    EXPECT_EQ(recordA<=recordB, false);

}

TEST(RecordTest, RecordComparison4)
{
    int A[RECORD_SERIES_LENGTH] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15};
    int B[RECORD_SERIES_LENGTH] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,16};
    Record recordA(A);
    Record recordB(B);
    EXPECT_EQ(recordA>recordB, false);
    EXPECT_EQ(recordA<recordB, true);
    EXPECT_EQ(recordA==recordB, false);
    EXPECT_EQ(recordA!=recordB, true);
    EXPECT_EQ(recordA>=recordB, false);
    EXPECT_EQ(recordA<=recordB, true);

}



TEST(RecordTest, RecordAssignment)
{
    Record record;
    Record record2;
    record2 = record;
    std::cout << record2 << std::endl;
    EXPECT_EQ(record, record2);
    record2[0] = 1;
    record[0] = 2;
    EXPECT_NE(record, record2);
}

