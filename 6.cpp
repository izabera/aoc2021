#include "day.hpp"
namespace {
std::unordered_map<std::pair<int, int>, uint64_t> fishmap;

uint64_t fish(int age, int time) {
    auto it = fishmap.find({age, time});
    if (it != fishmap.end())
        return it->second;

    uint64_t ret;
    if (time == 0)
        ret = 1;
    else if (age == 0)
        ret = fish(6, time - 1) + fish(8, time - 1);
    else
        ret = fish(age - 1, time - 1);
    fishmap[{age, time}] = ret;
    return ret;
}
}  // namespace

ret day::part1() {
    auto ages = split<int>(input[0], ',');

    uint64_t sum = 0;
    for (auto a : ages)
        sum += fish(a, 80);
    return sum;
}
ret day::part2() {
    auto ages = split<int>(input[0], ',');

    uint64_t sum = 0;
    for (auto a : ages)
        sum += fish(a, 256);
    return sum;
}
