#include "day.hpp"
ret day::part1() {
    std::map<std::pair<int,int>, int> memo;
    int x = 0, y = 0;
    memo[{x,y}] = 1;
    for (auto c : input[0]) {
        switch (c) {
            case '<': x--; break;
            case '>': x++; break;
            case 'v': y--; break;
            case '^': y++; break;
        }
        memo[{x,y}] += 1;
    }
    return memo.size();
}
ret day::part2() {
    std::map<std::pair<int,int>, int> memo;
    std::pair<int,int> santas[2];
    memo[santas[0]] = 1;
    int count = 0;
    for (auto c : input[0]) {
        switch (c) {
            case '<': santas[count % 2].first--; break;
            case '>': santas[count % 2].first++; break;
            case 'v': santas[count % 2].second--; break;
            case '^': santas[count % 2].second++; break;
        }
        memo[santas[count++ % 2]] += 1;
    }
    return memo.size();
}
