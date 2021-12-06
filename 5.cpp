#include "day.hpp"
#include <sys/mman.h>
#include <thread>
ret day::part1() {
    const int nthreads = std::thread::hardware_concurrency();

    struct line { int x0, y0, x1, y1; };
    std::vector<line> hori;
    std::vector<line> vert;
    // std::vector<line> diag;
    int size = 0;

    /* split the input into horizontal, vertical and diagonal lines
     * horizontal lines are stored left to right
     * vertical lines are stored top to bottom
     * */
    for (auto l : input) {
        auto xy = split(l);
        auto a = split<int>(xy[0], ',');
        auto b = split<int>(xy[2], ',');
        int x0 = a[0], y0 = a[1], x1 = b[0], y1 = b[1];
        size = std::max({x0, y0, x1, y1, size});
        if (y0 == y1) {
            if (x0 > x1) {
                std::swap(x0, x1);
                std::swap(y0, y1);
            }
            hori.push_back(line{x0, y0, x1, y1});
        }
        else if (x0 == x1) {
            if (y0 > y1) {
                std::swap(x0, x1);
                std::swap(y0, y1);
            }
            vert.push_back(line{x0, y0, x1, y1});
        }
        /*
        else
            diag.push_back(line{x0, y0, x1, y1});
            */
    }
    size++;

    std::vector<int> results(nthreads);
    auto calc = [nthreads, horitmp = hori, vert, /* diag, */ size, &results](auto idx) {
        uint64_t total = 0;

        // solve it for each row in this range
        auto ymin = idx * size/nthreads;
        auto ymax = std::min((idx+1) * size/nthreads, size);

        // we can skip large chunks of hori
        std::vector<line> hori;
        for (auto l : horitmp)
            if (ymin <= l.y0 && l.y0 <= ymax)
                hori.push_back(l);

        std::sort(hori.begin(), hori.end(), [](const auto& lhs, const auto& rhs) { return lhs.y0 < rhs.y0; });

        std::vector<uint16_t> current(size);
        mlock(current.data(), current.size() * sizeof current[0]);
        mlock(hori.data(), hori.size() * sizeof hori[0]);
        mlock(vert.data(), vert.size() * sizeof vert[0]);

#ifdef show_progress
        auto starttime = std::chrono::system_clock::now();
        auto onepercent = (ymax - ymin) / 100.f;
        auto nextprogress = ymin + onepercent;
#endif
        for (auto y = ymin; y < ymax; y++) {
#ifdef show_progress
            if (y > nextprogress) {
                auto now = std::chrono::system_clock::now();
                std::chrono::duration<double> elapsed = now - starttime;
                std::cout << "part1 thread " << idx
                          << " [" << ymin << "," << ymax << ") "
                          << ((y - ymin) / onepercent) << "% "
                          << elapsed.count() << "s" << std::endl;
                nextprogress += onepercent;
            }
#endif
            std::fill(current.begin(), current.end(), 0);

            // we can skip even more chunks of hori
            struct comp {
                bool operator()(const line& l, int y) const { return l.y0 < y; }
                bool operator()(int y, const line& l) const { return y < l.y0; }
            };
            auto [hbegin, hend] = std::equal_range(hori.begin(), hori.end(), y, comp{});
            for (auto it = hbegin; it != hend; it++) {
                auto [x0, y0, x1, y1] = *it; // y0 and y1 ignored
                for ( ; x0 <= x1; x0++)
                    current[x0]++;
            }

            for (auto [x0, y0, x1, y1] : vert) {
                if (y0 <= y && y <= y1) // x1 ignored
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
    std::vector<line> hori, vert, diag;
    int size = 0;

    /* split the input into horizontal, vertical and diagonal lines
     * horizontal lines are stored left to right
     * vertical lines are stored top to bottom
     * */
    for (auto l : input) {
        auto xy = split(l);
        auto a = split<int>(xy[0], ',');
        auto b = split<int>(xy[2], ',');
        int x0 = a[0], y0 = a[1], x1 = b[0], y1 = b[1];
        size = std::max({x0, y0, x1, y1, size});
        if (y0 == y1) {
            if (x0 > x1) {
                std::swap(x0, x1);
                std::swap(y0, y1);
            }
            hori.push_back(line{x0, y0, x1, y1});
        }
        else if (x0 == x1) {
            if (y0 > y1) {
                std::swap(x0, x1);
                std::swap(y0, y1);
            }
            vert.push_back(line{x0, y0, x1, y1});
        }
        else
            diag.push_back(line{x0, y0, x1, y1});
    }
    size++;

    std::vector<int> results(nthreads);
    auto calc = [nthreads, horitmp = hori, vert, diag, size, &results](auto idx) {
        uint64_t total = 0;

        // solve it for each row in this range
        auto ymin = idx * size/nthreads;
        auto ymax = std::min((idx+1) * size/nthreads, size);

        // we can skip large chunks of hori
        std::vector<line> hori;
        for (auto l : horitmp)
            if (ymin <= l.y0 && l.y0 <= ymax)
                hori.push_back(l);

        std::sort(hori.begin(), hori.end(), [](const auto& lhs, const auto& rhs) { return lhs.y0 < rhs.y0; });

        std::vector<uint16_t> current(size);
        mlock(current.data(), current.size() * sizeof current[0]);
        mlock(hori.data(), hori.size() * sizeof hori[0]);
        mlock(vert.data(), vert.size() * sizeof vert[0]);
        mlock(diag.data(), diag.size() * sizeof diag[0]);

#ifdef show_progress
        auto starttime = std::chrono::system_clock::now();
        auto onepercent = (ymax - ymin) / 100.f;
        auto nextprogress = ymin + onepercent;
#endif
        for (auto y = ymin; y < ymax; y++) {
#ifdef show_progress
            if (y > nextprogress) {
                auto now = std::chrono::system_clock::now();
                std::chrono::duration<double> elapsed = now - starttime;
                std::cout << "part2 thread " << idx
                          << " [" << ymin << "," << ymax << ") "
                          << ((y - ymin) / onepercent) << "% "
                          << elapsed.count() << "s" << std::endl;
                nextprogress += onepercent;
            }
#endif
            std::fill(current.begin(), current.end(), 0);

            // we can skip even more chunks of hori
            struct comp {
                bool operator()(const line& l, int y) const { return l.y0 < y; }
                bool operator()(int y, const line& l) const { return y < l.y0; }
            };
            auto [hbegin, hend] = std::equal_range(hori.begin(), hori.end(), y, comp{});
            for (auto it = hbegin; it != hend; it++) {
                auto [x0, y0, x1, y1] = *it; // y0 and y1 ignored
                for ( ; x0 <= x1; x0++)
                    current[x0]++;
            }

            for (auto [x0, y0, x1, y1] : vert) {
                if (y0 <= y && y <= y1) // x1 ignored
                    current[x0]++;
            }

            for (auto [x0, y0, x1, y1] : diag) {
                int dx = std::clamp(x1 - x0, -1, 1);
                if ((y0 <= y && y <= y1) || (y1 <= y && y <= y0))
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
