#pragma once
//
// Created by Alex Dremov on 31.03.2022.
//

#include <string_view>
#include "interfaces/MatcherInterface.h"

namespace StringMatch {
    /**
     * Searches for occurrence of pattern in string.
     * Utilizes Ukkonen's compressed tree algorithm
     */
    class SmallSearcher : public MatcherInterface {
    public:
        /**
         * Complexity: O(1)
         * @param text text to use
         */
        explicit SmallSearcher(const std::string_view &text);

        /**
         * Complexity: O(|text|)
         * @param pattern pattern to search
         * @return indexes of all entries
         */
        std::vector<size_t> getEntrances(const std::string &pattern) override;

        ~SmallSearcher() override = default;
    private:
        /**
         * Search of pattern, optimized for pattern of length 2, 4, and 8
         * @tparam T uint{16, 32, 64}_t
         * @param pattern pattern to search
         * @return indexes of all entries
         */
        template<typename T>
        std::vector<size_t> searchBatched(const std::string &pattern);

        const std::string_view text;
    };
}
