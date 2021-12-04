#include "day.hpp"

constexpr int size = 5;
class board {
    int bingo[size][size];
    int colhits[size] = {0}, rowhits[size] = {0};

   public:
    board(const std::vector<std::string>& vec, size_t from) {
        for (auto i = 0u; i < size; i++) {
            auto nums = split<int>(vec[i+from]);
            for (auto j = 0; j < size; j++)
                bingo[i][j] = nums[j];
        }
    }

    auto sum() {
        int sum = 0;
        for (auto i = 0; i < size; i++)
            for (auto j = 0; j < size; j++)
                sum += bingo[i][j] == -1 ? 0 : bingo[i][j];
        return sum;
    }

    bool playnum(int n) {
        for (auto i = 0; i < size; i++) {
            for (auto j = 0; j < size; j++) {
                if (bingo[i][j] == n) {
                    bingo[i][j] = -1;

                    // only check if we won after finding the right cell
                    if (++colhits[i] == size) return true;
                    if (++rowhits[j] == size) return true;
                    return false;
                }
            }
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
