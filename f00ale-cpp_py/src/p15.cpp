#include "aoc.h"
#include <vector>
#include <algorithm>
#include <iostream>
#include <tuple>
#include <set>

std::tuple<std::string, std::string> p15(const std::string &input) {
    int64_t ans1 = 0;
    int64_t ans2 = 0;
    std::vector<std::string> v;
    {
        std::string curr;
        for (const auto c: input) {
            if ((c >= '0' && c <= '9') || (c >= 'a' && c <= 'z') || c == '=' || c == '-') {
                curr.push_back(c);
            } else {
                if(!curr.empty()) v.push_back(curr);
                curr.clear();
                if(c != ',' && c != '\n') std::cout << "unexpected input " << c << '\n';
            }
        }

    }

    //for(auto & s : v) std::cout << s << '\n';
    auto hash = [](const std::string & s) {
        int64_t ret = 0;
        for(auto c : s) {
            ret += c;
            ret *= 17;
            ret %= 256;
        }
        return ret;
    };
    for(auto & s : v) ans1 += hash(s);

    std::vector<std::vector<std::tuple<std::string, int64_t>>> boxes(256);
    for(auto & s : v) {
        auto pos = s.find_first_of("-=");
        auto lbl = s.substr(0, pos);
        auto boxidx = hash(lbl);
        auto & box = boxes[boxidx];
        if(s[pos] == '-') {
            box.erase(std::remove_if(box.begin(), box.end(), [&lbl](auto && tup){ return lbl == std::get<0>(tup); }), box.end());
        } else {
            auto num = std::stoll(s.substr(pos+1));
            auto it = std::find_if(box.begin(), box.end(), [&lbl](auto & tup) { return lbl == std::get<0>(tup);});
            if(it != box.end()) {
                std::get<1>(*it) = num;
            } else {
                box.emplace_back(lbl, num);
            }
        }
    }
    for(size_t boxid = 0; boxid < boxes.size(); boxid++) {
        for(size_t slot = 0; slot < boxes[boxid].size(); slot++) {
            ans2 += (boxid+1) * (slot+1) * std::get<1>(boxes[boxid][slot]);
        }
    }

    return {std::to_string(ans1), std::to_string(ans2)};
}
