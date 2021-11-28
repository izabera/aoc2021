#include "day.hpp"
ret day::part1() {
    int longest = 0;
    int limit = 2503;

    for (auto l : input) {
        auto vec = split(l);

        auto speed = std::stoi(vec[3]);
        auto time = std::stoi(vec[6]);
        auto rest = std::stoi(vec[13]);

        int total = 0;
        enum { flying, sleeping } state = flying;
        for (auto i = 0; i < limit; i++, state = state == flying ? sleeping : flying) {
            if (state == flying) {
                if (i < limit - time) {
                    total += speed * time;
                    i += time - 1;
                }
                else {
                    total += speed * (limit - i);
                    break;
                }
            }
            else {
                if (i < limit - rest) {
                    i += rest - 1;
                }
                else {
                    break;
                }
            }
        }
        if (longest < total) longest = total;
    }

    return longest;
}

struct reindeer {
    std::string name;
    int speed;
    int time;
    int rest;

    enum { flying, sleeping } state;
    int progress; // [0, time) or [0, rest)
    int total;
    int points;
};
ret day::part2() {
    int limit = 2503;

    std::vector<reindeer> reindeers;
    for (auto l : input) {
        auto vec = split(l);

        reindeer r;
        r.name = vec[0];
        r.speed = std::stoi(vec[3]);
        r.time = std::stoi(vec[6]);
        r.rest = std::stoi(vec[13]);
        r.state = reindeer::flying;
        r.progress = 0;
        r.total = 0;
        r.points = 0;
        
        reindeers.push_back(r);
    }

    for (auto i = 0; i < limit; i++) {
        int farthest = 0;
        for (auto& r : reindeers) {
            if (r.state == reindeer::flying) {
                r.total += r.speed;
                if (++r.progress == r.time) {
                    r.progress = 0;
                    r.state = reindeer::sleeping;
                }
            }
            else {
                if (++r.progress == r.rest) {
                    r.progress = 0;
                    r.state = reindeer::flying;
                }
            }
            if (r.total > farthest)
                farthest = r.total;
        }

        for (auto& r : reindeers)
            if (r.total == farthest)
                r.points++;
    }

    int most_points = 0;
    for (auto& r : reindeers)
        if (r.points > most_points)
            most_points = r.points;

    return most_points;
}
