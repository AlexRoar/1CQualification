//
// Created by Alex Dremov on 31.03.2022.
//

#include "LargeMatcher.h"
#include "core/StringMatcher.h"

namespace StringMatch {
    LargeMatcher::LargeMatcher(std::ifstream pfile, bool single, size_t bufferSize)
            : file(std::move(pfile)), single(single), bufferSize(bufferSize) {
        file.seekg(0, std::ios::beg);
        file.seekg(0, std::ios::end);
        size = file.tellg();
    }

    std::vector<size_t> LargeMatcher::getEntrances(const std::string &pattern) {
        std::vector<size_t> entrances;

        auto bufferActualSize = std::max(bufferSize, pattern.size() * 2);
        std::string buffer(bufferActualSize + 1, '\0');

        size_t globalPos = 0;
        while (globalPos + pattern.size() <= size) {
            size_t pos = 0;
            auto stepSize = std::min(size - globalPos, bufferActualSize);

            file.seekg(globalPos);
            file.read(&buffer[0], stepSize);
            buffer[stepSize] = 0;

            std::string_view batch(&buffer[pos]);

            StringMatcher matcher(batch, false);
            for(auto entry: matcher.getEntrances(pattern)) {
                entrances.push_back(entry + globalPos);
                if (single) {
                    return entrances;
                }
            }
            globalPos += stepSize - pattern.size() + 1;
        }

        return entrances;
    }

    LargeMatcher::~LargeMatcher() {
        file.close();
    }
}

