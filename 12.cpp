#include <regex>
#include "day.hpp"
ret day::part1() {
    auto s = input[0];
    std::regex num("(-?[0-9]+)");
    auto num_begin = std::sregex_iterator(s.begin(), s.end(), num);
    auto num_end = std::sregex_iterator();

    int sum = 0;
    for (auto it = num_begin; it != num_end; ++it) {
        sum += std::stoi(it->str());
    }
    return sum;
}
ret day::part2() { return "default"; }
