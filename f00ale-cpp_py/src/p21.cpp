#include "aoc.h"
#include <vector>
#include <algorithm>
#include <iostream>
#include <tuple>
#include <set>
#include <map>

std::tuple<std::string, std::string> p21(const std::string &input) {
    int64_t ans1 = 0;
    int64_t ans2 = 0;

    std::vector<std::string> v;
    size_t startr = 0, startc = 0;
    {
        bool first = true;
        size_t row = 0, col = 0;
        for (auto c: input) {
            if (c == '.' || c == '#' || c == 'S') {
                if(c == 'S') {
                    startr = row;
                    startc = col;
                    c = '.';
                }
                if(first) {
                    v.emplace_back();
                    first = false;
                }
                v.back().push_back(c);
                col++;
            } else if(c == '\n') {
                if(!first) row++;
                first = true;
                col = 0;
            }
        }

    }

    for(auto & s : v) std::cout << s << '\n';
    std::cout << startr << ' ' << startc << '\n';

    std::set<std::tuple<size_t, size_t>> pos{{startr,startc}};
    for(int i = 0; i < 64; i++) {
        decltype(pos) newp;
        for(auto [r,c] : pos) {
            if(r > 0 && v[r-1][c] == '.') newp.emplace(r-1,c);
            if(r < v.size()-1 && v[r+1][c] == '.') newp.emplace(r+1, c);
            if(c > 0 && v[r][c-1] == '.') newp.emplace(r,c-1);
            if(c < v[0].size()-1 && v[r][c+1] == '.') newp.emplace(r, c+1);
        }
        pos.swap(newp);
        std::cout << i+1 << ' ' << pos.size() << '\n';
    }
    ans1 = pos.size();
/*
    std::set<std::tuple<int64_t, int64_t>> pos2{{startr,startc}};
    std::cout << v.size() << ' ' << v[0].size() << '\n';
    int64_t last = 0;
    for(int i = 0; i < 100; i++) {
        decltype(pos2) newp;
        for(auto [r,c] : pos2) {
            auto rm = r;
            while(rm < 0) rm += v.size();
            rm %= v.size();
            auto rm1 = rm - 1;
            if(rm1 < 0) rm1 += v.size();
            auto rp1 = (rm+1)%v.size();
            auto cm = c;
            while(cm < 0) cm += v[0].size();
            cm %= v[0].size();
            auto cm1 = cm - 1;
            if(cm1 < 0) cm1 += v[0].size();
            auto cp1 = (cm+1)%v[0].size();

            if(v[rm1][cm] == '.') newp.emplace(r-1,c);
            if(v[rp1][cm] == '.') newp.emplace(r+1,c);
            if(v[rm][cm1] == '.') newp.emplace(r,c-1);
            if(v[rm][cp1] == '.') newp.emplace(r,c+1);
        }

        pos2.swap(newp);
        if(true || i+1 == 6 || i+1 == 10 || i+1 == 50) {
            std::cout << i+1 << ' ' << pos2.size() << ' ' << pos2.size()-last << '\n';
            last = pos2.size();
        }
    }
    */
/*
    std::vector<std::vector<size_t>> scores(v.size(), std::vector<size_t>(v[0].size()));
    scores[startr][startc] = 1;
    for(int i = 0; i < 50; i++) {
        std::vector<std::vector<size_t>> news(v.size(), std::vector<size_t>(v[0].size()));

        for(size_t r = 0; r < scores.size(); r++) {
            for(size_t c = 0; c < scores[0].size(); c++) {
                if(scores[r][c]) {
                    auto rp1 = (r+1) % v.size();
                    auto cp1 = (c+1) % v[0].size();
                    auto rm1 = (r==0 ? v.size()-1 : r-1);
                    auto cm1 = (c==0 ? v[0].size()-1 : c-1);
                    if(v[r][cm1] == '.') news[r][cm1] = news[r][cm1] ? news[r][cm1]+1 : scores[r][c];
                    if(v[r][cp1] == '.') news[r][cp1] = news[r][cm1] ? news[r][cp1]+1 : scores[r][c];
                    if(v[rm1][c] == '.') news[rm1][c] = news[r][cm1] ? news[rm1][c]+1 : scores[r][c];
                    if(v[rp1][c] == '.') news[rp1][c] = news[r][cm1] ? news[rp1][c]+1 : scores[r][c];
                }
            }
        }
        scores.swap(news);

        if(true || i+1 == 6 || i+1 == 10 || i+1 == 50) {
            int64_t cnt = 0;
            for(auto & s : scores) for(auto c : s) cnt+=c;
            std::cout << i+1 << ' ' << cnt << ' ' << cnt-last << '\n';
            last = cnt;
        }

    }
*/

/*
    std::map<std::tuple<size_t, size_t>, size_t> posm;
    posm[std::make_tuple(startr, startc)] = 1;


    for(int i = 0; i < 50; i++) {
        decltype(posm) newp;
        for(auto [t, cnt] : posm) {
            auto [r,c] = t;
            if(r > 0 && v[r-1][c] == '.') newp[{r-1,c}] = 1;
            if(r < v.size()-1 && v[r+1][c] == '.') newp[{r+1, c}] = 1;
            if(c > 0 && v[r][c-1] == '.') newp[{r,c-1}] = 1;
            if(c < v[0].size()-1 && v[r][c+1] == '.') newp[{r, c+1}] = 1;
        }
        posm.swap(newp);

        if(i+1 == 6 || i+1 == 10 || i+1 == 50) {
            size_t cnt = 0;
            for(auto & [t,c] : posm) cnt += c;
            std::cout << i+1 << ' ' << cnt << '\n';
        }
    }
    ans1 = pos.size();
*/

    return {std::to_string(ans1), std::to_string(ans2)};
}
