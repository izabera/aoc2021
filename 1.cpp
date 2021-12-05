#include "day.hpp"
ret day::part1() {
    auto prev = 0;
    auto incremented = 0;
    for (auto l : input) {
        auto tmp = std::stoi(l);
        if (prev < tmp)
            incremented++;
        prev = tmp;
    }
    return incremented - 1;
}
ret day::part2() {
    auto prev = 0;
    auto incremented = 0;

    auto a = 0;
    auto b = 0;
    for (auto l : input) {
        auto c = std::stoi(l);
        if (prev < a + b + c)
            incremented++;
        prev = a + b + c;
        a = b;
        b = c;
    }
    return incremented - 3;
}
