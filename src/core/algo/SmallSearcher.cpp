//
// Created by Alex Dremov on 31.03.2022.
//

#include "SmallSearcher.h"
#include <exception>
#include <cstring>
#include <stdexcept>

namespace StringMatch {
    SmallSearcher::SmallSearcher(const std::string_view &text) :
            text(text) {

    }

    std::vector<size_t> SmallSearcher::getEntrances(const std::string &pattern) {
        if (pattern.size() != 1 && pattern.size() != 2 && pattern.size() != 4 && pattern.size() != 8) {
            throw std::runtime_error("Cannot use SmallSearcher for pattern with specified length");
        }

        if (text.size() < pattern.size())
            return {};

        std::vector<size_t> entrances;
        if (pattern.size() == 8) {
            entrances = searchBatched<uint64_t>(pattern);
        } else if (pattern.size() == 4) {
            entrances = searchBatched<uint32_t>(pattern);
        } else if (pattern.size() == 2) {
            entrances = searchBatched<uint16_t>(pattern);
        } else { // pattern.size() == 1
            const char* textPacked = (text.begin());
            size_t lastPos = -1;
            char pat = pattern[0];
            while (true) {
                auto newEntry = strchr(textPacked + lastPos + 1, pat);
                if(newEntry == nullptr)
                    break;
                lastPos = size_t(newEntry - textPacked);
                entrances.push_back(lastPos);
            }
        }
        return entrances;
    }

    template<typename T>
    std::vector<size_t> SmallSearcher::searchBatched(const std::string &pattern) {
        std::vector<size_t> entrances;

        T patternPacked = *(T *) (pattern.c_str());
        const char* textPacked = (text.begin());

        for (size_t i = 0; i <= text.size() - pattern.size(); i++) {
            T ptr = *(const T *) (textPacked + i);
            if (ptr == patternPacked) {
                entrances.push_back(i);
            }
        }
        return entrances;
    }
}
