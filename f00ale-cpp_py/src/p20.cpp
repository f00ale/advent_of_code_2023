#include "aoc.h"
#include <vector>
#include <algorithm>
#include <iostream>
#include <tuple>
#include <set>
#include <map>
#include <deque>

std::tuple<std::string, std::string> p20(const std::string &input) {
    int64_t ans1 = 0;
    int64_t ans2 = 0;

    std::map<std::string, std::tuple<char, std::vector<std::string>>> m;

    {
        std::string name;
        std::vector<std::string> vec;
        std::string tmp;
        for (const auto c: input) {
            if(c == '%' || c == '&' || (c>='a' && c <='z')) {
                tmp.push_back(c);
            } else {
                if(!tmp.empty()) {
                    if(name.empty()) name = tmp;
                    else vec.push_back(tmp);
                    tmp.clear();
                }
                if(c == '\n') {
                    if(name.empty()) continue;
                    char x = name[0];
                    if(x == '%' || x == '&') {
                        name = name.substr(1);
                    } else {
                        x = 0;
                    }
                    m[name] = std::make_tuple(x, vec);
                    name.clear();
                    vec.clear();
                }
            }
        }
    }

    std::map<std::string,bool> flipflops;
    std::map<std::string,std::map<std::string,bool>> conjunctions;

    for(auto & [n,t] : m) {
        auto & [c, v] = t;
        if(c == '%') flipflops[n] = false;
        if(c == '&') conjunctions[n] = {};
    }

    for(auto & [n,t] : m) {
        auto & [c, v] = t;
        for(auto & o : v) {
            auto it = conjunctions.find(o);
            if(it != conjunctions.end()) {
                it->second[n] = false;
            }
        }
    }

    int64_t lows = 0;
    int64_t highs = 0;
    std::string wanted;
    // find single thing outputing to rx
    for(auto & [n,t] : m)
    {
        auto & [x,outputs] = t;
        if(std::find(outputs.begin(),outputs.end(), "rx") != outputs.end()) {
            wanted = n;
            break;
        }
    }
    // find things outputing to wanted
    std::map<std::string, int64_t> factors;
    for(auto & [n,t] : m)
    {
        auto & [x,outputs] = t;
        if(std::find(outputs.begin(),outputs.end(), wanted) != outputs.end()) {
            factors[n] = 0;
        }
    }

    for(int64_t i = 0; ; i++) {
        if(i == 1000) ans1 = lows*highs;
        if(ans1 && ans2) break;
        std::deque<std::tuple<std::string, std::string, bool>> q;
        lows++;
        q.emplace_back("broadcaster", "button", false);
        while (!q.empty()) {
            auto [n, from, b] = q.front();
            if(n == wanted && b) {
                if(!factors[from]) {
                    factors[from] = i+1;
                }
                ans2 = 1;
                for(auto & [x,f] : factors) ans2 *= f;
            }
            q.pop_front();
            auto &[type, outputs] = m[n];
            if (!type) {
                for (auto &o: outputs) {
                    //std::cout << n << ' ' << b << " -> " << o << '\n';
                    if (b) highs++; else lows++;
                    q.emplace_back(o, n, b);
                }
            } else if (type == '%') { // flipflop
                if (b) {
//                std::cout << n << " got high, ignore\n";
                    continue;
                }
                auto it = flipflops.find(n);
                if (it == flipflops.end()) std::cout << "flipflop " << n << "not found!!!\n";
                it->second = !it->second;
                auto nb = it->second;
                for (auto &o: outputs) {
                    //std::cout << n << ' ' << nb << " -> " << o << '\n';
                    if (nb) highs++; else lows++;
                    q.emplace_back(o, n, nb);
                }
            } else if (type == '&') {
                auto &conj = conjunctions[n];
                auto it = conj.find(from);
                if (it == conj.end()) std::cout << "conj " << from << " for " << n << " not found\n";
                it->second = b;

                bool allhigh = true;
                for (auto [_, l]: conj) {
                    allhigh = l && allhigh;
                }
                auto nb = !allhigh;
                for (auto &o: outputs) {
                    //std::cout << n << ' ' << nb << " -> " << o << '\n';
                    if (nb) highs++; else lows++;
                    q.emplace_back(o, n, nb);
                }
            }
        }
    }

    return {std::to_string(ans1), std::to_string(ans2)};
}
