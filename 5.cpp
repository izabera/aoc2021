#include <cmath>
#include "day.hpp"
ret day::part1() {
    std::vector<std::string> banned { "ab", "cd", "pq", "xy" };
    int nicecount = 0;
    for (auto s : input) {
        int vowels = std::count_if(s.begin(), s.end(),
                [](auto c) { return c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u'; });
        if (vowels < 3)
            goto bad;

        for (auto ban : banned) {
            if (s.find(ban) != std::string::npos)
                goto bad;
        }

        for (auto i = 1u; i < s.size(); i++) {
            if (s[i-1] == s[i])
                goto good;
        }

        bad: continue;
        good: nicecount++;
    }
    return nicecount;
}
ret day::part2() {
    int nicecount = 0;
    for (auto s : input) {
        bool found = false;
        for (auto i = 0u; i < s.size() - 2; i++) {
            if (s[i] == s[i+2]) {
                found = true;
            }
        }
        if (!found)
            goto bad;

        for (auto i = 0; static_cast<size_t>(i) < s.size() - 1; i++) {
            for (auto j = 0; static_cast<size_t>(j) < s.size() - 1; j++) {
                if (abs(i - j) < 2)
                    continue;
                if (s[i] == s[j] && s[i+1] == s[j+1])
                    goto good;
            }
        }

        bad: continue;
        good: nicecount++;
    }
    return nicecount;
}
