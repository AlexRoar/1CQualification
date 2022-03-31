//
// Created by Alex Dremov on 31.03.2022.
//

#include "Ukkonen.h"

namespace StringMatch::details {
    STree::STreeNode::STreeNode(long long int l, long long int r, long long int par)
            : start(l), end(r), parent(par), suffLink(-1) {}

    long long STree::STreeNode::len() const {
        return end - start;
    }

    int &STree::STreeNode::get(char c) {
        if (next.find(c) == next.end())
            next[c] = -1;
        return next[c];
    }

    STree::AlgoPos::AlgoPos(long long int v, long long int pos) : v(v), pos(pos) {}

    size_t STree::size() {
        return text_view.size() + 1;
    }

    char STree::text(size_t pos) {
        return pos == text_view.size() ? ender : text_view[pos];
    }

    STree::AlgoPos
    STree::go(STree::AlgoPos st, long long int l, long long int r) {
        while (l < r)
            if (st.pos == nodes[st.v].len()) {
                st = AlgoPos(nodes[st.v].get(text(l)), 0);
                if (st.v == -1) return st;
            } else {
                if (text(nodes[st.v].start + st.pos) != text(l))
                    return AlgoPos(-1, -1);
                if (r - l < nodes[st.v].len() - st.pos)
                    return AlgoPos(st.v, st.pos + r - l);
                l += nodes[st.v].len() - st.pos;
                st.pos = nodes[st.v].len();
            }
        return st;
    }

    long long STree::split(STree::AlgoPos st) {
        if (st.pos == nodes[st.v].len())
            return st.v;
        if (st.pos == 0)
            return nodes[st.v].parent;
        STreeNode v = nodes[st.v];
        long long id = nodes.size();
        nodes.emplace_back(v.start, v.start + st.pos, v.parent);
        nodes[v.parent].get(text(v.start)) = id;
        nodes[id].get(text(v.start + st.pos)) = st.v;
        nodes[st.v].parent = id;
        nodes[st.v].start += st.pos;
        return id;
    }

    long long STree::get_link(long long int v) {
        if (nodes[v].suffLink != -1) return nodes[v].suffLink;
        if (nodes[v].parent == -1) return 0;
        long long to = get_link(nodes[v].parent);
        return nodes[v].suffLink = split(go({to, nodes[to].len()},
                                            nodes[v].start + (nodes[v].parent == 0),
                                            nodes[v].end));
    }

    void STree::tree_extend(long long int pos) {
        for (;;) {
            auto nptr = go(ptr, pos, pos + 1);
            if (nptr.v != -1) {
                ptr = nptr;
                return;
            }

            long long mid = split(ptr);
            long long leaf = nodes.size();
            nodes.emplace_back(pos, size(), mid);
            nodes[mid].get(text(pos)) = leaf;
            ptr.v = get_link(mid);
            ptr.pos = nodes[ptr.v].len();
            if (!mid) break;
        }
    }

    void STree::build_tree() {
        nodes.emplace_back(0, 0, -1);
        for (long long i = 0; i < size(); ++i)
            tree_extend(i);
    }

    void STree::setSuffixIndexByDFS(size_t n, size_t labelHeight) {
        size_t minSuffLen = size();
        for (auto i: nodes[n].next) {
            setSuffixIndexByDFS(i.second, labelHeight + nodes[i.second].len());
            minSuffLen = std::min(minSuffLen, (size_t) nodes[i.second].suffixIndex);
        }
        if (nodes[n].next.empty())
            nodes[n].suffixIndex = size() - labelHeight;
        else {
            nodes[n].suffixIndex = minSuffLen;
        }
    }

    void STree::finalize() {
        setSuffixIndexByDFS(0, 0);
    }

    STree::STree(const std::string_view &ptext) : text_view(ptext) {
        build_tree();
        finalize();
    }

    size_t STree::find(const std::string& pattern) {
        AlgoPos st = {0, 0};
        size_t l = 0;
        const size_t r = pattern.size();
        while (l < pattern.size()) {
            if (st.pos == nodes[st.v].len()) {
                st = AlgoPos(nodes[st.v].get(pattern[l]), 0);
                if (st.v == -1)
                    break;
            } else {
                if (text(nodes[st.v].start + st.pos) != pattern[l]) {
                    return -1;
                }
                if (r - l < nodes[st.v].len() - st.pos) {
                    st = AlgoPos(st.v, st.pos + r - l);
                    break;
                }
                l += nodes[st.v].len() - st.pos;
                st.pos = nodes[st.v].len();
            }
        }

        if (st.v == -1)
            return -1;
        return nodes[st.v].suffixIndex;
    }
}