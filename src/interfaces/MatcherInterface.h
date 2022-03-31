#pragma once
//
// Created by Alex Dremov on 31.03.2022.
//
#include <vector>
#include <string>

namespace StringMatch {
    /**
     * Interface for string matching algorithm
     */
    class MatcherInterface {
    public:
        virtual std::vector<size_t> getEntrances(const std::string& pattern) = 0;
        virtual ~MatcherInterface() = default;
    };
}
