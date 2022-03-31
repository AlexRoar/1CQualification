//
// Created by Alex Dremov on 31.03.2022.
//

#include "KMP.h"

namespace StringMatch::details {
    std::vector<size_t> KMP::computeLPSArray(const std::string &pat) {
        std::vector<size_t> lps(pat.size());
        lps[0] = 0;
        size_t len = 0, i = 1;
        while (i < pat.size()) {
            if (pat[i] == pat[len]) {
                len++;
                lps[i] = len;
                i++;
            } else {
                if (len != 0) {
                    len = lps[len - 1];
                } else // if (len == 0)
                {
                    lps[i] = 0;
                    i++;
                }
            }
        }
        return lps;
    }

    KMP::KMP(const std::string_view &text) : text(text) {}

    std::vector<size_t> KMP::getEntrances(const std::string &pat) {
        std::vector<size_t> entrances;

        auto M = pat.size(), N = text.size();
        auto lps = computeLPSArray(pat);

        size_t i = 0;
        size_t j = 0;
        while (i < N) {
            if (pat[j] == text[i]) {
                j++;
                i++;
            }

            if (j == M) {
                entrances.push_back(i - j);
                j = lps[j - 1];
            } else if (i < N && pat[j] != text[i]) {
                if (j != 0)
                    j = lps[j - 1];
                else
                    i = i + 1;
            }
        }
        return entrances;
    }
}