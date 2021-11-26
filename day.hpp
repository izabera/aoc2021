#pragma once
#include <algorithm>
#include <cctype>
#include <fstream>
#include <iterator>
#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include "base.hpp"
#include "library.hpp"
namespace {
struct day : baseday {
    std::vector<std::string> input;
    day() {
        days[currentday-1] = this;

        std::ifstream file(std::to_string(currentday) + ".input");
        std::string line;
        while (std::getline(file, line)) input.push_back(line);
    }
    virtual ret part1();
    virtual ret part2();
};
day instance;
}
