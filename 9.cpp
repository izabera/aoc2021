#include "day.hpp"

namespace {
    using city = int;
    using pair = std::pair<city, city>;
    using path = std::vector<city>;
    std::map<path, int> g_travels;
};

std::map<path, int>& getalltravels(const std::vector<std::string>& input) {
    if (!g_travels.empty())
        return g_travels;
    auto& travels = g_travels;

    std::map<std::string, city> cities;
    city citycount = 0;

    std::map<pair, int> distances;

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

    do {
        auto total = 0;
        for (auto i = 0u; i < current.size() -1; i++)
            total += distances[{current[i], current[i+1]}];

        travels[current] = total;
    } while (std::next_permutation(current.begin(), current.end()));

    return travels;
}

ret day::part1() {
    auto travels = getalltravels(input);
    return std::min_element(travels.begin(), travels.end(),
            [](const auto& l, const auto& r) { return l.second < r.second; })->second;
}
ret day::part2() {
    auto travels = getalltravels(input);
    return std::max_element(travels.begin(), travels.end(),
            [](const auto& l, const auto& r) { return l.second < r.second; })->second;
}
