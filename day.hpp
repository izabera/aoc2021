#include "base.hpp"
namespace {
struct day : baseday {
    std::vector<std::string> *input = inputs[currentday-1];
    day() { days[currentday-1] = this; }
    virtual ret part1();
    virtual ret part2();
};
day instance;
}
