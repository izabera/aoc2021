#include "library.hpp"

std::vector<std::string> detail::split(const std::string& s, char delim) {
    std::stringstream ss(s);
    std::string word;
    std::vector<std::string> words;
    while (std::getline(ss, word, delim))
        words.push_back(word);
    return words;
}

std::vector<uint64_t> detail::factor(uint64_t num) {
    std::vector<uint64_t> factors;
    for (auto factor : {2, 3, 5, 7}) {
        while (num % factor == 0) {
            num /= factor;
            factors.push_back(factor);
        }
    }

    // mini wheel
    for (uint64_t factor = 11, increment = 4; factor * factor <= num; factor += (increment ^= 6)) {
        while (num % factor == 0) {
            num /= factor;
            factors.push_back(factor);
        }
    }

    if (num > 1)
        factors.push_back(num);

    return factors;
}

uint64_t gcd(uint64_t a, uint64_t b) {
    if (b == 0)
        return a;
    return gcd(b, a % b);
}

uint64_t lcm(uint64_t a, uint64_t b) {
    return a / gcd(a, b) * b;
}

#include <openssl/md5.h>
std::array<uint8_t, 16> md5(const std::string& s) {
    std::array<uint8_t, 16> ret;
    MD5((uint8_t*)(s.data()), s.size(), ret.data());
    return ret;
}
