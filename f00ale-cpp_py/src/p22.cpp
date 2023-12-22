#include "aoc.h"
#include <vector>
#include <algorithm>
#include <iostream>
#include <tuple>
#include <set>

std::tuple<std::string, std::string> p22(const std::string &input) {
    int64_t ans1 = 0;
    int64_t ans2 = 0;

    std::vector<std::vector<int>> v;

    {
        int num = 0;
        bool havenum = false;
        std::vector<int> tmp;
        for (const auto c: input) {
            if (c >= '0' && c <= '9') {
                num *= 10;
                num += c - '0';
                havenum = true;
            } else {
                if(havenum) tmp.push_back(num);
                havenum = false;
                num = 0;
                if(c == '\n') {
                    if(!tmp.empty()) {
                        v.push_back(tmp);
                        tmp.clear();
                    }
                }
            }
        }

    }

    std::sort(v.begin(), v.end(), [](const auto & v1, const auto & v2) { return v1[2] < v2[2]; });
    int maxx = 0;
    int maxy = 0;
    int maxz = 0;
    for(auto & s : v) {
        maxx = std::max(maxx, s[3]);
        maxy = std::max(maxy, s[4]);
        maxz = std::max(maxz, s[5]);
    }
    for(auto & s : v) if(s[0]>s[3] || s[1] > s[4] || s[2] > s[5]) std::cout << "hmmmm" << '\n';

    std::vector<std::set<int>> supported_by(v.size());
    std::vector<std::set<int>> supports(v.size());

    for(int i = 0; i < static_cast<int>(v.size()); i++) {
        auto x1 = v[i][0];
        auto y1 = v[i][1];
        auto z1 = v[i][2];
        auto x2 = v[i][3];
        auto y2 = v[i][4];
        int highest = 0;
        for(int j = 0; j < i; j++) {
            if (!(x2 < v[j][0] || x1 > v[j][3] || y2 < v[j][1] || y1 > v[j][4])) {
                if (v[j][5] > highest) {
                    highest = v[j][5];
                    supported_by[i] = {j};
                } else if (v[j][5] == highest) {
                    supported_by[i].insert(j);
                }

            }
        }
        int delta = z1 - highest - 1;
        v[i][2] -= delta;
        v[i][5] -= delta;
        for(int j : supported_by[i]) {
            supports[j].insert(i);
        }

    }

    for(int i = 0; i < static_cast<int>(v.size()); i++) {
        bool r = true;
        for(auto supp : supports[i]) {
            r = r && (supported_by[supp].size() > 1);
        }
        if(r) {
            ans1++;
        } else {
            std::set<int> removed {i};
            std::set<int> tocheck = supports[i];

            while(true) {
                int toremove = -1;
                for(int j : tocheck) {
                    bool all_gone = true;
                    for(auto s : supported_by[j]) {
                        all_gone = all_gone and removed.count(s);
                    }
                    if(all_gone) {
                        toremove = j;
                        break;
                    }
                }
                if(toremove >= 0) {
                    tocheck.erase(toremove);
                    removed.insert(toremove);
                    for(auto j : supports[toremove]) {
                        tocheck.insert(j);
                    }
                } else break;
            }

            ans2 += removed.size() - 1;
        }
    }

    return {std::to_string(ans1), std::to_string(ans2)};
}
