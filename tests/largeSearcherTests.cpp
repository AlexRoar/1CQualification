//
// Created by Alex Dremov on 31.03.2022.
//
#include <gtest/gtest.h>
#include <vector>
#include "core/algo/LargeMatcher.h"

using std::vector;

TEST(LargeFileTest, Stress) {
    std::ofstream outFile ("test.txt");
    outFile.clear();
    auto size = 10;
    std::string text = "";
    text.reserve(size);
    for(int i = 0; i < size; i++) {
        text += "aba";
    }
    outFile<<text;
    outFile.close();

    std::ifstream infile ("test.txt");
    StringMatch::LargeMatcher matcher(std::move(infile), false, 11);

    auto res = matcher.getEntrances("aba");
    vector<std::size_t> actual;
    actual.reserve(size);
    for(int i = 0; i < size; i++) {
        actual.push_back(i * 3);
    }
    ASSERT_EQ(res, actual);
}

TEST(LargeFileTest, Stress2) {
    std::ofstream outFile ("test.txt");
    outFile.clear();
    auto size = 10'000'000;
    std::string text = "";
    text.reserve(size);
    for(int i = 0; i < size; i++) {
        text += "aba";
    }
    outFile<<text;
    outFile.close();

    std::ifstream infile ("test.txt");
    StringMatch::LargeMatcher matcher(std::move(infile), false, 1000000000);

    auto res = matcher.getEntrances("aba");
    vector<std::size_t> actual;
    actual.reserve(size);
    for(int i = 0; i < size; i++) {
        actual.push_back(i * 3);
    }
    ASSERT_EQ(res, actual);
}

TEST(LargeFileTest, Stress3) {
    std::ofstream outFile ("test.txt");
    outFile.clear();
    auto size = 10'000'000;
    std::string text = "";
    text.reserve(size);
    for(int i = 0; i < size; i++) {
        text += "a";
    }
    outFile<<text;
    outFile.close();

    std::ifstream infile ("test.txt");
    StringMatch::LargeMatcher matcher(std::move(infile), false, 1000000000);

    auto res = matcher.getEntrances("a");
    vector<std::size_t> actual;
    actual.reserve(size);
    for(int i = 0; i < size; i++) {
        actual.push_back(i);
    }
    ASSERT_EQ(res, actual);
}

TEST(LargeFileTest, Last) {
    std::ofstream outFile ("test.txt");
    outFile.clear();
    size_t size = 10'000'000;
    std::string text = "";
    text.reserve(size);
    for(int i = 0; i < size; i++) {
        text += "a";
    }
    text += "b";
    outFile<<text;
    outFile.close();

    std::ifstream infile ("test.txt");
    StringMatch::LargeMatcher matcher(std::move(infile), false, 1000000000);

    auto res = matcher.getEntrances("b");
    vector<std::size_t> actual = {size};
    ASSERT_EQ(res, actual);
}