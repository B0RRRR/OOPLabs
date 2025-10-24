#include <gtest/gtest.h>
#include "Seven.h"

TEST(SevenTest, ConstructionFromInt) {
    seven::Seven num1(0);
    seven::Seven num2(7);
    seven::Seven num3(35);

    EXPECT_EQ(num1.toString(), "0");
    EXPECT_EQ(num2.toString(), "10");
    EXPECT_EQ(num3.toString(), "50");
}

TEST(SevenTest, ConstructionFromString) {
    seven::Seven num("123");
    EXPECT_EQ(num.toString(), "123");

    EXPECT_THROW(seven::Seven(""), std::invalid_argument);
    EXPECT_THROW(seven::Seven("8"), std::invalid_argument);
}

TEST(SevenTest, Addition) {
    seven::Seven a(35);
    seven::Seven b(15);
    seven::Seven sum = seven::Seven::Add(a, b);

    EXPECT_EQ(sum.toString(), "101");
}

TEST(SevenTest, Subtraction) {
    seven::Seven a(35);
    seven::Seven b(15);
    seven::Seven diff = seven::Seven::Subtract(a, b);

    EXPECT_EQ(diff.toString(), "26");
    EXPECT_THROW(seven::Seven::Subtract(b, a), std::invalid_argument);
}

TEST(SevenTest, Comparison) {
    seven::Seven a(35);
    seven::Seven b(15);
    seven::Seven c(35);

    EXPECT_TRUE(seven::Seven::Greater(a, b));
    EXPECT_TRUE(seven::Seven::Less(b, a));
    EXPECT_TRUE(seven::Seven::Equals(a, c));
    EXPECT_FALSE(seven::Seven::Equals(a, b));
}

TEST(SevenTest, AdditionWithCarry) {
    seven::Seven a("666");
    seven::Seven b("1");
    seven::Seven sum = seven::Seven::Add(a, b);
    EXPECT_EQ(sum.toString(), "1000");
}

TEST(SevenTest, SubtractionWithBorrow) {
    seven::Seven a("1000"); 
    seven::Seven b("1");
    seven::Seven diff = seven::Seven::Subtract(a, b);
    EXPECT_EQ(diff.toString(), "666");
}

TEST(SevenTest, AdditionWithZero) {
    seven::Seven a("1234");
    seven::Seven b("0");
    seven::Seven sum = seven::Seven::Add(a, b);
    EXPECT_EQ(sum.toString(), "1234");
}

TEST(SevenTest, SubtractionWithZero) {
    seven::Seven a("1234");
    seven::Seven diff = seven::Seven::Subtract(a, seven::Seven("0"));
    EXPECT_EQ(diff.toString(), "1234");
}

TEST(SevenTest, LargeNumbers) {
    seven::Seven a("666666");
    seven::Seven b("111111");
    seven::Seven sum = seven::Seven::Add(a, b);
    seven::Seven diff = seven::Seven::Subtract(sum, b);
    EXPECT_EQ(sum.toString(), "1111110");
    EXPECT_EQ(diff.toString(), "666666");
}
