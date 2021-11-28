#include "day.hpp"

#define size 100
#define iterations 100

namespace {
int life(std::vector<std::string> input, const std::vector<std::pair<int,int>>& stuck) {
    bool grid[size+2][size+2] = { };
    int sums[size+2][size+2] = { };
    for (auto i = 1; i < size+1; i++) {
        auto line = input[i-1];
        for (auto j = 1; j < size+1; j++)
            grid[i][j] = line[j-1] == '#';
    }

    for (auto count = 0; count < iterations; count++) {
        for (auto [i, j] : stuck) {
            grid[i+1][j+1] = true;
        }

        for (auto i = 1; i < size+1; i++) {
            for (auto j = 1; j < size+1; j++) {
                sums[i][j] = grid[i-1][j-1] + grid[i-1][j] + grid[i-1][j+1]
                           + grid[i  ][j-1]                + grid[i  ][j+1]
                           + grid[i+1][j-1] + grid[i+1][j] + grid[i+1][j+1];
            }
        }

        for (auto i = 1; i < size+1; i++) {
            for (auto j = 1; j < size+1; j++) {
                if (grid[i][j]) {
                    if (!(sums[i][j] == 2 || sums[i][j] == 3))
                        grid[i][j] = false;
                }
                else {
                    if (sums[i][j] == 3)
                        grid[i][j] = true;
                }
            }
        }
    }
    for (auto [i, j] : stuck) {
        grid[i+1][j+1] = true;
    }

    auto total = 0;
    for (auto i = 1; i < size+1; i++)
        for (auto j = 1; j < size+1; j++)
            total += grid[i][j];

    return total;
}
}

ret day::part1() { return life(input, {}); }
ret day::part2() { return life(input, {{0,0}, {0,size-1}, {size-1,0}, {size-1,size-1}}); }
