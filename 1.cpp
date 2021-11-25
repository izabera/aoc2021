#include "day.hpp"
ret day::part1() {
    int floor = 0;
    for (auto c : input[0])
        floor += c == '(' ? 1 : -1;
    return floor;
}
ret day::part2() {
    int floor = 0;
    auto pos = 0u;
    for ( ; pos < input[0].size() && floor >= 0; pos++)
        floor += input[0][pos] == '(' ? 1 : -1;
    return pos;
}
