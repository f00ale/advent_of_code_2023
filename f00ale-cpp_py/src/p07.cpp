#include "aoc.h"
#include <vector>
#include <algorithm>
#include <iostream>
#include <tuple>
#include <set>

std::tuple<std::string, std::string> p07(const std::string &input) {
    int64_t ans1 = 0;
    int64_t ans2 = 0;
    std::vector<std::tuple<std::string, int64_t>> v;
    {
        int num = 0;
        bool havenum = false;
        bool first = true;
        std::string tmp;
        for (const auto c: input) {
            if (!first && c >= '0' && c <= '9') {
                num *= 10;
                num += c - '0';
                havenum = true;
            } else {
                if((c >= '0' && c <= '9') || c == 'A' || c == 'K' || c == 'Q' || c == 'J' || c == 'T') tmp.push_back(c);
                if (c == '\n') {
                    if (havenum) {
                        v.emplace_back(tmp, num);
                    }
                    first = true;
                    tmp.clear();
                }
                if (c == ' ') {
                    first = false;
                }
                havenum = false;
                num = 0;
            }
        }

    }

    auto cardrank = [](char c) {
        switch(c) {
            case 'A': return 14;
            case 'K': return 13;
            case 'Q': return 12;
            case 'J': return 11;
            case 'T': return 10;
            default: return c-'0';
        }
    };
    auto handrank = [](const std::string & s) {
        auto tmp = s;
        std::sort(tmp.begin(), tmp.end());
        int maxsame = 0;
        auto cpy = tmp;
        cpy.erase(std::unique(cpy.begin(), cpy.end()), cpy.end());
        // len 1 = 5 kind, 2 = 4 kind or full house, 3 = triss/2pair, 4 1 pair, 5 highcard

        switch(cpy.size()) {
            case 1: return 7;
            case 2: {
                if(tmp[0]==tmp[1] && tmp[3]==tmp[4]) return 5; // full house
                else return 6; // 4 kiind
            }
            case 3: {
                if((tmp[0] == tmp[1] && tmp[1] == tmp[2]) || (tmp[1] == tmp[2] && tmp[2] == tmp[3]) || (tmp[2] == tmp[3] && tmp[3] == tmp[4])) return 4;
                else return 3;
            }
            case 4: return 2;
            case 5: return 1;
        }
    };

    auto cardrank2 = [](char c) {
        switch(c) {
            case 'A': return 14;
            case 'K': return 13;
            case 'Q': return 12;
            case 'J': return 1;
            case 'T': return 10;
            default: return c-'0';
        }
    };
    auto handrank2 = [&handrank](const std::string & s) {
        int maxret = 0;
        auto t1 = s;
        std::sort(t1.begin(), t1.end());
        t1.erase(std::unique(t1.begin(),t1.end()), t1.end());
        if(t1.find('J') == std::string::npos) return handrank(s);
        if(t1.size() == 1) return 7;
        for(auto r : t1) {
            if(r == 'J') continue;
            int ret = 0;
            auto tmp = s;
            for(auto & x : tmp) if(x == 'J') x = r;
            std::sort(tmp.begin(), tmp.end());
            int maxsame = 0;
            auto cpy = tmp;
            cpy.erase(std::unique(cpy.begin(), cpy.end()), cpy.end());
            // len 1 = 5 kind, 2 = 4 kind or full house, 3 = triss/2pair, 4 1 pair, 5 highcard

            switch (cpy.size()) {
                case 1:
                    ret =  7; break;
                case 2: {
                    if (tmp[0] == tmp[1] && tmp[3] == tmp[4]) ret = 5; // full house
                    else ret = 6; // 4 kiind
                } break;
                case 3: {
                    if ((tmp[0] == tmp[1] && tmp[1] == tmp[2]) || (tmp[1] == tmp[2] && tmp[2] == tmp[3]) ||
                        (tmp[2] == tmp[3] && tmp[3] == tmp[4]))
                        ret =  4;
                    else  ret = 3;
                } break;
                case 4:
                    ret= 2; break;
                case 5:
                    ret = 1; break;
            }
            if (ret > maxret) maxret = ret;
        }
        return maxret;
    };

    std::sort(v.begin(), v.end(), [&cardrank,&handrank](auto && t1, auto && t2) {
        auto & h1 = std::get<0>(t1);
        auto & h2 = std::get<0>(t2);
        auto hr1 = handrank(h1);
        auto hr2 = handrank(h2);
        if(hr1 != hr2) return hr1<hr2;
        for(int i = 0; i < 5; i++) {
            if(h1[i] != h2[i]) return cardrank(h1[i]) < cardrank(h2[i]);
        }
        return false;
    });

    for(decltype(v)::size_type i = 0; i < v.size(); i++) {
        auto & [h, b] = v[i];
        ans1 += b*(i+1);
    }

    std::sort(v.begin(), v.end(), [&cardrank2,&handrank2](auto && t1, auto && t2) {
        auto & h1 = std::get<0>(t1);
        auto & h2 = std::get<0>(t2);
        auto hr1 = handrank2(h1);
        auto hr2 = handrank2(h2);
        if(hr1 != hr2) return hr1<hr2;
        for(int i = 0; i < 5; i++) {
            if(h1[i] != h2[i]) return cardrank2(h1[i]) < cardrank2(h2[i]);
        }
        return false;
    });

    for(decltype(v)::size_type i = 0; i < v.size(); i++) {
        auto & [h, b] = v[i];
        ans2 += b*(i+1);
    }


    return {std::to_string(ans1), std::to_string(ans2)};
}
