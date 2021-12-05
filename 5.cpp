#include "day.hpp"
constexpr int size = 1000;
ret day::part1() {
    int grid[size][size]{};

    for (auto l : input) {
        auto xy = split(l);
        auto a = split<int>(xy[0], ',');
        auto b = split<int>(xy[2], ',');
        int x0 = a[0], y0 = a[1], x1 = b[0], y1 = b[1];

        int dx = std::clamp(x1 - x0, -1, 1), dy = std::clamp(y1 - y0, -1, 1);

        if (dx == 0 || dy == 0) {
            while (x0 != x1 || y0 != y1) {
                grid[x0][y0]++;
                x0 += dx;
                y0 += dy;
            }
            grid[x0][y0]++;
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

        int dx = std::clamp(x1 - x0, -1, 1), dy = std::clamp(y1 - y0, -1, 1);

        while (x0 != x1 || y0 != y1) {
            grid[x0][y0]++;
            x0 += dx;
            y0 += dy;
        }
        grid[x0][y0]++;
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
