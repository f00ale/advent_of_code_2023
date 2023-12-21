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
        //std::cout << i+1 << ' ' << pos.size() << '\n';
    }
    ans1 = pos.size();

    pos.clear();

    auto origsize = v.size();
    auto fulliter = 26501365 / origsize;
    auto rest = 26501365 % origsize;

    startr += 2*origsize;
    startc += 2*origsize;

    pos.emplace(startr,startc);
    // make 5 times larger
    {
        auto tmp = v;
        //first each line times 5
        for(size_t idx = 0; idx < v.size(); idx++) {
            auto & s = v[idx];
            for(int i = 1; i < 5; i++) tmp[idx].append(s);
        }
        auto tmp2 = tmp;
        for(int i = 1; i < 5; i++) {
            for(auto & s : tmp) tmp2.push_back(s);
        }
        v.swap(tmp2);
    }

    std::vector<size_t> coeff;
    for(size_t i = 0; i < rest + 2*origsize; i++) {
        decltype(pos) newp;
        for(auto [r,c] : pos) {
            if(r > 0 && v[r-1][c] == '.') newp.emplace(r-1,c);
            if(r < v.size()-1 && v[r+1][c] == '.') newp.emplace(r+1, c);
            if(c > 0 && v[r][c-1] == '.') newp.emplace(r,c-1);
            if(c < v[0].size()-1 && v[r][c+1] == '.') newp.emplace(r, c+1);
        }
        pos.swap(newp);
        if((i+1) % origsize == rest) {
            coeff.push_back(pos.size());
        }
    }

    ans2 = coeff[0] + (coeff[1]-coeff[0]) * fulliter + (coeff[2]-2*coeff[1]+coeff[0]) * ((fulliter-1)*fulliter)/2;

    return {std::to_string(ans1), std::to_string(ans2)};
}
