#include "day.hpp"
auto lookandsay(std::string str, int times) {
    for (auto i = 0; i < times; i++) {
        std::string tmp;
        auto digit = str[0];
        auto run = '1';

        for (auto j = 1u; j < str.size(); j++) {
            if (str[j] == digit)
                run ++;
            else {
                tmp += run;
                tmp += digit;
                digit = str[j];
                run = '1';
            }
        }
        tmp += run;
        tmp += digit;
        str = tmp;
    }
    return str.size();
}
ret day::part1() {
    auto str = input[0];
    return lookandsay(str, 40);
}
ret day::part2() {
    auto str = input[0];
    return lookandsay(str, 50);
}
