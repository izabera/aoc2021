#pragma once
#include <algorithm>
#include <array>
#include <bitset>
#include <cctype>
#include <fstream>
#include <iostream>
#include <iterator>
#include <limits>
#include <map>
#include <set>
#include <sstream>
#include <string>
#include <string_view>
#include <unordered_map>
#include <unordered_set>
#include <vector>

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
    if constexpr (std::is_same_v<t, typename decltype(vec)::value_type>)
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

std::array<uint8_t, 16> md5(const std::string& s);

// https://stackoverflow.com/a/56766138/2815203
template <typename T>
constexpr auto type_name() {
  std::string_view name, prefix, suffix;
#ifdef __clang__
  name = __PRETTY_FUNCTION__;
  prefix = "auto type_name() [T = ";
  suffix = "]";
#elif defined(__GNUC__)
  name = __PRETTY_FUNCTION__;
  prefix = "constexpr auto type_name() [with T = ";
  suffix = "]";
#elif defined(_MSC_VER)
  name = __FUNCSIG__;
  prefix = "auto __cdecl type_name<";
  suffix = ">(void)";
#endif
  name.remove_prefix(prefix.size());
  name.remove_suffix(suffix.size());
  return name;
}

// with clang, is_to_stream_writable<std::array<char, n>> is false if this is
// below is_to_stream_writable. no such problem with gcc
template <size_t n>
std::ostream& operator<<(std::ostream& os, std::array<char, n> array) {
    return os << std::string_view{array.data(), array.size()};
}

template <size_t n>
std::ostream& operator<<(std::ostream& os, std::array<int, n> array) {
    os << "{";
    auto sep = " ";
    for (auto i : array) {
        os << sep << i;
        sep = ", ";
    }
    return os << " }";
}

template <typename k, typename v>
std::ostream& operator<<(std::ostream& os, const std::map<k,v>& map) {
    os << "(" << map.size() << ")";
    os << "{";
    auto sep = " ";
    for (auto [key, val] : map) {
        os << sep << key << ": " << val;
        sep = ", ";
    }
    return os << " }";
}

template <typename k, typename v>
std::ostream& operator<<(std::ostream& os, const std::unordered_map<k,v>& map) {
    os << "(" << map.size() << ")";
    os << "{";
    auto sep = " ";
    for (auto [key, val] : map) {
        os << sep << key << ": " << val;
        sep = ", ";
    }
    return os << " }";
}

template <typename t>
std::ostream& operator<<(std::ostream& os, const std::set<t>& set) {
    os << "(" << set.size() << ")";
    os << "{";
    auto sep = " ";
    for (auto item : set) {
        os << sep << item;
        sep = ", ";
    }
    return os << " }";
}

template <typename t>
std::ostream& operator<<(std::ostream& os, const std::unordered_set<t>& set) {
    os << "(" << set.size() << ")";
    os << "{";
    auto sep = " ";
    for (auto item : set) {
        os << sep << item;
        sep = ", ";
    }
    return os << " }";
}

// https://stackoverflow.com/a/49026811/2815203
template<typename S, typename T, typename = void>
struct is_to_stream_writable: std::false_type {};

template<typename S, typename T>
struct is_to_stream_writable<S, T,
        std::void_t<  decltype( std::declval<S&>()<<std::declval<T>() )  > >
: std::true_type {};

template <typename T>
std::ostream& debug(const std::string& name, T val, int line, bool nl = true) {
    std::cout << line << ":";
    std::cout << name << "=";
    std::cout << "\x1b[33m";
    std::cout << "(" << type_name<decltype(val)>() << ")";
    std::cout << "\x1b[32m";
    if constexpr (is_to_stream_writable<std::ostream,decltype(val)>::value)
        std::cout << val;
    else
        std::cout << "<unprintable>";
    std::cout << "\x1b[m";
    if (nl)
        std::cout << std::endl;
    return std::cout;
}
#define debug(x, ...) debug(#x, (x), __LINE__, ##__VA_ARGS__)

// why is this not in the standard??
namespace std {
template <typename t1, typename t2>
struct hash<pair<t1,t2>> {
    size_t operator() (const pair<t1,t2> &p) const {
        return hash<t1>{}(p.first) ^ hash<t2>{}(p.second);
    }
};
template <size_t N>
bool operator<(const bitset<N>& x, const bitset<N>& y) {
    for (int i = N-1; i >= 0; i--) {
        if (x[i] && !y[i]) return false;
        if (!x[i] && y[i]) return true;
    }
    return false;
}
}


// quick implementation that doesn't do any checks
template <typename a, typename b>
class bidimap {
    std::unordered_map<a,b> ab;
    std::unordered_map<b,a> ba;

   public:
    bool contains(a aa) { return ab.contains(aa); }
    bool contains(b bb) { return ba.contains(bb); }

    void set(a aa, b bb) { ab[aa] = bb; ba[bb] = aa; }
    void set(b bb, a aa) { ab[aa] = bb; ba[bb] = aa; }

    a get(b bb) { return ba[bb]; }
    b get(a aa) { return ab[aa]; }

    auto size() { return ab.size(); }
    auto begin() { return ab.begin(); }
    auto end() { return ab.end(); }
};

template <typename t>
class interning : public bidimap<t,int> {
    int count = 0;
   public:
    void intern(t key) { if (!this->contains(key)) this->set(key, count++); }

};
