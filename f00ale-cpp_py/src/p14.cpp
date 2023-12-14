#include "aoc.h"
#include <vector>
#include <algorithm>
#include <iostream>
#include <tuple>
#include <map>

std::tuple<std::string, std::string> p14(const std::string &input) {
    int64_t ans1 = 0;
    int64_t ans2 = 0;

    std::vector<std::string> v;
    std::vector<int64_t> loads;
    std::map<decltype(v), size_t> memo;
    {
        bool first = true;
        for (const auto c: input) {
            if (c == '.' || c == 'O' || c == '#') {
                if(first) v.emplace_back();
                v.back().push_back(c);
                first = false;
            } else if(c == '\n') {
                first = true;
            }
        }

    }
    for(size_t cycle = 1; cycle < 300000; cycle++) {
        // north
        for (size_t row = 1; row < v.size(); row++) {
            for (size_t col = 0; col < v[0].size(); col++) {
                if (v[row][col] == 'O') {
                    size_t off = 1;
                    while (off <= row) {
                        if (v[row - off][col] == '.') {
                            v[row - off][col] = 'O';
                            v[row - off + 1][col] = '.';
                        } else break;
                        off++;
                    }
                }
            }
        }

        if (!ans1) {
            for (size_t row = 0; row < v.size(); row++) {
                for (size_t col = 0; col < v[0].size(); col++) {
                    if (v[row][col] == 'O') {
                        ans1 += v.size() - row;
                    }
                }
            }
        }
        // west
        for (size_t row = 0; row < v.size(); row++) {
            for (size_t col = 1; col < v[0].size(); col++) {
                if (v[row][col] == 'O') {
                    size_t off = 1;
                    while (off <= col) {
                        if (v[row][col-off] == '.') {
                            v[row][col-off] = 'O';
                            v[row][col-off+1] = '.';
                        } else break;
                        off++;
                    }
                }
            }
        }

        // south
        for (size_t ro = 1; ro < v.size(); ro++) {
            auto row = v.size()-1-ro;
            for (size_t col = 0; col < v[0].size(); col++) {
                if (v[row][col] == 'O') {
                    size_t off = 1;
                    while (row+off < v.size()) {
                        if (v[row + off][col] == '.') {
                            v[row + off][col] = 'O';
                            v[row + off - 1][col] = '.';
                        } else break;
                        off++;
                    }
                }
            }
        }

        // east
        for (size_t row = 0; row < v.size(); row++) {
            for (size_t co = 1; co < v[0].size(); co++) {
                auto col = v[0].size()-1-co;
                if (v[row][col] == 'O') {
                    size_t off = 1;
                    while (col+off < v[0].size()) {
                        if (v[row][col+off] == '.') {
                            v[row][col+off] = 'O';
                            v[row][col+off-1] = '.';
                        } else break;
                        off++;
                    }
                }
            }
        }
        int64_t load = 0;
        for (size_t row = 0; row < v.size(); row++) {
            for (size_t col = 0; col < v[0].size(); col++) {
                if (v[row][col] == 'O') {
                    load += v.size() - row;
                }
            }
        }
        loads.push_back(load);
        auto it = memo.find(v);
        if(it != memo.end()){
            auto off = it->second;
            auto cl = cycle - off;
            auto idx = off + (1'000'000'000 - off - 1) % cl;
            ans2 = loads[idx];
            break;
        }
        memo[v] = cycle;
    }

    return {std::to_string(ans1), std::to_string(ans2)};
}
