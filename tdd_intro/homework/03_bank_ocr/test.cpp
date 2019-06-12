/*### Bank OCR

Your manager has recently purchased a machine that assists in reading letters and faxes sent in by branch offices. The machine scans the paper documents, and produces a file with a number of entries. You will write a program to parse this file.

#### Specification
#### User Story 1

The following format is created by the machine:
```
    _  _     _  _  _  _  _
  | _| _||_||_ |_   ||_||_|
  ||_  _|  | _||_|  ||_| _|
```
Each entry is 3 lines long, and each line has 27 characters. 3 lines of each entry contain an account number written using pipes and underscores.

Each account number should have 9 digits, all of which should be in the range 0-9. A normal file contains around 500 entries.

Write a program that can take this file and parse it into actual account numbers.

Example input and output
```
 _  _  _  _  _  _  _  _  _
| || || || || || || || || |
|_||_||_||_||_||_||_||_||_|

=> 000000000

  |  |  |  |  |  |  |  |  |
  |  |  |  |  |  |  |  |  |

=> 111111111

 _  _  _  _  _  _  _  _  _
 _| _| _| _| _| _| _| _| _|
|_ |_ |_ |_ |_ |_ |_ |_ |_

=> 222222222

 _  _  _  _  _  _  _  _  _
 _| _| _| _| _| _| _| _| _|
 _| _| _| _| _| _| _| _| _|

=> 333333333

|_||_||_||_||_||_||_||_||_|
  |  |  |  |  |  |  |  |  |

=> 444444444

 _  _  _  _  _  _  _  _  _
|_ |_ |_ |_ |_ |_ |_ |_ |_
 _| _| _| _| _| _| _| _| _|

=> 555555555

 _  _  _  _  _  _  _  _  _
|_ |_ |_ |_ |_ |_ |_ |_ |_
|_||_||_||_||_||_||_||_||_|

=> 666666666

 _  _  _  _  _  _  _  _  _
  |  |  |  |  |  |  |  |  |
  |  |  |  |  |  |  |  |  |

=> 777777777

 _  _  _  _  _  _  _  _  _
|_||_||_||_||_||_||_||_||_|
|_||_||_||_||_||_||_||_||_|

=> 888888888

 _  _  _  _  _  _  _  _  _
|_||_||_||_||_||_||_||_||_|
 _| _| _| _| _| _| _| _| _|

=> 999999999

    _  _     _  _  _  _  _
  | _| _||_||_ |_   ||_||_|
  ||_  _|  | _||_|  ||_| _|

=> 123456789
```
*/

/*
 * ARCHITECTURE:
 * There are going to be 3 functions:
 * 1. the one that casts a single Digit to a valid integer symbol
 * 2. the one that casts 3x27 input to a valid string of integers
 * 3. the one that reads new entries and handles the output
 */

/* TEST PLAN:
 * 1. Convert '1';
 * 2. Convert '2';
 * 3. Convert '3';
 * 4. Convert '000000000';
 * 5. Convert '111111111';
 * 6. Convert '222222222';
 * 7. Convert '333333333';
 * 8. Convert '123456789';
 * 9. Convert '987654321';
 * 10. Convert '123456789'
 *             '987654321';
 */

/*
 * New tests needed:
 * 1. convert Display to Digit:
 *   a. 000000000 -> {000000000}
 *   b. 123456789 -> {123456789g}
 */

#include <gtest/gtest.h>
#include <digit.h>
#include <string>

bool compareDigits(const Digit& d1, const Digit& d2)
{
    for (int i = 0; i < g_linesInDigit; i++)
        if(d1.lines[i] != d2.lines[i])
            return false;
    return true;
}

char mapSingleDigit(const Digit& digit)
{
    if (compareDigits(digit, s_digit0)) return '0';
    if (compareDigits(digit, s_digit1)) return '1';
    if (compareDigits(digit, s_digit2)) return '2';
    if (compareDigits(digit, s_digit3)) return '3';
    if (compareDigits(digit, s_digit4)) return '4';
    if (compareDigits(digit, s_digit5)) return '5';
    if (compareDigits(digit, s_digit6)) return '6';
    if (compareDigits(digit, s_digit7)) return '7';
    if (compareDigits(digit, s_digit8)) return '8';
    if (compareDigits(digit, s_digit9)) return '9';
    return '~';
}

std::string mapEntry(const std::vector<Digit> &entry)
{
    std::string result;
    for (Digit d : entry)
    {
        result.push_back(mapSingleDigit(d));
    }
    return result;
}

std::vector<Digit> displayToDigits(const Display& display)
{
    std::vector<Digit> result;
    for (int i = 0; i < g_digitsOnDisplay * g_digitLen; i += g_digitLen)
    {
        Digit d = { display.lines[0].substr(i, g_digitLen),
                    display.lines[1].substr(i, g_digitLen),
                    display.lines[2].substr(i, g_digitLen)
                  };
        result.push_back(d);
    }
    return result;
}

TEST(entryConverter, map1)
{
    ASSERT_EQ('1', mapSingleDigit(s_digit1));
}

TEST(entryConverter, map2)
{
    ASSERT_EQ('2', mapSingleDigit(s_digit2));
}

TEST(entryConverter, map3)
{
    ASSERT_EQ('3', mapSingleDigit(s_digit3));
}

TEST(entryConverter, mapAllZeroesEntry)
{
    std::vector<Digit> entry;
    for (int i = 0; i < g_digitsOnDisplay; i++) entry.insert(entry.end(), s_digit0);
    ASSERT_EQ("000000000", mapEntry(entry));
}

TEST(entryConverter, mapAllOnesEntry)
{
    std::vector<Digit> entry;
    for (int i = 0; i < g_digitsOnDisplay; i++) entry.insert(entry.end(), s_digit1);
    ASSERT_EQ("111111111", mapEntry(entry));
}

TEST(entryConverter, mapAllDigitsEntry)
{
    std::vector<Digit> entry;
    entry.push_back(s_digit1);
    entry.push_back(s_digit2);
    entry.push_back(s_digit3);
    entry.push_back(s_digit4);
    entry.push_back(s_digit5);
    entry.push_back(s_digit6);
    entry.push_back(s_digit7);
    entry.push_back(s_digit8);
    entry.push_back(s_digit9);
    ASSERT_EQ("123456789", mapEntry(entry));
}

TEST(entryConverter, convert000000000DisplayToDigits)
{
    std::vector<Digit> entry;
    entry.push_back(s_digit0);
    entry.push_back(s_digit0);
    entry.push_back(s_digit0);
    entry.push_back(s_digit0);
    entry.push_back(s_digit0);
    entry.push_back(s_digit0);
    entry.push_back(s_digit0);
    entry.push_back(s_digit0);
    entry.push_back(s_digit0);
    std::vector<Digit> result = displayToDigits(s_displayAll0);
    for (int i = 0; i < entry.size(); i++)
        ASSERT_TRUE(compareDigits(entry[i], result[i]));
}
