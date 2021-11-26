#include "day.hpp"
ret day::part1() {
    for (auto i = 0; ; i++) {
        auto str = input[0] + std::to_string(i);
        auto sum = md5(str);

        if (sum[0] == 0 &&
            sum[1] == 0 &&
            sum[2] >> 4 == 0)
            return i;
    }
}
ret day::part2() {
    for (auto i = 0; ; i++) {
        auto str = input[0] + std::to_string(i);
        auto sum = md5(str);

        if (sum[0] == 0 &&
            sum[1] == 0 &&
            sum[2] == 0)
            return i;
    }
}
