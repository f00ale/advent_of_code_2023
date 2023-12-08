#include "aoc.h"
#include <vector>
#include <algorithm>
#include <iostream>
#include <tuple>
#include <set>
#include <unordered_map>
#include <unordered_set>

std::tuple<std::string, std::string> p08(const std::string &input) {
    int64_t ans1 = 0;
    int64_t ans2 = 0;
    std::unordered_map<std::string, std::tuple<std::string, std::string>> m;
    std::string instructions;
    {
        bool have_ins = false;
        std::vector<std::string> tmpv;
        std::string tmp;
        for (const auto c: input) {
            if ((c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9')) {
                tmp.push_back(c);
            } else {
                if(!tmp.empty()) {
                    tmpv.push_back(tmp);
                    tmp.clear();
                }
                if(c == '\n') {
                    if(!have_ins && tmpv.size() == 1) {
                        have_ins = true;
                        instructions = tmpv[0];
                    } else if(tmpv.size() == 3) {
                        m[tmpv[0]] = std::make_tuple(tmpv[1], tmpv[2]);
                    }
                    tmpv.clear();
                }
            }
        }

    }

    size_t idx = 0;

    std::string current = "AAA";
    while(current != "ZZZ") {
        auto & [l,r] = m[current];
        if(instructions[idx] == 'L') current = l;
        else current = r;
        ans1++;
        idx++;
        if(idx >= instructions.size()) idx = 0;
    }

    std::vector<std::string> currents;
    for(auto & [k,v] : m) {
        if(k[2] == 'A') currents.push_back(k);
    }

    auto get_factors = [](int64_t num) {
        std::vector<int64_t> ret;
        while(num % 2 == 0) {
            num /= 2;
            ret.push_back(2);
        }
        int64_t f = 3;
        while(f*f <= num) {
            while(num % f == 0) {
                num /= f;
                ret.push_back(f);
            }
            f += 2;
        }
        if(num != 1) ret.push_back(num);
        return ret;
    };
    std::unordered_set<int64_t> factors;

    for(auto & current : currents) {
        int64_t cyc = 0;
        idx = 0;
        while(current[2] != 'Z') {
            auto & [l,r] = m[current];
            if(instructions[idx] == 'L') current = l;
            else current = r;
            cyc++;
            idx++;
            if(idx >= instructions.size()) idx = 0;
        }
        for(auto f : get_factors(cyc)) {
            factors.insert(f);
        }
    }

    ans2 = 1;
    for(auto f : factors) {
        ans2 *= f;
    }

    return {std::to_string(ans1), std::to_string(ans2)};
}
