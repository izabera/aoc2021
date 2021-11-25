#pragma once
#include <string>
#include <vector>
#include <algorithm>
#include <sstream>

namespace detail {
    std::vector<std::string> split(const std::string& s, char delim);
    std::vector<uint64_t> factor(uint64_t);
}

template <typename t>
t gcd(t a, t b) {
   if (b == 0) return a;
   return gcd<t>(b, a % b);
}

template <typename t>
t lcm(t a, t b) {
    return a / gcd<t>(a, b) * b;
}

template <typename t>
std::vector<t> factor(t num) {
    auto vec = detail::factor(num);
    if constexpr (std::is_same_v<t, decltype(vec)::value_type>)
        return vec;

    std::vector<t> dest;
    dest.reserve(vec.size());

    std::transform(vec.begin(), vec.end(), std::back_inserter(dest), [](auto v) { return static_cast<t>(v); });
    return dest;
}

template <typename t = std::string>
std::vector<t> split(const std::string& s, char delim = ' ') {
    auto vec = detail::split(s, delim);

    if constexpr (std::is_same_v<t, std::string>)
        return vec;

    std::vector<t> dest;
    dest.reserve(vec.size());

    std::transform(vec.begin(), vec.end(), std::back_inserter(dest),
            [](auto s) {
                t ret;
                std::istringstream(s) >> ret;
                return ret;
            });
    return dest;
}
