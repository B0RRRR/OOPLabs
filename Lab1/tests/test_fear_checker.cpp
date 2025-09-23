#include <gtest/gtest.h>
#include "../include/fear_checker.h"

TEST(FearCheckerTest, Monday) {
    EXPECT_TRUE(isAfraid("понедельник", 12));
    EXPECT_FALSE(isAfraid("понедельник", 13));
    EXPECT_FALSE(isAfraid("ПОНЕДЕЛЬНИК", 11));
}

TEST(FearCheckerTest, Tuesday) {
    EXPECT_TRUE(isAfraid("вторник", 96));
    EXPECT_FALSE(isAfraid("вторник", 95));
    EXPECT_FALSE(isAfraid("ВТОРНИК", 50));
}

TEST(FearCheckerTest, Wednesday) {
    EXPECT_TRUE(isAfraid("среда", 34));
    EXPECT_FALSE(isAfraid("среда", 35));
}

TEST(FearCheckerTest, Thursday) {
    EXPECT_TRUE(isAfraid("четверг", 0));
    EXPECT_FALSE(isAfraid("четверг", 1));
}

TEST(FearCheckerTest, Friday) {
    EXPECT_TRUE(isAfraid("пятница", 4));
    EXPECT_TRUE(isAfraid("пятница", -2));
    EXPECT_FALSE(isAfraid("пятница", 3));
}

TEST(FearCheckerTest, Saturday) {
    EXPECT_TRUE(isAfraid("суббота", 56));
    EXPECT_FALSE(isAfraid("суббота", 55));
}

TEST(FearCheckerTest, Sunday) {
    EXPECT_TRUE(isAfraid("воскресенье", 666));
    EXPECT_TRUE(isAfraid("воскресенье", -666));
    EXPECT_FALSE(isAfraid("воскресенье", 0));
}

TEST(FearCheckerTest, CaseInsensitive) {
    EXPECT_TRUE(isAfraid("ПОНЕДЕЛЬНИК", 12));
    EXPECT_TRUE(isAfraid("ВтОрНиК", 100));
    EXPECT_TRUE(isAfraid("СрЕдА", 34));
}

TEST(FearCheckerTest, InvalidDay) {
    EXPECT_THROW(isAfraid("панедельниг", 42), std::invalid_argument);
    EXPECT_THROW(isAfraid("январь", 100), std::invalid_argument);
}