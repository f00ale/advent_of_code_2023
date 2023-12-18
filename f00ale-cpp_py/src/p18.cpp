#include "aoc.h"
#include <vector>
#include <algorithm>
#include <iostream>
#include <tuple>
#include <set>
#include <deque>

std::tuple<std::string, std::string> p18(const std::string &input) {
    int64_t ans1 = 0;
    int64_t ans2 = 0;
    std::vector<std::tuple<char, int64_t, std::string>> v;
    {
        int num = 0;
        bool havenum = false;
        char dir = 0;
        int ant = 0;
        std::string hex;
        for (const auto c: input) {
            if (!ant && c >= '0' && c <= '9') {
                num *= 10;
                num += c - '0';
                havenum = true;
            } else if (ant && ((c >= '0' && c <= '9') || (c >= 'a' && c <= 'f'))) {
                hex.push_back(c);
            } else if (c == 'U' || c == 'D' || c == 'R' || c == 'L') {
                dir = c;
            }
            else {
                if(havenum && !ant) ant = num;
                if(c == ')') {
                    v.emplace_back(dir, ant, hex);
                    ant = 0;
                    hex.clear();
                }
                havenum = false;
                num = 0;
            }
        }

    }

    for(auto p : {1,2}) {
        int64_t x = 0, y = 0;

        std::vector<std::tuple<int64_t, int64_t>> verts{{0, 0}};
        int64_t tot = 0;
        for (auto [d, ant, col]: v) {
            if(p == 2) {
                ant = stoll(col.substr(0,5), nullptr, 16);
                switch(col[5]) {
                    case '0': d = 'R'; break;
                    case '1': d = 'D'; break;
                    case '2': d = 'L'; break;
                    case '3': d = 'U'; break;
                }
            }

            switch (d) {
                case 'R':
                    x += ant;
                    break;
                case 'L':
                    x -= ant;
                    break;
                case 'D':
                    y += ant;
                    break;
                case 'U':
                    y -= ant;
                    break;
            }
            tot += ant;
            verts.emplace_back(x, y);
        }

        int64_t tmp = 0;
        for (size_t i = 0; i < verts.size() - 1; i++) {
            auto [x1, y1] = verts[i];
            auto [x2, y2] = verts[i + 1];
            tmp += (x1 * y2) - (y1 * x2);
        }
        (p == 1 ? ans1 : ans2) = (tmp + tot) / 2 + 1;
    }
    return {std::to_string(ans1), std::to_string(ans2)};
}
