#pragma once
//
// Created by Alex Dremov on 31.03.2022.
//

#include "interfaces/MatcherInterface.h"

namespace StringMatch {
    /**
     * Optimized pattern search in string.
     * Automatically selects the best algorithm
     */
    class StringMatcher : public MatcherInterface {
    public:
        explicit StringMatcher(const std::string_view &text, bool first = false);


        std::vector<size_t> getEntrances(const std::string &pattern) override;

        ~StringMatcher() override;
    private:
        const std::string_view &text;
        bool single;
        MatcherInterface* matcher = nullptr;
    };
}