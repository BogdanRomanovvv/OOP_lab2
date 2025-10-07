#include <gtest/gtest.h>
#include "twelve.h"

TEST(TwelveAdd, SimpleAdd)
{
    Twelve a("1B");
    Twelve b("05");
    Twelve c = a.add(b);
    EXPECT_EQ(c.ToString(), "24");
}

TEST(TwelveSubtract, SimpleSubtract)
{
    Twelve a("24");
    Twelve b("05");
    Twelve c = a.subtract(b);
    EXPECT_EQ(c.ToString(), "1B");
}

TEST(TwelveSubtract, SubtractToZero)
{
    Twelve a("1B");
    Twelve b("1B");
    Twelve c = a.subtract(b);
    EXPECT_EQ(c.ToString(), "0");
}

TEST(TwelveSubtract, SubtractThrows)
{
    Twelve a("05");
    Twelve b("1B");
    EXPECT_THROW(a.subtract(b), std::logic_error);
}

TEST(TwelveEquals, Equals)
{
    Twelve a("1B");
    Twelve b("1B");
    EXPECT_TRUE(a.equals(b));
}

TEST(TwelveEquals, NotEquals)
{
    Twelve a("1B");
    Twelve b("05");
    EXPECT_FALSE(a.equals(b));
}

TEST(TwelveComparison, LessThan)
{
    Twelve a("05");
    Twelve b("1B");
    EXPECT_TRUE(a.lessThan(b));
    EXPECT_FALSE(b.lessThan(a));
}

TEST(TwelveComparison, GreaterThan)
{
    Twelve a("1B");
    Twelve b("05");
    EXPECT_TRUE(a.greaterThan(b));
    EXPECT_FALSE(b.greaterThan(a));
}

TEST(TwelveCtor, DefaultCtor)
{
    Twelve a;
    EXPECT_EQ(a.ToString(), "0");
}

TEST(TwelveCtor, StringCtor)
{
    Twelve a("1B");
    EXPECT_EQ(a.ToString(), "1B");
}

TEST(TwelveCtor, InitializerListCtor)
{
    Twelve a{1, 11}; // 1 и B
    EXPECT_EQ(a.ToString(), "B1");
}

TEST(TwelveToString, LeadingZeros)
{
    Twelve a("0001B");
    EXPECT_EQ(a.ToString(), "1B");
}

TEST(TwelveCtor, InvalidStringThrows)
{
    EXPECT_THROW(Twelve("");, std::invalid_argument);
    EXPECT_THROW(Twelve("1C"), std::invalid_argument); // 'C' — недопустимый символ
}
