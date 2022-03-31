#pragma once
//
// Created by Alex Dremov on 31.03.2022.
//

#include <string_view>
#include <string>
#include <vector>

namespace StringMatch::details {
    /**
     * Knuth-Morris-Pratt algorithm for searching pattern in text
     */
    class KMP {
    public:
        std::vector<size_t> getEntrances(const std::string &pat);

        explicit KMP(const std::string_view& text);
    private:
        std::vector<size_t> computeLPSArray(const std::string &pat);

        const std::string_view text;
    };
}
