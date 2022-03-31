//
// Created by Alex Dremov on 31.03.2022.
//
#include <gtest/gtest.h>
#include <vector>
#include <string>
#include "core/algo/GeneralSearcher.h"

using std::vector;

// Demonstrate some basic assertions.
TEST(GeneralSearcherTest, OneChar) {
    vector<std::size_t> actual = {0};
    for (unsigned char i = 1; i < 255; i++) {
        unsigned char text[] = "a";
        text[0] = i;

        StringMatch::GeneralSearcher searcher((char *) text);

        auto res = searcher.getEntrances((char *) text);
        ASSERT_EQ(res, actual);
    }
}

TEST(GeneralSearcherTest, OneCharString) {
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

        StringMatch::GeneralSearcher searcher((char *) text);
        auto res = searcher.getEntrances((char *) pat);
        ASSERT_EQ(res, actual);
    }
}

TEST(GeneralSearcherTest, CustomString8) {
    const char *text = "abacabacabacabacabacabacabacabac";

    StringMatch::GeneralSearcher searcher(text);

    auto res = searcher.getEntrances("abacabac");
    vector<std::size_t> actual = {0, 4, 8, 12, 16, 20, 24};
    ASSERT_EQ(res, actual);
}

TEST(GeneralSearcherTest, CustomString4) {
    const char *text = "abacabacdcba";

    StringMatch::GeneralSearcher searcher(text);

    auto res = searcher.getEntrances("abac");
    vector<std::size_t> actual = {0, 4};
    ASSERT_EQ(res, actual);
}

TEST(GeneralSearcherTest, CustomString2) {
    const char *text = "abacabacdcbab";

    StringMatch::GeneralSearcher searcher(text);

    auto res = searcher.getEntrances("ab");
    vector<std::size_t> actual = {0, 4, 11};
    ASSERT_EQ(res, actual);
}

TEST(GeneralSearcherTest, Stress) {
    auto size = 10'000'000;
    std::string text = "";
    text.reserve(size);
    for(int i = 0; i < size; i++) {
        text += "aba";
    }

    StringMatch::GeneralSearcher searcher(text);

    auto res = searcher.getEntrances("aba");
    vector<std::size_t> actual;
    actual.reserve(size);
    for(int i = 0; i < size; i++) {
        actual.push_back(i * 3);
    }
    ASSERT_EQ(res, actual);
}

TEST(GeneralSearcherTest, Last) {
    size_t size = 10'000'000;
    std::string text = "";
    text.reserve(size);
    for(int i = 0; i < size; i++) {
        text += "aba";
    }
    text += "x";

    StringMatch::GeneralSearcher searcher(text);

    auto res = searcher.getEntrances("x");
    vector<std::size_t> actual = {size * 3};
    ASSERT_EQ(res, actual);
}