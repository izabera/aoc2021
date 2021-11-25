#pragma once
#include <fstream>
#include <iostream>
#include <iterator>
#include <algorithm>
#include <map>
#include <vector>
#include <string>
#include <variant>
using ret = std::variant<int, std::string>;

struct baseday {
    void print() {
        std::visit([](auto&& part1, auto&& part2){
                std::cout << "part 1: " << part1 << std::endl;
                std::cout << "part 2: " << part2 << std::endl;
                }, part1(), part2());
    }
    virtual ret part1() = 0;
    virtual ret part2() = 0;
};
extern baseday *days[25];
