/*
Given a phrase, count the occurrences of each word in that phrase. Ignore whitespaces and punctual symbols
For example for the input "olly olly in come free please please let it be in such manner olly"
olly: 3
in: 2
come: 1
free: 1
please: 2
let: 1
it: 1
be: 1
manner: 1
such: 1
*/

/*
 * There are going to be 2 functions:
 * 1. the one that extracts a word from a sentence and puts them into vector;
 * 2. the one that checks how many times unique words occur in the sentence.
 */

/*
 * Test plan:
 * 1. split "" -> empty vector
 * 2. split "hello" -> vector with one element
 * 3. split "hello world" -> vector with two elements
 * 4. split "hello, world" -> vector with two elements
 * 5. split "hello, world." -> vector with two elements
 * 6. count "" -> empty map
 * 7. count "hello world" -> {{"hello", 1}, {"world", 1}}
 * 8. count "hello, world" -> {{"hello", 1}, {"world", 1}}
 * 9. count "hello, world." -> {{"hello", 1}, {"world", 1}}
 * 10. count "hello world. hello world again" -> {{"hello", 2}, {"world", 2}, {"again", 1}}
 */

#include <gtest/gtest.h>
#include <string>
#include <map>
#include <sstream>

std::vector<std::string> splitPhrase(const std::string& sentence)
{
    std::vector<std::string> result;
    std::istringstream stream(sentence);
    std::string word;

    while(getline(stream, word, ' '))
        result.push_back(word);

    return result;
}

TEST(wordCount, splitEmptyPhrase)
{
    ASSERT_TRUE(splitPhrase("").empty());
}

TEST(wordCount, splitHello)
{
    std::string str = "hello";
    std::vector<std::string> result = {str};

    ASSERT_EQ(result, splitPhrase(str));
}

TEST(wordCount, splitHelloWorld)
{
    std::string str = "hello world";
    std::vector<std::string> result = {"hello", "world"};

    ASSERT_EQ(result, splitPhrase(str));
}

TEST(wordCount, splitHelloCommaWorld)
{
    std::string str = "hello, world";
    std::vector<std::string> result = {"hello", "world"};

    ASSERT_EQ(result, splitPhrase(str));
}
