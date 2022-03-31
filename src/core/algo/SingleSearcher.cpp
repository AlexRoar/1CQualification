//
// Created by Alex Dremov on 31.03.2022.
//

#include "SingleSearcher.h"

namespace StringMatch{
    SingleSearcher::SingleSearcher(const std::string_view &text) :  tree(text) {
    }

    std::vector<size_t> SingleSearcher::getEntrances(const std::string &pattern) {
        auto entry = tree.find(pattern);
        if (entry == -1)
            return {};
        return {entry};
    }

}
