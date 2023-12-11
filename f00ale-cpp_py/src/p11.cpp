#include "aoc.h"
#include <vector>
#include <algorithm>
#include <iostream>
#include <tuple>
#include <set>

std::tuple<std::string, std::string> p11(const std::string &input) {
    int64_t ans1 = 0;
    int64_t ans2 = 0;
    std::vector<std::string> v;

    {
        bool first = true;
        for (const auto c: input) {
            if(c == '\n') {
                first = true;
            } else {
                if(first) v.emplace_back();
                v.back().push_back(c);
                first = false;
            }
        }
    }



    std::vector<size_t> emptyrows, emptycols;
    std::string combinedrow(v[0].size(), '.');
    std::vector<std::tuple<size_t,size_t>> points;

    for(size_t r = 0; r < v.size(); r++) {
        bool found = false;
        for(size_t c = 0; c < v[r].size(); c++) {
            if(v[r][c] == '#') {
                found = true;
                combinedrow[c] = '#';
                points.emplace_back(r,c);
            }
        }
        if(!found) emptyrows.push_back(r);
    }

    for(size_t c = 0; c < combinedrow.size(); c++) {
        if(combinedrow[c] != '#') emptycols.push_back(c);
    }

    for(auto p : {1, 2}) {
        for (size_t p1 = 0; p1 < points.size(); p1++) {
            for (size_t p2 = p1 + 1; p2 < points.size(); p2++) {
                auto [r1, c1] = points[p1];
                auto [r2, c2] = points[p2];
                if (r1 > r2) std::swap(r1, r2);
                if (c1 > c2) std::swap(c1, c2);

                auto between = [](size_t i1, size_t i2) {
                    return [i1,i2](size_t i) { return i > i1 && i < i2; };
                };

                auto crossed_rows = std::count_if(emptyrows.begin(), emptyrows.end(), between(r1,r2));
                auto crossed_cols = std::count_if(emptycols.begin(), emptycols.end(), between(c1,c2));

                if(p == 2) {
                    crossed_rows *= (1000000-1);
                    crossed_cols *= (1000000-1);
                }
                (p == 1 ? ans1 : ans2) += (c2 - c1) + crossed_cols + (r2 - r1) + crossed_rows;
            }
        }
    }
    return {std::to_string(ans1), std::to_string(ans2)};
}
