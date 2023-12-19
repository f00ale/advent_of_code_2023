#include "aoc.h"
#include <vector>
#include <algorithm>
#include <iostream>
#include <tuple>
#include <set>
#include <map>

namespace {
int64_t recurse(const std::map<std::string, std::vector<std::tuple<char, char, int, std::string>>> & rules,
                const std::string & current,
                int minx = 1, int maxx = 4000, int minm = 1, int maxm = 4000,
                int mina = 1, int maxa = 4000, int mins = 1, int maxs = 4000) {
    int64_t ret = 0;
    if(maxx <= minx || maxm <= minm || maxa <= mina || maxs <= mins) return 0;
    if(current == "R") return ret;
    if(current == "A") {
        ret = 1;
        ret *= (maxx-minx+1);
        ret *= (maxm-minm+1);
        ret *= (maxa-mina+1);
        ret *= (maxs-mins+1);
        return ret;
    }

    auto it = rules.find(current);
    for(auto & [c,g,num,to] : it->second) {
        if(!c) {
            ret += recurse(rules, to, minx,maxx,minm,maxm,mina,maxa,mins,maxs);
            break;
        }
        else {
            if(g == '<') {
                switch(c) {
                    case 'x': ret += recurse(rules, to, minx, std::min(maxx,num-1), minm, maxm, mina, maxa, mins,maxs); minx = std::max(minx,num); break;
                    case 'm': ret += recurse(rules, to, minx, maxx, minm, std::min(maxm,num-1), mina, maxa, mins,maxs); minm = std::max(minm,num); break;
                    case 'a': ret += recurse(rules, to, minx, maxx, minm, maxm, mina, std::min(maxa, num-1), mins,maxs); mina = std::max(mina,num); break;
                    case 's': ret += recurse(rules, to, minx, maxx, minm, maxm, mina, maxa, mins,std::min(maxs, num-1)); mins = std::max(mins,num); break;
                }
            } else { // g == '>'
                switch(c) {
                    case 'x': ret += recurse(rules, to, std::max(minx,num+1), maxx, minm, maxm, mina, maxa, mins,maxs); maxx = std::min(maxx,num); break;
                    case 'm': ret += recurse(rules, to, minx, maxx, std::max(minm,num+1), maxm, mina, maxa, mins,maxs); maxm = std::min(maxm,num); break;
                    case 'a': ret += recurse(rules, to, minx, maxx, minm, maxm, std::max(mina,num+1), maxa, mins,maxs); maxa = std::min(maxa,num); break;
                    case 's': ret += recurse(rules, to, minx, maxx, minm, maxm, mina, maxa, std::max(mins,num+1),maxs); maxs = std::min(maxs,num); break;
                }
            }
        }
    }

    return ret;
}
}

std::tuple<std::string, std::string> p19(const std::string &input) {
    int64_t ans1 = 0;
    int64_t ans2 = 0;

    std::vector<std::tuple<int,int,int,int>> data;
    std::map<std::string, std::vector<std::tuple<char, char, int, std::string>>> rules;

    {
        std::string line;
        for (const auto c: input) {
            if(c == '\n') {
                if(line.empty()) continue;
                if(line[0] == '{') {
                    int num = 0;
                    bool havenum = false;
                    std::vector<int> tmp;
                    for(auto q : line) {
                        if(q >='0' && q <= '9') {
                            num *= 10;
                            num += q-'0';
                            havenum = true;
                        } else {
                            if(havenum) {
                                tmp.push_back(num);
                            }
                            num = 0;
                            havenum = false;
                        }
                    }
                    if(tmp.size() == 4) {
                        data.emplace_back(tmp[0], tmp[1], tmp[2], tmp[3]);
                    }
                } else {
                    auto brace = line.find_first_of('{');
                    std::string name = line.substr(0, brace);
                    auto & v = rules[name];
                    char cc = 0;
                    char gt = 0;
                    std::string target;
                    int num;
                    for(size_t idx = brace; idx < line.size(); idx++) {
                        char q = line[idx];
                        if(q == ',' || q == '}') {
                            v.emplace_back(cc,gt,num,target);
                            cc = 0;
                            gt = 0;
                            num = 0;
                            target.clear();
                        } else if(q == '<' || q == '>') {
                            gt = q;
                        } else if(q >= '0' && q <= '9') {
                            num *= 10;
                            num += q-'0';
                        } else if((q >= 'a' && q <= 'z') || (q>='A' && q <='Z')) {
                            if(line[idx+1] == '<' || line[idx+1] == '>') {
                                cc = q;
                            } else {
                                target.push_back(q);
                            }
                        }
                    }

                }

                line.clear();
            } else {
                line.push_back(c);
            }
        }

    }

    for(const auto & [x,m,a,s] : data) {
        std::string curr = "in";
        while(true) {
            if(curr == "R") break;
            if(curr == "A") {
                ans1 += x+m+a+s;
                break;
            }
            const auto & v = rules[curr];
            for(auto & [c,g,n,to] : v) {
                bool check = true;
                auto checker = [](int val, char gt, int num) {
                    if(gt == '<') return val < num;
                    else return val > num;
                };
                switch(c) {
                    case 0: check = true; break;
                    case 'x': check = checker(x,g,n); break;
                    case 'm': check = checker(m,g,n); break;
                    case 'a': check = checker(a,g,n); break;
                    case 's': check = checker(s,g,n); break;
                }
                if(!check) continue;
                curr = to;
                break;
            }
        }
    }

    ans2 = recurse(rules, "in");

    return {std::to_string(ans1), std::to_string(ans2)};
}
