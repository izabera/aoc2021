#include "day.hpp"
ret day::part1() {
    int pos = 0, depth = 0;
    for (auto l : input) {
        auto vec = split(l);
        auto val = std::stoi(vec[1]);
        if (vec[0] == "forward")
            pos += val;
        if (vec[0] == "down")
            depth += val;
        if (vec[0] == "up")
            depth -= val;
    }
    return pos * depth;
}
ret day::part2() {
    int pos = 0, depth = 0, aim = 0;
    for (auto l : input) {
        auto vec = split(l);
        auto val = std::stoi(vec[1]);
        if (vec[0] == "forward") {
            pos += val;
            depth += aim * val;
        }
        if (vec[0] == "down")
            aim += val;
        if (vec[0] == "up")
            aim -= val;
    }
    return pos * depth;
}
