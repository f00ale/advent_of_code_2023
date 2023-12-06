#include "aoc.h"
#include <vector>
#include <algorithm>
#include <iostream>
#include <tuple>
#include <set>

std::tuple<std::string, std::string> p06(const std::string &input) {
    int64_t ans1 = 0;
    int64_t ans2 = 0;

    for(int p : {1,2})
    {
        std::vector<int64_t> time;
        std::vector<int64_t> dist;

        int64_t num = 0;
        bool havenum = false;
        bool have_time = false;
        for (const auto c: input) {
            if (c >= '0' && c <= '9') {
                num *= 10;
                num += c - '0';
                havenum = true;
            } else {
                if(p == 1) {
                    if(havenum) {
                        (have_time ? dist : time).push_back(num);
                    }
                    if(c == '\n') {
                        have_time = true;
                    }
                    havenum = false;
                    num = 0;
                } else if(c == '\n' && havenum) {
                    (have_time ? dist : time).push_back(num);
                    have_time = true;
                    havenum = false;
                    num = 0;
                }
            }
        }

        (p == 1 ? ans1 : ans2) = 1;
        for(decltype(time)::size_type i = 0; i < time.size(); i++) {
            int64_t ways = 0;
            for(int k = 0; k < time[i]; k++) {
                auto d = k * (time[i]-k);
                if(d > dist[i]) ways++;
            }
            (p == 1 ? ans1 : ans2) *= ways;
        }
    }

    return {std::to_string(ans1), std::to_string(ans2)};
}
