#include "day.hpp"
namespace {
struct instr {
    enum { toggle, on, off } op;
    int x0, x1, y0, y1;
    instr(const std::string &s) {
        std::vector<int> start, end;
        auto vec = split(s);
        if (vec[0] == "toggle") {
            op = toggle;
            start = split<int>(vec[1], ',');
            end = split<int>(vec[3], ',');
        }
        else {
            op = vec[1] == "on" ? on : off;
            start = split<int>(vec[2], ',');
            end = split<int>(vec[4], ',');
        }
        x0 = start[0];
        x1 = end[0];
        y0 = start[1];
        y1 = end[1];
    }
};
}

ret day::part1() {
    bool grid[1000][1000] = {};
    for (auto l : input) {
        instr i{l};

        for (auto x = i.x0; x <= i.x1; x++) {
            for (auto y = i.y0; y <= i.y1; y++) {
                switch (i.op) {
                    case instr::on:     grid[x][y] = 1;           break;
                    case instr::off:    grid[x][y] = 0;           break;
                    case instr::toggle: grid[x][y] = !grid[x][y]; break;
                }
            }
        }
    }

    int total = 0;
    for (auto i = 0; i < 1000; i++)
        for (auto j = 0; j < 1000; j++)
            total += grid[i][j] == true;
    return total;
}
ret day::part2() {
    int grid[1000][1000] = {};
    for (auto l : input) {
        instr i{l};

        for (auto x = i.x0; x <= i.x1; x++) {
            for (auto y = i.y0; y <= i.y1; y++) {
                switch (i.op) {
                    case instr::on:     grid[x][y]++;                 break;
                    case instr::off:    grid[x][y] -= grid[x][y] > 0; break;
                    case instr::toggle: grid[x][y] += 2;              break;
                }
            }
        }
    }
    int total = 0;
    for (auto i = 0; i < 1000; i++)
        for (auto j = 0; j < 1000; j++)
            total += grid[i][j];
    return total;
}
