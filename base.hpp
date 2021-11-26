#pragma once
#include <fstream>
#include <iostream>
#include <iterator>
#include <algorithm>
#include <map>
#include <vector>
#include <string>
#include <variant>
using ret = std::variant<int, uint32_t, uint64_t, std::string>;

struct baseday {
    void print() {
        std::visit([](auto&& arg) { std::cout << "part 1: " << arg << std::endl; }, part1());
        std::visit([](auto&& arg) { std::cout << "part 2: " << arg << std::endl; }, part2());
    }
    virtual ret part1() = 0;
    virtual ret part2() = 0;
};
extern baseday *days[25];
