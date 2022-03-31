//
// Created by Alex Dremov on 31.03.2022.
//
#include <gtest/gtest.h>
#include <vector>
#include "core/algo/SmallSearcher.h"

using std::vector;

// Demonstrate some basic assertions.
TEST(SmallSearcherTest, OneChar) {
    vector<std::size_t> actual = {0};
    for (unsigned char i = 1; i < 255; i++) {
        unsigned char text[] = "a";
        text[0] = i;

        StringMatch::SmallSearcher searcher((char *) text);

        auto res = searcher.getEntrances((char *) text);
        ASSERT_EQ(res, actual);
    }
}

TEST(SmallSearcherTest, OneCharString) {
    constexpr int size = 16;
    vector<std::size_t> actual = {};
    actual.reserve(size);
    for (int i = 0; i < size; i++)
        actual.push_back(i);

    for (unsigned char i = 1; i < 255; i++) {
        unsigned char pat[size] = {i, 0};
        unsigned char text[size + 1] = {};
        for (auto &c: text) {
            c = i;
        }
        text[size] = 0;

        StringMatch::SmallSearcher searcher((char *) text);
        auto res = searcher.getEntrances((char *) pat);
        ASSERT_EQ(res, actual);
    }
}

TEST(SmallSearcherTest, CustomString8) {
    const char *text = "abacabacabacabacabacabacabacabac";

    StringMatch::SmallSearcher searcher(text);

    auto res = searcher.getEntrances("abacabac");
    vector<std::size_t> actual = {0, 4, 8, 12, 16, 20, 24};
    ASSERT_EQ(res, actual);
}

TEST(SmallSearcherTest, CustomString2) {
    const char *text = "abacabacdcbab";

    StringMatch::SmallSearcher searcher(text);

    auto res = searcher.getEntrances("ab");
    vector<std::size_t> actual = {0, 4, 11};
    ASSERT_EQ(res, actual);
}

TEST(SmallSearcherTest, WrongSizes) {
    const char *text = "abacabacdcbab";

    StringMatch::SmallSearcher searcher(text);

    EXPECT_ANY_THROW(searcher.getEntrances("123"));
    EXPECT_ANY_THROW(searcher.getEntrances("12345"));
    EXPECT_ANY_THROW(searcher.getEntrances("123456"));
    EXPECT_ANY_THROW(searcher.getEntrances("1234567"));
    EXPECT_ANY_THROW(searcher.getEntrances("123456789"));
}