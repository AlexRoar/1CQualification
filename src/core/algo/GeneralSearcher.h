#pragma once
//
// Created by Alex Dremov on 31.03.2022.
//
#include <string>
#include <vector>
#include "interfaces/MatcherInterface.h"

namespace StringMatch {
    /**
     * Searches for multiple occurrences of pattern in string
     * Utilizes KMP algorithm
     */
    class GeneralSearcher : public MatcherInterface {
    public:
        /**
         * Complexity: O(1)
         * @param text text to be used
         */
        explicit GeneralSearcher(const std::string_view& text);


        /**
         * Complexity: O(|text| + |pattern|)
         * @param pattern pattern to search
         * @return indexes of all entries
         */
        std::vector<size_t> getEntrances(const std::string &pattern) override;

        ~GeneralSearcher() override = default;
    private:
        const std::string_view& text;
    };
}

