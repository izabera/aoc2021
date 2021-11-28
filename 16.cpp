#include "day.hpp"
namespace {
using sue = std::unordered_map<std::string, int>;

sue target {
    { "children", 3 },
    { "cats", 7 },
    { "samoyeds", 2 },
    { "pomeranians", 3 },
    { "akitas", 0 },
    { "vizslas", 0 },
    { "goldfish", 5 },
    { "trees", 3 },
    { "cars", 2 },
    { "perfumes", 1 },
};
sue parsesue(std::string l) {
    sue ret;
    //Sue 15: vizslas: 2, perfumes: 8, trees: 3
    // find ':', skip the space, then remove all commas and colons
    auto colonpos = l.find(':');
    auto str = l.substr(colonpos + 2);
    str.erase(std::remove(str.begin(), str.end(), ','), str.end());
    str.erase(std::remove(str.begin(), str.end(), ':'), str.end());

    auto vec = split(str);
    for (auto i = 0u; i < vec.size(); i += 2)
        ret[vec[i]] = std::stoi(vec[i+1]);

    return ret;
}
}

ret day::part1() {
    auto id = 0;
    for (auto l : input) {
        id++;

        auto current = parsesue(l);

        for (auto [k, v] : current) {
            if (target[k] != v)
                goto bad;
        }
        return id;
        bad: continue;
    }
    return 0;
}
ret day::part2() {
    auto id = 0;
    for (auto l : input) {
        id++;

        auto current = parsesue(l);

        for (auto [k, v] : current) {
            if (k == "cats" || k == "trees") {
                if (target[k] >= v)
                    goto bad;
            }
            else if (k == "pomeridians" || k == "goldfish") {
                if (target[k] <= v)
                    goto bad;
            }
            else
                if (target[k] != v)
                    goto bad;
        }
        return id;
        bad: continue;
    }
    return 0;
}
