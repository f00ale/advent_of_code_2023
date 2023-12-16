#include "aoc.h"
#include <vector>
#include <algorithm>
#include <iostream>
#include <tuple>
#include <set>
#include <deque>

std::tuple<std::string, std::string> p16(const std::string &input) {
    int64_t ans1 = 0;
    int64_t ans2 = 0;

    std::vector<std::string> v;
    {
        bool first = true;
        for (const auto c: input) {
            if (c == '.' || c == '-' || c == '|' || c == '/' || c == '\\') {
                if(first) v.emplace_back();
                v.back().push_back(c);
                first = false;
            } else if(c == '\n') {
                first = true;
            }
        }

    }

    std::vector<std::tuple<int,int,int,int>> startpoints;

    for(size_t r = 0; r < v.size(); r++) {
        startpoints.emplace_back(r,0,0,1);
        startpoints.emplace_back(r,v[0].size()-1,0,-1);
    }
    for(size_t c = 0; c < v[0].size(); c++) {
        startpoints.emplace_back(0,c,1,0);
        startpoints.emplace_back(v.size()-1,c,-1,0);
    }

    for(const auto & start : startpoints) {
        auto energized = v;
        for (auto &s: energized) for (auto &c: s) c = '.';

        std::set<std::tuple<int, int, int, int>> visited;
        // r,c,dy,dx
        std::deque<std::tuple<int, int, int, int>> q{start};
        while (!q.empty()) {
            auto item = q.front();
            auto [r, c, dy, dx] = item;
            q.pop_front();
            if (r < 0 || r >= static_cast<int>(v.size())) continue;
            if (c < 0 || c >= static_cast<int>(v[0].size())) continue;
            if (visited.find(item) != visited.end()) continue;
            visited.insert(item);
            energized[r][c] = '#';
            switch (v[r][c]) {
                case '.':
                    q.emplace_back(r + dy, c + dx, dy, dx);
                    break;
                case '|':
                    if (dx) {
                        q.emplace_back(r, c, 1, 0);
                        q.emplace_back(r, c, -1, 0);
                    } else {
                        q.emplace_back(r + dy, c + dx, dy, dx);
                    }
                    break;
                case '-':
                    if (dy) {
                        q.emplace_back(r, c, 0, 1);
                        q.emplace_back(r, c, 0, -1);
                    } else {
                        q.emplace_back(r + dy, c + dx, dy, dx);
                    }
                    break;
                case '/':
                    q.emplace_back(r-dx, c-dy, -dx, -dy);
                    break;
                case '\\':
                    q.emplace_back(r+dx, c+dy, dx, dy);
                    break;
            }

        }

        int64_t cnt = 0;
        for (auto &s: energized) for (auto c: s) if (c == '#') cnt++;
        if (cnt > ans2) ans2 = cnt;
        if(start == std::make_tuple(0,0,0,1)) ans1 = cnt;
    }
    return {std::to_string(ans1), std::to_string(ans2)};
}
