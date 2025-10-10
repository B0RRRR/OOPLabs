#include <gtest/gtest.h>
#include "Seven.h"

TEST(SevenTest, ConstructionFromInt) {
    Seven num1(0);
    Seven num2(7);
    Seven num3(35);

    EXPECT_EQ(num1.toString(), "0");
    EXPECT_EQ(num2.toString(), "10");  // 7₁₀ = 10₇
    EXPECT_EQ(num3.toString(), "50");  // 35₁₀ = 50₇
}

TEST(SevenTest, ConstructionFromString) {
    Seven num("123");
    EXPECT_EQ(num.toString(), "123");

    EXPECT_THROW(Seven(""), std::invalid_argument);
    EXPECT_THROW(Seven("8"), std::invalid_argument); // невалидная цифра
}

TEST(SevenTest, Addition) {
    Seven a(35); // 50₇
    Seven b(15); // 21₇
    Seven sum = Seven::Add(a, b);

    EXPECT_EQ(sum.toString(), "101"); // 35 + 15 = 50 (в 10) = 111₇
}

TEST(SevenTest, Subtraction) {
    Seven a(35); // 50₇
    Seven b(15); // 21₇
    Seven diff = Seven::Subtract(a, b);

    EXPECT_EQ(diff.toString(), "26"); // 20₁₀ = 26₇

    EXPECT_THROW(Seven::Subtract(b, a), std::invalid_argument);
}

TEST(SevenTest, Comparison) {
    Seven a(35);
    Seven b(15);
    Seven c(35);

    EXPECT_TRUE(Seven::Greater(a, b));
    EXPECT_TRUE(Seven::Less(b, a));
    EXPECT_TRUE(Seven::Equals(a, c));
    EXPECT_FALSE(Seven::Equals(a, b));
}

// Проверка сложения с переносом через несколько цифр
TEST(SevenTest, AdditionWithCarry) {
    Seven a("666"); // максимальное трёхзначное семеричное число
    Seven b("1");
    Seven sum = Seven::Add(a, b);
    EXPECT_EQ(sum.toString(), "1000"); // 666₇ + 1₇ = 1000₇
}

// Проверка вычитания с "занятием"
TEST(SevenTest, SubtractionWithBorrow) {
    Seven a("1000"); 
    Seven b("1");
    Seven diff = Seven::Subtract(a, b);
    EXPECT_EQ(diff.toString(), "666"); // 1000₇ - 1₇ = 666₇
}

// Проверка сложения нуля
TEST(SevenTest, AdditionWithZero) {
    Seven a("1234");
    Seven b("0");
    Seven sum = Seven::Add(a, b);
    EXPECT_EQ(sum.toString(), "1234");
}

// Проверка вычитания нуля
TEST(SevenTest, SubtractionWithZero) {
    Seven a("1234");
    Seven diff = Seven::Subtract(a, Seven("0"));
    EXPECT_EQ(diff.toString(), "1234");
}

// Проверка больших чисел
TEST(SevenTest, LargeNumbers) {
    Seven a("666666");
    Seven b("111111");
    Seven sum = Seven::Add(a, b);
    Seven diff = Seven::Subtract(sum, b);
    EXPECT_EQ(sum.toString(), "1111110");
    EXPECT_EQ(diff.toString(), "666666"); // проверка вычитания
}

