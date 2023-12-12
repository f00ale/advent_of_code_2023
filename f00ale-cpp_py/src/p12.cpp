#include "aoc.h"
#include <vector>
#include <algorithm>
#include <iostream>
#include <tuple>
#include <set>

bool canwork(const std::string & s, const std::vector<int> & ns, int tot, bool final = false) {
    // check up until first ?
    auto poss = std::count_if(s.begin(), s.end(), [](char c){return c == '#' || c == '?';});
    if(poss < tot) return false;
    auto firstq = s.find('?');
    bool complete = firstq == std::string::npos;
    auto sub = s.substr(0, firstq);
    std::vector<int> tmp;
    auto pos = sub.find('#', 0);
    while(pos < sub.size()) {
        int l = 0;
        while(sub[pos] == '#' && pos < sub.size()) l++, pos++;
        tmp.push_back(l);
        pos = sub.find('#', pos);
        if(tmp.size()>ns.size()) break;
    }

    if(tmp.size() > ns.size()) {
        //std::cout << "XXXX\n";
        return false;
    }
    if(!final) {
    if(!complete && !tmp.empty()) tmp.pop_back();
    for(size_t i = 0; i < tmp.size(); i++) {
        if(tmp[i] != ns[i]) return false;
    }
    }else {
        return tmp == ns;
    }
//    if(complete) std::cout << s << '\n';
    return true;
}

int64_t recurse(const std::string & ins, const std::vector<int> & ns, int tot) {
    auto q = ins.find('?');
    if(q == std::string::npos) return canwork(ins, ns, tot,true) ? 1 : 0;
    auto s = ins;

    int64_t ret = 0;
    s[q] = '.';
    if(canwork(s,ns, tot)) ret += recurse(s, ns, tot);
    s[q] = '#';
    if(canwork(s,ns,tot)) ret += recurse(s, ns, tot);
    return ret;
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

    for(auto & [s,ns] : v) {
        int tot = 0;
        for(auto n : ns) tot += n;
        std::cout << s;
        for(auto n : ns) std::cout << ' ' << n;
        std::cout << '\n';
        auto x = recurse(s, ns, tot);
        std::cout << x << '\n';
        ans1 += x;
    }
    for(auto & [s,ns] : v) {

        auto s2 = s+"?"+s+"?"+s+"?"+s+"?"+s;
        auto ns2 = ns;
        for(int i = 0; i< 4; i++) {
            for(auto n:ns) ns2.push_back(n);
        }
        int tot = 0;
        for(auto n : ns2) tot += n;
        std::cout << s2.length() << ' ' << tot << ' ' << ns2.size() << '\n';
        //        auto x = recurse(s2, ns2, tot);
//        std::cout << x << '\n';
//        ans2 += x;

    }

    return {std::to_string(ans1), std::to_string(ans2)};
}
