#include "day.hpp"
ret day::part1() {
    int total = 0;
    for (auto line : input) {
        auto vec = split<int>(line, 'x');

        int lo = std::min({vec[0], vec[1], vec[2]});
        int hi = std::max({vec[0], vec[1], vec[2]});
        int mi = vec[0] + vec[1] + vec[2] - lo - hi;

        total += 3 * lo * mi +
                 2 * lo * hi +
                 2 * hi * mi;
    }
    return total;
}
ret day::part2() {
    int total = 0;
    for (auto line : input) {
        auto vec = split<int>(line, 'x');

        int lo = std::min({vec[0], vec[1], vec[2]});
        int hi = std::max({vec[0], vec[1], vec[2]});
        int mi = vec[0] + vec[1] + vec[2] - lo - hi;

        total += 2 * lo +
                 2 * mi +
                 lo * mi * hi;
    }
    return total;
}
