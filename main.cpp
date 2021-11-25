#include "base.hpp"

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
