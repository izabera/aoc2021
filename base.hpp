#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <variant>
using ret = std::variant<int, uint32_t, uint64_t, std::string>;

struct baseday {
    void print();
    virtual ret part1() = 0;
    virtual ret part2() = 0;
};
extern baseday *days[25];
