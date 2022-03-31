#pragma once

#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <map>
#include <algorithm>

using std::vector;
using std::string;
using std::max;
using std::pair;
using std::fill;
using std::map;

namespace StringMatch::details {
    /**
     * Compressed suffix tree
     * Ukkonen's algorithm
     */
    class STree {
    public:
        explicit STree(const std::string_view& ptext);

        size_t find(const std::string& pattern);
    private:
        static const char ender = '\1';

        struct STreeNode {
            long long parent = -1;
            long long suffLink = -1;
            long long start = 0, end = 0;
            long long suffixIndex = -1;
            map<char, int> next;

            explicit STreeNode(long long l = 0, long long r = 0, long long par = -1);

            [[nodiscard]] long long len() const;

            int &get(char c);
        };

        struct AlgoPos {
            long long v, pos;

            AlgoPos(long long v, long long pos);
        };

        inline size_t size();

        inline char text(size_t pos);

        AlgoPos go(AlgoPos st, long long l, long long r);

        long long split(AlgoPos st);

        long long get_link(long long v);

        void tree_extend(long long pos);

        void build_tree();

        void setSuffixIndexByDFS(size_t n, size_t labelHeight);

        void finalize();

        AlgoPos ptr = {0, 0};
        vector<STreeNode> nodes;
        const std::string_view text_view;
    };
}
