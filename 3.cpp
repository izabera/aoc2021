#include "day.hpp"

namespace {
constexpr int nbits = 12;
using num = std::bitset<nbits>;
num common(std::unordered_set<num> nums) {
    int comm[nbits] = {0};

    for (auto n : nums) {
        for (auto i = 0; i < nbits; i++)
            comm[i] += n[i];
    }

    int size = nums.size();
    num ret;
    for (auto i = 0; i < nbits; i++)
        ret[i] = comm[i] >= (size - comm[i]);
    return ret;
}
}

ret day::part1() {
    std::unordered_set<num> nums;
    for (auto l : input)
        nums.insert(num{l});

    auto gamma = common(nums);
    return gamma.to_ulong() * (~gamma).to_ulong();
}

ret day::part2() {
    std::unordered_set<num> nums;
    for (auto l : input)
        nums.insert(num{l});

    std::unordered_set<num> oxyset = nums, co2set = nums, tmp;

    for (auto bit = nbits - 1; bit >= 0; bit--) {
        if (oxyset.size() > 1) {
            auto oxy = common(oxyset);
            tmp.clear();
            for (auto elem : oxyset) {
                if (elem[bit] == oxy[bit]) {
                    tmp.insert(elem);
                }
            }
            oxyset = tmp;
        }
        if (co2set.size() > 1) {
            auto co2 = ~common(co2set);
            tmp.clear();
            for (auto elem : co2set) {
                if (elem[bit] == co2[bit])
                    tmp.insert(elem);
            }
            co2set = tmp;
        }
    }

    auto oxy = *oxyset.begin();
    auto co2 = *co2set.begin();
    return oxy.to_ulong() * co2.to_ulong();
}
