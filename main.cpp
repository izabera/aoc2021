#include <iostream>
#include <iomanip>
#include <chrono>
#include "base.hpp"

void baseday::print() {
    auto t0 = std::chrono::system_clock::now();
    auto p1 = part1();
    auto t1 = std::chrono::system_clock::now();
    auto p2 = part2();
    auto t2 = std::chrono::system_clock::now();

    std::chrono::duration<double> dur1 = t1 - t0;
    std::chrono::duration<double> dur2 = t2 - t1;

    auto printer = [](auto&& arg, auto part, auto time) {
        std::cout << "part " << part << ": ";
        std::cout << std::setw(10) << arg;
        std::cout << " (" << std::fixed << time << "s)";
        std::cout << std::endl;
    };

    std::visit([time = dur1.count(), printer](auto&& arg) { printer(arg, 1, time); }, p1);
    std::visit([time = dur2.count(), printer](auto&& arg) { printer(arg, 2, time); }, p2);
}

baseday *days[25];

namespace {
    void print(size_t i) {
        if (days[i]) {
            std::cout << "day " << i+1 << "\n";
            days[i]->print();
        }
    }
}

int main(int argc, char **argv) {
    if (argc > 1) {
        for (auto i = 1; i < argc; i++)
            print(std::stoi(argv[i])-1);
    }
    else {
        for (auto i = 0u; i < sizeof(days)/sizeof*days; i++)
            print(i);
    }
}
