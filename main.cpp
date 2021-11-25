#include "base.hpp"

baseday *days[25];
std::vector<std::string> *inputs[25];

int main() {
    for (auto i = 0u; i < sizeof(days)/sizeof*days; i++) {
        if (days[i]) {
            std::cout << "day " << i << "\n";
            days[i]->print();
        }
    }
}
