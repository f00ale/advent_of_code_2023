#include "aoc.h"
#include <vector>
#include <algorithm>
#include <iostream>
#include <tuple>
#include <set>
#include <map>
#include <limits>

std::tuple<std::string, std::string> p25(const std::string &input) {
    uint64_t ans1 = 0;

    std::map<std::string, std::vector<std::string>> m;
    std::vector<std::set<std::string>> v;
    {
        std::string tmp;
        std::string name;
        for (const auto c: input) {
            if(c >= 'a' && c <= 'z') {
                tmp.push_back(c);
            } else {
                if(!tmp.empty()) {
                    if(name.empty()) {
                        name = tmp;
                        v.emplace_back();
                    }
                    else m[name].push_back(tmp);
                    v.back().insert(tmp);
                }
                tmp.clear();
                if(c == '\n') name.clear();
            }
        }

    }

    auto orig = v;

    std::set<std::string> verts;
    for(auto & vv : v) {
        for(auto & s : vv) verts.insert(s);
    }
    std::map<std::string, int> n2i;
    int cnt=0;
    for(auto & s : verts) n2i[s] = cnt++;

    std::vector<std::vector<int>> weights(verts.size(), std::vector<int>(verts.size(), 0));

    for(auto & [n,nv] : m) {
        for(auto & s : nv) {
            weights[n2i[n]][n2i[s]] = 1;
            weights[n2i[s]][n2i[n]] = 1;
        }
    }

    // from https://en.wikipedia.org/wiki/Stoer%E2%80%93Wagner_algorithm#Example_code
    auto globalmincut = [](std::vector<std::vector<int>> & mat)
    {
            std::pair<int, std::vector<int>> best = {std::numeric_limits<int>::max(), {}};
            int n = mat.size();
            std::vector<std::vector<int>> co(n);

            for (int i = 0; i < n; i++)
                co[i] = {i};

            for (int ph = 1; ph < n; ph++) {
                std::vector<int> w = mat[0];
                size_t s = 0, t = 0;
                for (int it = 0; it < n - ph; it++) { // O(V^2) -> O(E log V) with prio. queue
                    w[t] = std::numeric_limits<int>::min();
                    s = t, t = max_element(w.begin(), w.end()) - w.begin();
                    for (int i = 0; i < n; i++) w[i] += mat[t][i];
                }
                best = min(best, {w[t] - mat[t][t], co[t]});
                co[s].insert(co[s].end(), co[t].begin(), co[t].end());
                for (int i = 0; i < n; i++) mat[s][i] += mat[t][i];
                for (int i = 0; i < n; i++) mat[i][s] = mat[s][i];
                mat[0][t] = std::numeric_limits<int>::min();
            }

            return best;
    };

    auto [num,numv] = globalmincut(weights);

    ans1 = numv.size() * (verts.size()-numv.size());

    return {std::to_string(ans1), "-"};
}
