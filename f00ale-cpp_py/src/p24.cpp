#include "aoc.h"
#include <vector>
#include <algorithm>
#include <iostream>
#include <tuple>
#include <set>
#include <optional>
std::tuple<std::string, std::string> p24(const std::string &input) {
    int64_t ans1 = 0;
    int64_t ans2 = 0;
    std::vector<std::tuple<int64_t,int64_t,int64_t,int64_t,int64_t,int64_t>> v;
    {
        int64_t num = 0;
        bool havenum = false;
        std::vector<int64_t> tmp;
        bool neg = false;
        for (const auto c: input) {
            if (c >= '0' && c <= '9') {
                num *= 10;
                num += c - '0';
                havenum = true;
            } else if(c == '-') {
                neg = true;
            } else {
                if(havenum) {
                    if (neg) num = -num;
                    tmp.push_back(num);
                }
                havenum = false;
                num = 0;
                neg = false;
                if(c == '\n') {
                    if(tmp.size() == 6) {
                        v.emplace_back(tmp[0], tmp[1], tmp[2], tmp[3], tmp[4], tmp[5]);
                    }
                    tmp.clear();
                }
            }
        }

    }

    const double minx = 200000000000000., maxx = 400000000000000.;
    const double miny = 200000000000000., maxy = 400000000000000.;

    static constexpr double EPSILON = 0.000001;

    auto intersect = [](double x1, double x2, double x3, double x4, double y1, double y2, double y3, double y4)
            -> std::optional<std::tuple<double,double>> {
        double div = (x1-x2)*(y3-y4) - (y1-y2)*(x3-x4);
        if(div < EPSILON && div > -EPSILON) return {};

        double x = (x1*y2 - y1*x2)*(x3-x4) - (x1-x2)*(x3*y4 - y3*x4);
        double y = (x1*y2 - y1*x2)*(y3-y4) - (y1-y2)*(x3*y4 - y3*x4);

        return std::make_tuple(x/div, y/div);
    };

    for(size_t i = 0; i < v.size(); i++) {
        auto [px1, py1, pz1, dx1, dy1, dz1] = v[i];
        for (size_t j = i + 1; j < v.size(); j++) {
            auto [px2, py2, pz2, dx2, dy2, dz2] = v[j];

            auto opt = intersect(px1, px1+dx1, px2, px2+dx2,
                                 py1, py1+dy1, py2, py2+dy2);

            if(opt) {
                auto [px,py] = *opt;
                auto t1 = (px - px1) / dx1;
                auto t2 = (px - px2) / dx2;
                if(t1 >= 0 && t2 >= 0) {
                    if(minx <= px && px <= maxx && miny <= py && py <= maxy) {
                        ans1++;
                    }
                }
            }

        }
    }


    return {std::to_string(ans1), std::to_string(ans2)};
}
