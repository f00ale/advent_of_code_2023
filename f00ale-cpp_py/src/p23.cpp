#include "aoc.h"
#include <vector>
#include <algorithm>
#include <iostream>
#include <tuple>
#include <set>
#include <deque>
namespace {
int64_t maxfound = 0;

int64_t recurse(size_t row, size_t col, int64_t steps, std::vector<std::string> v) {
    auto rowin = row;
    auto colin = col;

    while(true) {
        if(row == v.size()-1) {
            maxfound = std::max(steps, maxfound);
            //std::cout << "found goal " << steps << ' ' << maxfound << '\n';
            return steps;
        }

        int poss = 0;
        if (row > 0 && (v[row - 1][col] == '.' || v[row - 1][col] == '^')) poss++;
        if (row < v.size() - 1 && (v[row + 1][col] == '.' || v[row + 1][col] == 'v')) poss++;
        if (v[row][col - 1] == '.' || v[row][col - 1] == '<') poss++;
        if (v[row][col + 1] == '.' || v[row][col + 1] == '>') poss++;
        v[row][col] = 'O';
        if(poss == 0) {
            return 0;
        } else if (poss == 1) {
            if (row > 0 && (v[row - 1][col] == '.' || v[row - 1][col] == '^')) row--;
            else if (row < v.size() - 1 && (v[row + 1][col] == '.' || v[row + 1][col] == 'v')) row++;
            else if (v[row][col - 1] == '.' || v[row][col - 1] == '<') col--;
            else if (v[row][col + 1] == '.' || v[row][col + 1] == '>') col++;
            steps++;
        } else {
            int64_t tmp = 0;
            if (row > 0 && (v[row - 1][col] == '.' || v[row - 1][col] == '^')) {
                tmp = std::max(tmp, recurse(row-1, col, steps+1, v));
            }
            if (row < v.size() - 1 && (v[row + 1][col] == '.' || v[row + 1][col] == 'v')) {
                tmp = std::max(tmp, recurse(row+1, col, steps+1, v));
            }
            if (v[row][col - 1] == '.' || v[row][col - 1] == '<') {
                tmp = std::max(tmp, recurse(row, col-1, steps+1, v));
            }
            if (v[row][col + 1] == '.' || v[row][col + 1] == '>') {
                tmp = std::max(tmp, recurse(row, col+1, steps+1, v));
            }
            return tmp;
        }

    }
}

}
std::tuple<std::string, std::string> p23(const std::string &input) {
    int64_t ans1 = 0;
    int64_t ans2 = 0;

    std::vector<std::string> v;

    {
        bool first = true;
        for (const auto c: input) {
            if (c == '\n') {
                first = true;
            } else {
                if(first) v.emplace_back();
                first = false;
                v.back().push_back(c);
            }
        }

    }

    ans1 = recurse(0,1,0,v);
    for(auto & s : v) for(auto & c : s) {
        if(c == '>' || c == 'v' || c == '<' || c == '^') c = '.';
    }
    ans2 = recurse(0,1,0,v);

    return {std::to_string(ans1), std::to_string(ans2)};
}
