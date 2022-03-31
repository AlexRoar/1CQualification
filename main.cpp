#include <iostream>
#include <string>
#include <fstream>
#include <string_view>
#include "core/utils/cxxopts.hpp"
#include "core/StringMatcher.h"
#include "core/algo/LargeMatcher.h"

int main(const int argc, const char** argv) {
    cxxopts::Options options("StringMatch", "Search substring in a file, enter substring to stdin. Type !exit to exit");
    options.add_options()
            ("f,file", "File name", cxxopts::value<std::string>())
            ("s,single", "Get first entry only", cxxopts::value<bool>()->default_value("false"))
            ("x,extralarge", "Extra large file search. O(nm) solution but can work with extra large data", cxxopts::value<bool>()->default_value("false"))
            ("b,buffSize", "Buffer size for extra large mode. 100Mb by default", cxxopts::value<int>()->default_value("0"))
            ("v,verbose", "Verbose", cxxopts::value<bool>()->default_value("true"))
            ("h,help", "Print usage");
    cxxopts::ParseResult cl;

    try {
        cl = options.parse(argc, argv);
    } catch (...) {
        std::cout << options.help() << std::endl;
        exit(1);
    }

    if (cl.count("help")) {
        std::cout << options.help() << std::endl;
        exit(0);
    }
    bool single, extralarge, verbose;
    std::string fileName;
    int buffSize = 1024 * 1024 * 100;
    try {
        extralarge = cl["extralarge"].as<bool>();
        fileName = cl["file"].as<std::string>();
        single = cl["single"].as<bool>();
        verbose = cl["verbose"].as<bool>();
        auto buffSizeTmp = cl["buffSize"].as<int>();
        if (buffSizeTmp != 0)
            buffSize = cl["buffSize"].as<int>();
    } catch (...) {
        std::cout << options.help() << std::endl;
        exit(1);
    }

    std::ifstream t(fileName);
    t.seekg(0, std::ios::end);
    std::streamsize size = t.tellg();

    if (size == -1) {
        std::cout << "Unable to read file " << fileName << std::endl;
        std::cout << options.help() << std::endl;
        exit(1);
    }

    StringMatch::MatcherInterface* matcher;
    std::string buffer;
    if (extralarge){
        matcher = new StringMatch::LargeMatcher(std::move(t), single, buffSize);
    } else {
        buffer.resize(size + 1, ' ');
        t.seekg(0);
        t.read(&buffer[0], size);
        t.close();
        matcher = new StringMatch::StringMatcher(buffer, single);
    }
    if(verbose) {
        std::cout << "Ready" << std::endl;
    }
    for (std::string line; std::getline(std::cin, line);) {
        if(line == "!exit") {
            break;
        }
        auto res = matcher->getEntrances(line);
        for (auto i: res) {
            std::cout << i << ' ';
        }
        if (res.empty()) {
            std::cout << "<no entry>";
        }
        std::cout << std::endl;
    }

    delete matcher;
    return 0;
}
