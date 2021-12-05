#include "day.hpp"
constexpr int size = 1000;
ret day::part1() {
    int grid[size][size]{};

    for (auto l : input) {
        auto xy = split(l);
        auto a = split<int>(xy[0], ',');
        auto b = split<int>(xy[2], ',');
        int x0 = a[0], y0 = a[1], x1 = b[0], y1 = b[1];

        if (x0 == x1) {
            auto [from, to] = std::minmax(y0, y1);
            for (auto i = from; i <= to; i++)
                grid[x0][i]++;
        } else if (y0 == y1) {
            auto [from, to] = std::minmax(x0, x1);
            for (auto i = from; i <= to; i++)
                grid[i][y0]++;
        }
    }

    int count = 0;
    for (auto i = 0; i < size; i++) {
        for (auto j = 0; j < size; j++) {
            if (grid[i][j] >= 2)
                count++;
        }
    }

    return count;
}
ret day::part2() {
    int grid[size][size]{};

    for (auto l : input) {
        auto xy = split(l);
        auto a = split<int>(xy[0], ',');
        auto b = split<int>(xy[2], ',');
        int x0 = a[0], y0 = a[1], x1 = b[0], y1 = b[1];

        if (x0 == x1) {
            auto [from, to] = std::minmax(y0, y1);
            for (auto i = from; i <= to; i++)
                grid[x0][i]++;
        } else if (y0 == y1) {
            auto [from, to] = std::minmax(x0, x1);
            for (auto i = from; i <= to; i++)
                grid[i][y0]++;
        } else if (std::abs(x0 - x1) == std::abs(y0 - y1)) {
            // always go left to right
            if (x0 > x1) {
                std::swap(x0, x1);
                std::swap(y0, y1);
            }

            for (; x0 <= x1; x0++) {
                grid[x0][y0]++;
                y0 += y0 <= y1 ? 1 : -1;
            }
        }
    }

    int count = 0;
    for (auto i = 0; i < size; i++) {
        for (auto j = 0; j < size; j++) {
            if (grid[i][j] >= 2)
                count++;
        }
    }

    return count;
}
