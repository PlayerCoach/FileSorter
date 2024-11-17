#include "gtest/gtest.h"
#include "record.h"
#include <iostream>
#include <set>
#include <vector>

TEST(RecordTest, RecordConstructor)
{
    Record record;
    std::cout << record << std::endl;

    Record record2;
    std::cout << record2 << std::endl;

    std::vector<int> testSeries = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16};
    Record record3(testSeries);
    std::cout << record3 << std::endl;
    EXPECT_EQ(record3.getSeries().size(), 15);
    for(int i = 1; i <= 15; i++)
    {
        EXPECT_EQ(record3.getSeries().find(i) != record3.getSeries().end(), true);
    }

}


TEST(RecordTest, RecordComparison)
{
    std::vector<int> testSeriesA =  {15,15,15,15,15,15,15,15,15,15,15,15,15,15,15};
    std::vector<int> testSeriesB = {15,15,15,15,15,15,15,15,15,15,15,15,15,15,14};

    Record recordA(testSeriesA);
    Record recordB(testSeriesB);
    EXPECT_EQ(recordA.getSeries().size(), 1);
    EXPECT_EQ(recordB.getSeries().size(), 2);

    EXPECT_EQ(recordA>recordB, false);
    EXPECT_EQ(recordA<recordB, true);
    EXPECT_EQ(recordA==recordB, false);
    EXPECT_EQ(recordA!=recordB, true);
    EXPECT_EQ(recordA>=recordB, false);
    EXPECT_EQ(recordA<=recordB, true);


}

TEST(RecordTest, RecordComparison2)
{
    std::vector<int> A = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15};
    std::vector<int> B = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15};
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
    std::vector<int> A = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15};
    std::vector<int> B = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,14};
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
    std::vector<int> A = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15};
    std::vector<int> B = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,16};
    Record recordA(A);
    Record recordB(B);
    EXPECT_EQ(recordA>recordB, false);
    EXPECT_EQ(recordA<recordB, true);
    EXPECT_EQ(recordA==recordB, false);
    EXPECT_EQ(recordA!=recordB, true);
    EXPECT_EQ(recordA>=recordB, false);
    EXPECT_EQ(recordA<=recordB, true);

}

TEST(RecordTest, RecordComparison5)
{
    std::vector<int> A = {-1};
    std::vector<int> B = {-2,-3,-4,-5};
    Record recordA(A);
    Record recordB(B);
    EXPECT_EQ(recordA>recordB, true);
    EXPECT_EQ(recordA<recordB, false);
    EXPECT_EQ(recordA==recordB, false);
    EXPECT_EQ(recordA!=recordB, true);
    EXPECT_EQ(recordA>=recordB, true);
    EXPECT_EQ(recordA<=recordB, false);

}

