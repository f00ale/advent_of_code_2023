#include "aoc.h"
#include <vector>
#include <algorithm>
#include <iostream>
#include <tuple>
#include <set>
#include <deque>
#include <limits>
#include <map>
#include <queue>

std::tuple<std::string, std::string> p17(const std::string &input) {
    int64_t ans1 = std::numeric_limits<int64_t>::max();
    int64_t ans2 = ans1;
    std::vector<std::vector<int>> v;
    {

        bool first = true;
        for (const auto c: input) {
            if (c >= '0' && c <= '9') {
                if(first) v.emplace_back();
                v.back().push_back(c-'0');
                first = false;
            } else if(c == '\n'){
                first = true;
            }
        }

    }

    const int d2dy[] = {0, 1, 0, -1};
    const int d2dx[] = {1, 0, -1, 0};

    for(auto p : {1,2}) {
        std::vector<std::vector<std::vector<std::vector<int64_t>>>> costs(v.size(),
                                                                          std::vector<std::vector<std::vector<int64_t>>>(
                                                                                  v[0].size(),
                                                                                  std::vector<std::vector<int64_t>>(4,
                                                                                                                    std::vector<int64_t>(
                                                                                                                            (p==1 ? 4 : 11),
                                                                                                                            std::numeric_limits<int64_t>::max()))));
        std::priority_queue<std::tuple<int64_t, std::tuple<int, int, int, int>>,
                std::vector<std::tuple<int64_t, std::tuple<int, int, int, int>>>,
                std::greater<>> pq;

        costs[0][0][0][0] = 0;
        pq.push({0, {0, 0, 0, 0}});

        auto canmove = [&v](int r, int c) {
            return r >= 0 && r < static_cast<int>(v.size()) && c >= 0 && c < static_cast<int>(v[0].size());
        };

        while (!pq.empty()) {
            const auto [cost, t] = pq.top();
            pq.pop();
            const auto [r, c, d, s] = t;
            if (cost > costs[r][c][d][s]) continue;
            for (auto delta: {0, 1, 3}) {
                int ns = 1;
                if (delta == 0) {
                    ns = s + 1;
                    if (ns > (p == 1 ? 3 : 10)) continue;
                } else if(p == 2 && (s > 0 && s < 4)) continue;

                int nd = (d + delta) % 4;
                int nr = r + d2dy[nd];
                int nc = c + d2dx[nd];
                if (canmove(nr, nc)) {
                    auto added = v[nr][nc];
                    if (costs[nr][nc][nd][ns] > costs[r][c][d][s] + added) {
                        costs[nr][nc][nd][ns] = costs[r][c][d][s] + added;
                        pq.push({costs[nr][nc][nd][ns], {nr, nc, nd, ns}});
                    }
                }
            }
        }

        auto & ans = p == 1 ? ans1 : ans2;
        for (int d = 0; d < 4; d++) {
            for (int s = (p == 1 ? 0 : 4); s < (p == 1 ? 4 : 11); s++) {
                auto tmp = costs[v.size() - 1][v[0].size() - 1][d][s];
                if (tmp < ans) ans = tmp;
            }
        }
    }
    return {std::to_string(ans1), std::to_string(ans2)};
}
// 1301
