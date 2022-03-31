#pragma once
//
// Created by Alex Dremov on 31.03.2022.
//

#include "interfaces/MatcherInterface.h"
#include "core/details/Ukkonen.h"

namespace StringMatch {
    /**
     * Searches for first occurrence of pattern in string
     * Utilizes Ukkonen's compressed tree algorithm
     */
    class SingleSearcher : public MatcherInterface {
    public:
        /**
         * Complexity: O(|text|)
         * @param pattern pattern to search
         * @return indexes of all entries
         */
        explicit SingleSearcher(const std::string_view &text);


        /**
         * Complexity: O(|pattern|)
         * @param pattern pattern to search
         * @return index of the first entry
         */
        std::vector<size_t> getEntrances(const std::string &pattern) override;

        ~SingleSearcher() override = default;
    private:
        details::STree tree;
    };
}
