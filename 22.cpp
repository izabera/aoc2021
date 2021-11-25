#include "day.hpp"
ret day::part1() {
    std::string solution = "input = [ ";
    for (auto line : input)
        solution += "<" + line + "> ";
    return solution + "]";
}
ret day::part2() { return "default"; }
