#pragma once
//
// Created by Alex Dremov on 31.03.2022.
//
#include <fstream>
#include "interfaces/MatcherInterface.h"

namespace StringMatch {
    /**
     * Find occurances in file without loading the whole file into the memory
     */
    class LargeMatcher : public MatcherInterface {
    public:
        /**
         *
         * @param file file to search string in
         * @param single is first occurance
         * @param bufferSize size of buffer
         */
        explicit LargeMatcher(std::ifstream file, bool single, size_t bufferSize = 1024 * 1024 * 100);

        /**
         * Complexity: O(|text|)
         * @param pattern
         * @return
         */
        std::vector<size_t> getEntrances(const std::string &pattern) override;

        ~LargeMatcher() override;;

    private:
        const size_t bufferSize;
        std::ifstream file;
        bool single;
        size_t size;
    };

}
