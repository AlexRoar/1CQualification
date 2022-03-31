//
// Created by Alex Dremov on 31.03.2022.
//
#include <gtest/gtest.h>
#include <vector>
#include <string>
#include "core/algo/SingleSearcher.h"

using std::vector;

TEST(SingleSearcherTests, OneChar) {
    vector<std::size_t> actual = {0};
    for (unsigned char i = 1; i < 255; i++) {
        unsigned char text[] = "a";
        text[0] = i;

        StringMatch::SingleSearcher searcher((char *) text);

        auto res = searcher.getEntrances((char *) text);
        ASSERT_EQ(res, actual);
    }
}

TEST(SingleSearcherTests, Stress) {
    auto size = 10;
    std::string text;
    text.reserve(size);
    for(int i = 0; i < size; i++) {
        text += "aba";
    }

    StringMatch::SingleSearcher searcher(text);

    auto res = searcher.getEntrances("aba");
    vector<std::size_t> actual = {0};
    actual.reserve(size);
    ASSERT_EQ(res, actual);
}

TEST(SingleSearcherTests, Middle) {
    std::string text = "abacabadabavavduabacabadu";

    StringMatch::SingleSearcher searcher(text);

    auto res = searcher.getEntrances("abavav");
    vector<std::size_t> actual = {8};
    ASSERT_EQ(res, actual);
}

TEST(SingleSearcherTests, NoEntry) {
    std::string text = "abacabadabavavduabacabadu";

    StringMatch::SingleSearcher searcher(text);

    auto res = searcher.getEntrances("wow");
    vector<std::size_t> actual = {};
    ASSERT_EQ(res, actual);
}

TEST(SingleSearcherTests, NoEntry2) {
    std::string text = "abacabadabavavduabacabadu";

    StringMatch::SingleSearcher searcher(text);

    auto res = searcher.getEntrances("w");
    vector<std::size_t> actual = {};
    ASSERT_EQ(res, actual);
}