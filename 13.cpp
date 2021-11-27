#include "day.hpp"

namespace {
using person = int;
using pair = std::pair<person, person>;

std::pair<int,int> getminmaxhappy(const std::vector<std::string>& input) {
    interning<std::string> people;

    std::unordered_map<pair, int> edges;

    for (auto l : input) {
        auto vec = split(l);

        auto p1 = vec[0];
        auto p2 = vec[10];
        p2.pop_back();
        auto level = (vec[2] == "gain" ? 1 : -1) * std::stoi(vec[3]);

        people.intern(p1);
        people.intern(p2);

        auto from = people.get(p1), to = people.get(p2);
        edges[{from,to}] += level;
        edges[{to,from}] += level;
    }

    std::vector<person> current;
    for (auto [_, p] : people)
        current.push_back(p);
    auto size = current.size();

    std::sort(current.begin(), current.end());

    int lo = std::numeric_limits<int>::max(), hi = 0;
    do {
        auto total = edges[{current[0],current[size-1]}];
        for (auto i = 0u; i < current.size() -1; i++)
            total += edges[{current[i], current[i+1]}];

        if (total < lo) lo = total;
        if (total > hi) hi = total;
    } while (std::next_permutation(current.begin() /* it doesn't matter who starts */ +1, current.end()));

    return {lo, hi};
}
}

ret day::part1() {
    return getminmaxhappy(input).second;
}
ret day::part2() {
    input.push_back("Myself would gain 0 happiness units by sitting next to Myself.");
    return getminmaxhappy(input).second;
}
