#include "day.hpp"

constexpr int size = 5;
class board {
    int bingo[size][size];
    int colhits[size] = {0}, rowhits[size] = {0};
    std::unordered_map<int, std::pair<int,int>> map;

   public:
    board(const std::vector<std::string>& vec, size_t from) {
        for (auto i = 0; i < size; i++) {
            auto nums = split<int>(vec[i+from]);
            for (auto j = 0; j < size; j++) {
                bingo[i][j] = nums[j];
                map[nums[j]] = {i,j};
            }
        }
    }

    auto sum() {
        int sum = 0;
        for (auto i = 0; i < size; i++)
            for (auto j = 0; j < size; j++)
                sum += bingo[i][j];
        return sum;
    }

    bool playnum(int n) {
        auto it = map.find(n);
        if (it != map.end()) {
            auto [i, j] = it->second;
            bingo[i][j] = 0;
            if (++colhits[i] == size) return true;
            if (++rowhits[j] == size) return true;
        }
        return false;
    }
};

ret day::part1() {
    auto numbers = split<int>(input[0], ',');
    std::vector<board> boards;

    for (auto i = 2u; i < input.size(); i += size+1)
        boards.push_back(board{input, i});

    for (auto n : numbers) {
        for (auto& b : boards) {
            if (b.playnum(n)) // win!
                return b.sum() * n;
        }
    }
    return 0;
}
ret day::part2() {
    auto numbers = split<int>(input[0], ',');
    std::vector<board> boards;

    for (auto i = 2u; i < input.size(); i += size+1)
        boards.push_back(board{input, i});

    auto score = 0;
    for (auto n : numbers) {
        for (auto b = 0u; b < boards.size(); ) {
            if (boards[b].playnum(n)) {
                score = boards[b].sum() * n;
                boards.erase(boards.begin() + b);
            }
            else b++; // don't increase b if we removed an element
        }
    }
    return score;
}
