#include "day.hpp"
struct pwd {
    std::array<char, 8> value;
    friend std::ostream& operator<<(std::ostream& os, const pwd& pass) {
        return os << pass.value;
    }
    void increment() {
        for (auto i = 7; i >= 0; i--) {
            if (value[i] == 'z')
                value[i] = 'a';
            else {
                value[i]++;
                break;
            }
        }
    }

    pwd(const std::string& s) {
        std::copy(s.begin(), s.end(), value.begin());
    }

    pwd& next() {
        while (1) {
            auto iol = [](auto& value) {
                for (auto i = 0; i < 8; i++) {
                    if (value[i] == 'i' || value[i] == 'o' || value[i] == 'l') {
                        // we found a bad value, so we can jump far ahead
                        value[i]++;
                        for (i++; i < 8; i++)
                            value[i] = 'a';
                        return true;
                    }
                }
                return false;
            };

            auto straight = [](auto& value) {
                for (auto i = 0; i < 6; i++) {
                    if (value[i] == value[i+1]-1 && value[i] == value[i+2]-2)
                        return true;
                }
                return false;
            };

            auto pairs = [](auto& value) {
                auto first = 8, second = 8;
                for (auto i = 0; i < 5; i++) {
                    if (value[i] == value[i+1]) {
                        first = i;
                        break;
                    }
                }
                for (auto i = first + 2; i < 7; i++) {
                    if (value[i] == value[i+1]) {
                        second = i;
                        break;
                    }
                }
                return first != 8 && second != 8;
            };

            if (iol(value))
                continue; // already incremented

            if (straight(value) && pairs(value))
                break;

            increment();
        }
        return *this;
    }
};
ret day::part1() {
    pwd pass{input[0]};
    auto next = pass.next();
    return std::string{next.value.data(), 8};
}
ret day::part2() {
    pwd pass{input[0]};
    auto first = pass.next();
    first.increment();
    auto second = first.next();
    return std::string{second.value.data(), 8};
}
