#include <gtest/gtest.h>
#include <string>
#include <math.h>
/*
Convert a ternary number, represented as a string (e.g. '102012'), to its decimal equivalent using first principles.

The program should consider strings specifying an invalid ternary as the value 0.

Ternary numbers contain three symbols: 0, 1, and 2.

The last place in a ternary number is the 1's place. The second to last is the 3's place, the third to last is the 9's place, etc.

# "102012"
    1       0       2       0       1       2    # the number
1*3^5   + 0*3^4 + 2*3^3 + 0*3^2 + 1*3^1 + 2*3^0    # the value
  243   +   0 +    54 +     0 +     3 +     2 =  302

If your language provides a method in the standard library to perform the conversion, pretend it doesn't exist and implement it yourself.
*/

bool isTernary(const std::string& number) {
    return number == "0" ||
            (number.size() > 1 && number[0] != '0') &&
            number.find_first_not_of("012") == std::string::npos;
}

int fromTernaryToDecimal(std::string number) {
    if(!isTernary(number)) return 0;
    int degree = 0;
    int result = 0;
    while(number.size()) {
        result += (number.back() - '0') * pow(3, degree++);
        number.pop_back();
    }
    return result;
}

TEST(TernaryNumbers, is0aTernaryNumberReturnsTrue) {
    ASSERT_TRUE(isTernary("0"));
}

TEST(TernaryNumbers, is10aTernaryNumberReturnsTrue) {
    ASSERT_TRUE(isTernary("10"));
}

TEST(TernaryNumbers, is123aTernaryNumberReturnsFalse) {
    ASSERT_FALSE(isTernary("123"));
}

TEST(TernaryNumbers, is120aTernaryNumberReturnsTrue) {
    ASSERT_TRUE(isTernary("120"));
}

TEST(TernaryNumbers, is012aTernaryNumberReturnsFalse) {
    ASSERT_FALSE(isTernary("012"));
}

TEST(TernaryNumbers, isEmptyStringaTernaryNumberReturnsFalse) {
    ASSERT_FALSE(isTernary(""));
}

TEST(TernaryNumbers, convert10FromTernaryIs3InDecimal) {
    ASSERT_EQ(3, fromTernaryToDecimal("10"));
}

TEST(TernaryNumbers, notValidumberIs0) {
    ASSERT_EQ(0, fromTernaryToDecimal("asdasd123"));
}

TEST(TernaryNumbers, convert110FromTernaryIs12InDecimal) {
    ASSERT_EQ(12, fromTernaryToDecimal("110"));
}

TEST(TernaryNumbers, convert102012FromTernaryIs302InDecimal) {
    ASSERT_EQ(302, fromTernaryToDecimal("102012"));
}
