//
// Created by Alex Dremov on 31.03.2022.
//

#include "StringMatcher.h"
#include "core/algo/GeneralSearcher.h"
#include "core/algo/SmallSearcher.h"
#include "core/algo/SingleSearcher.h"

namespace StringMatch {
    StringMatcher::StringMatcher(const std::string_view &text, bool single)
            : text(text), single(single) {
        if (single) {
            matcher = new SingleSearcher(text);
        }
    }

    std::vector<size_t> StringMatcher::getEntrances(const std::string &pattern) {
        if (single) {
            return matcher->getEntrances(pattern);
        }

        switch (pattern.size()) {
            case 1:
            case 2:
            case 4:
            case 8: {
                SmallSearcher searcher(text);
                return searcher.getEntrances(pattern);
            }
            default: {
                GeneralSearcher searcher(text);
                return searcher.getEntrances(pattern);
            }
        }
    }

    StringMatcher::~StringMatcher() {
        delete matcher;
    }
}

