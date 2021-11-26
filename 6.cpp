#include "day.hpp"
ret day::part1() {
    bool grid[1000][1000] = {};
    for (auto l : input) {
        std::vector<int> start, end;
        auto vec = split(l);

        std::function<bool(bool)> op;
        if (vec[0] == "toggle") {
            op = [](bool b) { return !b; };
            start = split<int>(vec[1], ',');
            end = split<int>(vec[3], ',');
        }
        else if (vec[1] == "on") {
            op = [](bool) { return 1; };
            start = split<int>(vec[2], ',');
            end = split<int>(vec[4], ',');
        }
        else if (vec[1] == "off") {
            op = [](bool) { return 0; };
            start = split<int>(vec[2], ',');
            end = split<int>(vec[4], ',');
        }

        int x0 = start[0], x1 = end[0],
            y0 = start[1], y1 = end[1];

        for (auto x = x0; x <= x1; x++)
            for (auto y = y0; y <= y1; y++)
                grid[x][y] = op(grid[x][y]);
    }
    int on = 0;
    for (auto i = 0; i < 1000; i++)
        for (auto j = 0; j < 1000; j++)
            on += grid[i][j] == true;
    return on;
}
ret day::part2() {
    int grid[1000][1000] = {};
    for (auto l : input) {
        std::vector<int> start, end;
        auto vec = split(l);

        std::function<int(int)> op;
        if (vec[0] == "toggle") {
            op = [](int i) { return i+2; };
            start = split<int>(vec[1], ',');
            end = split<int>(vec[3], ',');
        }
        else if (vec[1] == "on") {
            op = [](int i) { return i+1; };
            start = split<int>(vec[2], ',');
            end = split<int>(vec[4], ',');
        }
        else if (vec[1] == "off") {
            op = [](int i) { return i > 0 ? i-1 : 0; };
            start = split<int>(vec[2], ',');
            end = split<int>(vec[4], ',');
        }

        int x0 = start[0], x1 = end[0],
            y0 = start[1], y1 = end[1];

        for (auto x = x0; x <= x1; x++)
            for (auto y = y0; y <= y1; y++)
                grid[x][y] = op(grid[x][y]);
    }
    int on = 0;
    for (auto i = 0; i < 1000; i++)
        for (auto j = 0; j < 1000; j++)
            on += grid[i][j];
    return on;
}
