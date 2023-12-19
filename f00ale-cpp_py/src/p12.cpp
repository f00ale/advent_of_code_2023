#include "aoc.h"
#include <vector>
#include <algorithm>
#include <iostream>
#include <tuple>
#include <unordered_map>

template<>
struct std::hash<std::tuple<std::string::size_type, size_t>> {
    std::size_t operator()(const std::tuple<std::string::size_type, size_t> &tup) const noexcept {
        std::size_t h1 = std::hash<std::string::size_type>{}(std::get<0>(tup));
        std::size_t h2 = std::hash<size_t>{}(std::get<1>(tup));
        return h1 ^ (h2 << 1);
    }
};

namespace {
std::unordered_map<std::tuple<std::string::size_type, size_t>, int64_t> cache;

int64_t matches(const std::string &s, std::string::size_type pos, std::vector<int>::const_iterator it,
                std::vector<int>::const_iterator end) {
    if (pos == 0) cache.clear();
    int64_t ret = 0;
    auto key = std::make_tuple(pos, std::distance(it, end));
    auto fit = cache.find(key);
    if (fit != cache.end()) return fit->second;
    if (it == end) {
        ret = (s.find('#', pos) == std::string::npos ? 1 : 0);
    } else if (pos >= s.size()) {
        ret = 0;
    } else {
        auto sz = *it;
        pos = s.find_first_of("#?", pos);
        bool ok = pos != std::string::npos;
        for (auto p = pos; ok && p < pos + sz; p++) {
            if (s[p] == '.') ok = false;
        }
        if (ok && s[pos + sz] != '#') ret += matches(s, pos + sz + 1, it + 1, end);
        if (pos < s.size() && s[pos] == '?') {
            ret += matches(s, pos + 1, it, end);
        }
    }
    cache[key] = ret;
    return ret;
}
}

std::tuple<std::string, std::string> p12(const std::string &input) {
    int64_t ans1 = 0;
    int64_t ans2 = 0;

    std::vector<std::tuple<std::string,std::vector<int>>> v;

    {
        int num = 0;
        bool havenum = false;
        std::string conf;
        std::vector<int> nums;
        for (const auto c: input) {
            if (c >= '0' && c <= '9') {
                num *= 10;
                num += c - '0';
                havenum = true;
            } else {
                if(havenum) nums.push_back(num);
                havenum = false;
                num = 0;
                if(c == '.' || c == '#' || c == '?') conf.push_back(c);
                if(c == '\n') {
                    if(!conf.empty() && !nums.empty()) {
                        v.emplace_back(conf, nums);
                    }
                    conf.clear();
                    nums.clear();
                }
            }
        }

    }

    for(const auto & [s,ns] : v) {
        ans1 += matches(s+".", 0, ns.begin(), ns.end());
    }

    for(auto & [s,ns] : v) {
        auto s2 = s;
        auto ns2 = ns;
        for(int i = 0; i< 4; i++) {
            s2 += "?"+s;
            for(auto n:ns) ns2.push_back(n);
        }
        ans2 += matches(s2+".", 0, ns2.begin(), ns2.end());
    }

    return {std::to_string(ans1), std::to_string(ans2)};
}
