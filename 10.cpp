#include "day.hpp"
#include <cstring>
namespace {
// this is so much faster than allocating the strings every time
char buf0[10000000];
char buf1[10000000];
auto lookandsay(std::string str, int times) {
    memcpy(buf0, str.data(), str.size() + 1);

    char *bufs[] = { buf0, buf1 }, *ptr, *tmp;

    for (auto i = 0; i < times; i++) {
        ptr = bufs[i%2];
        tmp = bufs[(i+1)%2];

        auto digit = ptr[0];
        auto run = '1';

        for (auto j = 1u; ptr[j]; j++) {
            if (ptr[j] == digit)
                run++;
            else {
                *tmp++ = run;
                *tmp++ = digit;
                digit = ptr[j];
                run = '1';
            }
        }
        *tmp++ = run;
        *tmp++ = digit;
        *tmp++ = 0;
    }
    return tmp - bufs[times%2] - 1;
}
}

ret day::part1() {
    auto str = input[0];
    return lookandsay(str, 40);
}
ret day::part2() {
    auto str = input[0];
    return lookandsay(str, 50);
}
