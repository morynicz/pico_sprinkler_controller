#include "utils/io_testing.hpp"
#include "gtest/gtest.h"
#include "gmock/gmock.h"

TEST(NumToDispTests, NumToDispCorrectlyTranslatesInput)
{
    using testing::IsEmpty;
    using testing::ElementsAre;
    std::vector<int> outputs{10,11,12,13,14};

    EXPECT_THAT(numToDisp(outputs, 0), IsEmpty());
    EXPECT_THAT(numToDisp(outputs, 1), ElementsAre(10));
    EXPECT_THAT(numToDisp(outputs, 2), ElementsAre(11));
    EXPECT_THAT(numToDisp(outputs, 3), ElementsAre(10, 11));
    EXPECT_THAT(numToDisp(outputs, 4), ElementsAre(12));
    EXPECT_THAT(numToDisp(outputs, 27), ElementsAre(10, 11, 13, 14));
    EXPECT_THAT(numToDisp(outputs, 31), ElementsAre(10, 11, 12, 13, 14));
    
       
}