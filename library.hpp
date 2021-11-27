#pragma once
#include <algorithm>
#include <array>
#include <sstream>
#include <string>
#include <string_view>
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

// https://stackoverflow.com/a/49026811/2815203
template<typename S, typename T, typename = void>
struct is_to_stream_writable: std::false_type {};

template<typename S, typename T>
struct is_to_stream_writable<S, T,
        std::void_t<  decltype( std::declval<S&>()<<std::declval<T>() )  > >
: std::true_type {};

template<typename T>
std::ostream& debug(const std::string& name, T val, bool nl = true) {
    std::cout << name << "=";
    std::cout << "(" << type_name<T>() << ")";
    if constexpr (is_to_stream_writable<std::ostream,T>::value)
        std::cout << val;
    else
        std::cout << "<unprintable>";
    if (nl)
        std::cout << std::endl;
    return std::cout;
}
#define debug(x, ...) debug(#x, x, ##__VA_ARGS__)
