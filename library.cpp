#include "library.hpp"

std::vector<std::string> split(const std::string& s, const std::string& delim) {
    std::vector<std::string> vec;
    auto len = s.size();

    for (size_t start = 0u, end; start < len; start += end) {
        end = s.find_first_of(delim, start);
        if (end == std::string::npos)
            end = len;

        vec.push_back(s.substr(start, end));
        start += end;
    }
    return vec;
}

std::vector<std::string> split(const std::string& s, char delim) {
    return split(s, std::string(1, delim));
}
