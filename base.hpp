#pragma once
#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <variant>
using ret = std::variant<int, std::string>;

struct baseday {
    void print() {
        std::visit([](auto&& arg){ std::cout << "part 1: " << arg << std::endl; }, part1());
        std::visit([](auto&& arg){ std::cout << "part 2: " << arg << std::endl; }, part2());
    }
    virtual ret part1() = 0;
    virtual ret part2() = 0;
};
extern baseday *days[25];
extern std::vector<std::string> *inputs[25];
