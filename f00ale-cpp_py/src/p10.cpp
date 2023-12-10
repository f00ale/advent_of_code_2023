#include "aoc.h"
#include <vector>
#include <algorithm>
#include <iostream>
#include <tuple>
#include <set>
#include <deque>

std::tuple<std::string, std::string> p10(const std::string &input) {
    int64_t ans1 = 0;
    int64_t ans2 = 0;
    std::vector<std::string> v{""};
    {
        bool first = true;
        for (const auto c: input) {
            if (c == '\n') {
                if(!first) v.back().push_back('.');
                first = true;
            } else {
                if(first) v.emplace_back(".");
                first = false;
                v.back().push_back(c);
            }
        }

    }

    v[0] = std::string(v[1].size(), '.');
    v.emplace_back(v[1].size(), '.');

    size_t posr = 0, posc = 0;

    for(size_t r = 0; r < v.size(); r++) {
        auto c = v[r].find('S');
        if(c != std::string::npos) {
            posr = r;
            posc = c;
            break;
        }
    }
    std::cout << posr << ' ' << posc << '\n';



    std::vector<std::tuple<size_t, size_t>> poss;
    poss.emplace_back(posr, posc);

    auto wr = [](char c) { return c == '-' || c == 'J' || c == '7' || c == 'S'; };
    auto wl = [](char c) { return c == '-' || c == 'F' || c == 'L' || c == 'S'; };
    auto wu = [](char c) { return c == '|' || c == 'F' || c == '7' || c == 'S'; };
    auto wd = [](char c) { return c == '|' || c == 'L' || c == 'J' || c == 'S'; };
    auto w = v;
    while(!poss.empty()) {
        decltype(poss) newp;
        for(auto [r,c] : poss) {
            if((w[r][c] == 'S' || wu(w[r][c])) && wd(v[r+1][c])) { v[r+1][c] = 'x'; newp.emplace_back(r+1, c); }
            if((w[r][c] == 'S' || wd(w[r][c])) && wu(v[r-1][c])) { v[r-1][c] = 'x'; newp.emplace_back(r-1, c); }
            if((w[r][c] == 'S' || wr(w[r][c])) && wl(v[r][c-1])) { v[r][c-1] = 'x'; newp.emplace_back(r, c-1); }
            if((w[r][c] == 'S' || wl(w[r][c])) && wr(v[r][c+1])) { v[r][c+1] = 'x'; newp.emplace_back(r, c+1); }
        }
        if(!newp.empty()) ans1++;
        poss.swap(newp);
    }
    v[posr][posc] = 'x';

    decltype(v) v2;
    for(size_t r = 0; r < v.size(); r++) {
        for(size_t c = 0; c < v[r].size(); c++) {
            if(v[r][c] != 'x') w[r][c] = '.';
        }
    }

    for(size_t r = 0; r < v.size()-1; r++) {
        v2.emplace_back(v[r].size()*2-1, '.');
        for(size_t c = 0; c < v[r].size()-1;c++) {
            v2.back()[c*2] = w[r][c];
            v2.back()[c*2 + 1 ] = (wl(w[r][c]) && wr(w[r][c+1])) ? '-' : '.';
        }
        v2.emplace_back(v[r].size()*2-1, '.');
        for(size_t c = 0; c < v[r].size(); c++) {
            v2.back()[c*2] = (wu(w[r][c]) && wd(w[r+1][c])) ? '|' : '.';
        }
    }

    std::deque<std::tuple<size_t, size_t>> q;
    q.emplace_back(0,0);
    while(!q.empty()) {
        auto [r,c] = q.front();
        q.pop_front();
        if(v2[r][c] != '.') continue;
        v2[r][c] = 'O';
        if(r > 0) q.emplace_back(r-1,c);
        if(r < v2.size() - 1) q.emplace_back(r+1, c);
        if(c > 0) q.emplace_back(r,c-1);
        if(c < v2[r].size() - 1) q.emplace_back(r, c+1);
    }

    for(size_t r = 0; r < v2.size(); r+=2) {
        for(size_t c = 0; c < v2[r].size(); c+=2) {
            if(v2[r][c] == '.') ans2++;
        }
    }

    return {std::to_string(ans1), std::to_string(ans2)};
}
