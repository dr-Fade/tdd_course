/*
Given a year, report if it is a leap year.

The tricky thing here is that a leap year in the Gregorian calendar occurs:

on every year that is evenly divisible by 4
  except every year that is evenly divisible by 100
    unless the year is also evenly divisible by 400

For example, 1997 is not a leap year, but 1996 is. 1900 is not a leap year, but 2000 is.

If your language provides a method in the standard library that does this look-up, pretend it doesn't exist and implement it yourself.
*/

#include <gtest/gtest.h>

bool isLeapYear(int year) {
    return !(year % 4) && (year % 100 || !(year % 400));
}

TEST(LeapYear, is4aLeapYearTrue) {
    ASSERT_EQ(true, isLeapYear(4));
}

TEST(LeapYear, is8aLeapYearTrue) {
    ASSERT_EQ(true, isLeapYear(8));
}

TEST(LeapYear, is9aLeapYearFalse) {
    ASSERT_EQ(false, isLeapYear(9));
}

TEST(LeapYear, is12aLeapYearTrue) {
    ASSERT_EQ(true, isLeapYear(12));
}

TEST(LeapYear, is100aLeapYearFalse) {
    ASSERT_EQ(false, isLeapYear(100));
}

TEST(LeapYear, is400aLeapYearTrue) {
    ASSERT_EQ(true, isLeapYear(400));
}

TEST(LeapYear, is1996aLeapYearTrue) {
    ASSERT_EQ(true, isLeapYear(1996));
}

TEST(LeapYear, is1997aLeapYearFalse) {
    ASSERT_EQ(false, isLeapYear(1997));
}

TEST(LeapYear, is1900aLeapYearFalse) {
    ASSERT_EQ(false, isLeapYear(1900));
}

TEST(LeapYear, is2000aLeapYearTrue) {
    ASSERT_EQ(true, isLeapYear(2000));
}
