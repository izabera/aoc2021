#include <iostream>
#include <unistd.h>
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
        if (isatty(1)) {
            auto colour = time < 0.1 ? 2 :
                          time < 0.5 ? 3 : 1;
            std::cout << " (\x1b[3" << colour << "m" << std::fixed << std::setprecision(3) << time << "s\x1b[m)";
        }
        else
            std::cout << " (" << std::fixed << std::setprecision(3) << time << "s)";
    };

    std::visit([time = dur1.count(), printer](auto&& arg) { printer(arg, 1, time); }, p1);
    std::cout << "     ";
    std::visit([time = dur2.count(), printer](auto&& arg) { printer(arg, 2, time); }, p2);
    std::cout << std::endl;
}

baseday *days[25];

namespace {
    void print(size_t i) {
        if (days[i]) {
            std::cout << "day " << std::setw(2) << i+1 << ":     ";
            days[i]->print();
        }
    }
}

int main(int argc, char **argv) {
    auto t0 = std::chrono::system_clock::now();
    if (argc > 1) {
        for (auto i = 1; i < argc; i++)
            print(std::stoi(argv[i])-1);
    }
    else {
        for (auto i = 0u; i < sizeof(days)/sizeof*days; i++)
            print(i);
    }
    auto t1 = std::chrono::system_clock::now();
    std::chrono::duration<double> duration = t1 - t0;
    std::cout << "total: " << std::fixed << std::setprecision(3) << duration.count() << "s\n";
}
