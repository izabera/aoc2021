#include "day.hpp"
ret day::part1() {
    int total = 0, escaped = 0;
    for (auto l : input) {
        auto i = 0u;
        for ( ; i < l.size() -2 && ++escaped; i++) {
            if (l[i+1] != '\\') continue;
            if (l[++i+1] == 'x') i += 2;
        }
        total += l.size();
    }
    return total - escaped;
}
ret day::part2() {
    int total = 0, unescaped = 0;
    for (auto l : input) {
        unescaped += 2;
        for (auto c : l) {
            unescaped++;
            if (c == '"' || c == '\\') unescaped++;
        }
        total += l.size();
    }
    return unescaped - total;
}
