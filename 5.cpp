#include "day.hpp"
#include <thread>
ret day::part1() {
    const int nthreads = std::thread::hardware_concurrency();

    struct line { int x0, y0, x1, y1; };
    std::vector<line> lines;
    int size = 0;

    for (auto l : input) {
        auto xy = split(l);
        auto a = split<int>(xy[0], ',');
        auto b = split<int>(xy[2], ',');
        int x0 = a[0], y0 = a[1], x1 = b[0], y1 = b[1];
        size = std::max({x0, y0, x1, y1, size});
        lines.push_back(line{x0, y0, x1, y1});
    }
    size++;

    std::vector<int> results(nthreads);
    auto calc = [nthreads, lines, size, &results](auto idx) {
        uint64_t total = 0;

        // solve it for each row in this range
        auto ymin = idx * size/nthreads;
        auto ymax = std::min((idx+1) * size/nthreads, size);

        for (auto y = ymin; y < ymax; y++) {
            std::vector<uint16_t> current(size);
            for (auto [x0, y0, x1, y1] : lines) {
                if (!((y0 <= y && y <= y1) || (y0 >= y && y >= y1)))
                    continue;

                auto dx = std::clamp(x1 - x0, -1, 1);

                if (y0 == y1) {
                    while (x0 != x1) {
                        current[x0]++;
                        x0 += dx;
                    }
                    current[x0]++;
                }
                else if (x0 == x1)
                    current[x0]++;
            }

            for (auto i : current)
                total += i >= 2;
        }
        results[idx] = total;
    };

    std::vector<std::thread> threads;
    for (auto i = 0; i < nthreads; i++)
        threads.push_back(std::thread{calc, i});

    uint64_t sum = 0;
    for (auto i = 0; i < nthreads; i++) {
        threads[i].join();
        sum += results[i];
    }
    return sum;
}

ret day::part2() {
    const int nthreads = std::thread::hardware_concurrency();

    struct line { int x0, y0, x1, y1; };
    std::vector<line> lines;
    int size = 0;

    for (auto l : input) {
        auto xy = split(l);
        auto a = split<int>(xy[0], ',');
        auto b = split<int>(xy[2], ',');
        int x0 = a[0], y0 = a[1], x1 = b[0], y1 = b[1];
        size = std::max({x0, y0, x1, y1, size});
        lines.push_back(line{x0, y0, x1, y1});
    }
    size++;

    std::vector<int> results(nthreads);
    auto calc = [nthreads, lines, size, &results](auto idx) {
        uint64_t total = 0;

        // solve it for each row in this range
        auto ymin = idx * size/nthreads;
        auto ymax = std::min((idx+1) * size/nthreads, size);

        for (auto y = ymin; y < ymax; y++) {
            std::vector<uint16_t> current(size);
            for (auto [x0, y0, x1, y1] : lines) {
                if (!((y0 <= y && y <= y1) || (y0 >= y && y >= y1)))
                    continue;

                auto dx = std::clamp(x1 - x0, -1, 1);

                if (y0 == y1) {
                    while (x0 != x1) {
                        current[x0]++;
                        x0 += dx;
                    }
                    current[x0]++;
                }
                else if (x0 == x1)
                    current[x0]++;
                else
                    current[x0 + dx * std::abs(y - y0)]++;
            }

            for (auto i : current)
                total += i >= 2;
        }
        results[idx] = total;
    };

    std::vector<std::thread> threads;
    for (auto i = 0; i < nthreads; i++)
        threads.push_back(std::thread{calc, i});

    uint64_t sum = 0;
    for (auto i = 0; i < nthreads; i++) {
        threads[i].join();
        sum += results[i];
    }
    return sum;
}
