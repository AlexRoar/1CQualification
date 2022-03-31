//
// Created by Alex Dremov on 31.03.2022.
//

#include "GeneralSearcher.h"
#include "core/details/KMP.h"

#include <string>
#include <vector>
#include <cstdint>

namespace StringMatch {
    GeneralSearcher::GeneralSearcher(const std::string_view &text)
            : text(text) {}

    std::vector<size_t> GeneralSearcher::getEntrances(const std::string &pattern) {
        details::KMP kmp(this->text);
        return kmp.getEntrances(pattern);
    }
}

