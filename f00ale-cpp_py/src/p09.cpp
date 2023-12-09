#include "aoc.h"
#include <vector>
#include <algorithm>
#include <iostream>
#include <tuple>
#include <set>

std::tuple<std::string, std::string> p09(const std::string &input) {
    int64_t ans1 = 0;
    int64_t ans2 = 0;
    std::vector<std::vector<int64_t>> v;
    {
        int64_t num = 0;
        bool havenum = false;
        bool first = true;
        bool neg = false;
        for (const auto c: input) {
            if (c >= '0' && c <= '9') {
                num *= 10;
                num += c - '0';
                havenum = true;
            } else {
                if(c == '-') neg = true;
                if(havenum) {
                    if(first) v.emplace_back();
                    if(neg) num = -num;
                    v.back().emplace_back(num);
                    first = false;
                    neg = false;
                }
                if(c == '\n') first = true;
                havenum = false;
                num = 0;
            }
        }

    }

    for(auto & r : v) {
        decltype(v) tmp;
        tmp.emplace_back(r);

        bool all_zero = false;
        while(!all_zero) {
            std::vector<int64_t> oasis;
            all_zero = true;
            for(size_t i = 1; i < tmp.back().size(); i++) {
                oasis.push_back(tmp.back()[i]-tmp.back()[i-1]);
                all_zero = all_zero && oasis.back() == 0;
            }
            tmp.emplace_back(std::move(oasis));
        }

        int64_t back = 0;
        int64_t front = 0;

        for(size_t i = tmp.size(); i > 0; i--) {
            if(i > 1) {
                back += tmp[i-2].back();
                front = tmp[i-2].front() - front;
            }
        }

        ans1 += back;
        ans2 += front;
    }

    return {std::to_string(ans1), std::to_string(ans2)};
}

//  - rätt
