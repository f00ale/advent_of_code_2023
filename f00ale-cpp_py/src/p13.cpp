#include "aoc.h"
#include <vector>
#include <algorithm>
#include <iostream>
#include <tuple>
#include <set>

std::tuple<std::string, std::string> p13(const std::string &input) {
    int64_t ans1 = 0;
    int64_t ans2 = 0;

    std::vector<std::vector<std::string>> v;

    {
        bool last_empty = true;
        for (const auto c: input) {
            if(c == '.' || c == '#') {
                if(last_empty) {
                    v.emplace_back();
                    v.back().emplace_back();
                    last_empty = false;
                }
                v.back().back().push_back(c);
            } else if(c == '\n') {
                if(v.back().back().empty()) {
                    v.back().pop_back();
                    last_empty = true;
                } else {
                    v.back().emplace_back();
                }
            }
        }

    }
    while(v.back().back().empty()) v.back().pop_back();

    decltype(v) flip;
    for(auto & iv : v) {
        flip.emplace_back(iv[0].size(), std::string(iv.size(), ' '));
        for(size_t row = 0; row < iv.size(); row++) {
            for(size_t col = 0; col < iv[row].size(); col++) {
                flip.back()[col][row] = iv[row][col];
            }
        }
    }

    auto check = [](const auto & iv, int diffs, const size_t nok = 0) -> size_t {
        for(size_t i = 0; i < iv.size()-1; i++) {
            if(i+1 == nok) continue;
            size_t off = 0;
            int noks = 0;
            while(off <= i && i+1+off < iv.size()) {
                for(size_t j = 0; j < iv[i].size(); j++) {
                    if(iv[i-off][j] != iv[i+1+off][j]) noks++;
                }
                if(noks > diffs) break;
                off++;
            }
            if(noks == diffs) {
                return i+1;
            }
        }
        return 0;
    };

    for(auto & iv : v) {
        auto tmp = check(iv, 0);
        ans1 += 100*tmp;
        ans2 += 100*check(iv, 1, tmp);
    }

    for(auto & iv : flip) {
        auto tmp = check(iv, 0);
        ans1 += tmp;
        ans2 += check(iv, 1, tmp);
    }

    return {std::to_string(ans1), std::to_string(ans2)};
}
