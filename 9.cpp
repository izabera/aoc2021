#include "day.hpp"

namespace {
using city = int;
using pair = std::pair<city, city>;
using path = std::vector<city>;

std::pair<int,int> getminmaxtravels(const std::vector<std::string>& input) {
    std::map<std::string, city> cities;
    city citycount = 0;

    std::unordered_map<pair, int> distances;

    for (auto l : input) {
        auto vec = split(l);

        if (!cities.contains(vec[0]))
            cities[vec[0]] = ++citycount;
        if (!cities.contains(vec[2]))
            cities[vec[2]] = ++citycount;

        auto from = cities[vec[0]], to = cities[vec[2]];
        auto dist = std::stoi(vec[4]);
        distances[{from,to}] = dist;
        distances[{to,from}] = dist;
    }

    path current;
    for (auto [_, c] : cities)
        current.push_back(c);

    std::sort(current.begin(), current.end());

    int lo = std::numeric_limits<int>::max(), hi = 0;
    do {
        auto total = 0;
        for (auto i = 0u; i < current.size() -1; i++)
            total += distances[{current[i], current[i+1]}];

        if (total < lo) lo = total;
        if (total > hi) hi = total;
    } while (std::next_permutation(current.begin(), current.end()));

    return {lo, hi};
}
}

ret day::part1() {
    return getminmaxtravels(input).first;
}
ret day::part2() {
    return getminmaxtravels(input).second;
}
