#include "day.hpp"

namespace {
struct wire {
    std::array<char, 4> name = {};
    int value; // -1 if not set

    wire(std::string s, int val = -1) {
        if (std::isdigit(s[0])) {
            name = { 'v', 'a', 'l', 'u' };
            value = std::stoi(s);
        }
        else {
            s.resize(name.size());
            std::copy(s.begin(), s.end(), name.data());
            value = val;
        }
    }
    // we only ever want to look up by name
    auto operator<=>(const wire& rhs) const {
        return name <=> rhs.name;
    }
    [[maybe_unused]] friend std::ostream& operator<<(std::ostream& os, const wire& w) {
        os << "{ name=" << std::string{w.name.data(), w.name.size()}.data() << ", value=" << w.value << " }";
        return os;
    }
};

wire nowire("null");

struct op {
    mutable wire lhs = nowire, rhs = nowire, out = nowire;
    enum { Assign, Not, And, Or, Lshift, Rshift } type;
    inline static const std::vector<std::string> names {
        "\x1b[33mAssign\x1b[m",
        "\x1b[34mNot\x1b[m",
        "\x1b[35mAnd\x1b[m",
        "\x1b[35mOr\x1b[m",
        "\x1b[36mLshift\x1b[m",
        "\x1b[36mRshift\x1b[m",
    };

    op(const std::vector<std::string>& vec) {
        if (vec.size() == 3) {
            lhs = {vec[0]};
            out = {vec[2]};
            type = Assign;
        }
        else if (vec[0] == "NOT") {
            rhs = {vec[1]};
            out = {vec[3]};
            type = Not;
        }
        else {
            lhs = {vec[0]};
            rhs = {vec[2]};
            out = {vec[4]};
            type = vec[1] == "AND"    ? And     :
                   vec[1] == "OR"     ? Or      :
                   vec[1] == "LSHIFT" ? Lshift  : Rshift;
        }
    }
    bool operator<(const op& arg) const {
        return     type < arg.type ? true :
               arg.type < type     ? false:
                   lhs  < arg.lhs  ? true :
               arg.lhs  < lhs      ? false:
                   rhs  < arg.rhs  ? true :
               arg.rhs  < rhs      ? false:
               out      < arg.out;
    }
    [[maybe_unused]] friend std::ostream& operator<<(std::ostream& os, const op& o) {
        os << "{ type=" << o.names[o.type] << ", lhs=" << o.lhs << ", rhs=" << o.rhs << ", out=" << o.out << " }";
        return os;
    }
};

std::set<op> instructions;
}

ret day::part1() {
    /* it's a set of instructions in which the order doesn't really matter,
     * but we can only proceed by doing operations on known values */

    std::set<wire> known;
    if (instructions.empty()) {
        for (auto l : input) {
            auto i = op{split(l)};
            instructions.insert(i);
        }
    }
    auto target = wire{"a"};
    auto instr = instructions;
    while (!known.contains(target)) {
        for (auto i : instr) {
            auto lhs = known.find(i.lhs);
            if (i.lhs.value == -1 && lhs != known.end())
                i.lhs.value = lhs->value;

            auto rhs = known.find(i.rhs);
            if (i.rhs.value == -1 && rhs != known.end())
                i.rhs.value = rhs->value;

            if (i.type == op::Assign && i.lhs.value != -1) {
                i.out.value = i.lhs.value;
            }
            else if (i.type == op::Not && i.rhs.value != -1) {
                uint16_t val = i.rhs.value;
                val = ~val;
                i.out.value = val;
            }
            else if (i.lhs.value != -1 && i.rhs.value != -1) {
                i.out.value = i.type == op::And    ? i.lhs.value &  i.rhs.value :
                              i.type == op::Or     ? i.lhs.value |  i.rhs.value :
                              i.type == op::Lshift ? i.lhs.value << i.rhs.value :
                                                     i.lhs.value >> i.rhs.value;
            }
            else continue;

            known.insert(i.out);
            instr.erase(i);
        }
    }
    return known.find(target)->value;
}

ret day::part2() {
    auto b = wire{"b", std::get<int>(part1())};
    for (auto it = instructions.begin(); it != instructions.end(); ++it) {
        if ((it->lhs <=> b) == 0) {
            it->lhs.value = b.value;
        }
        if ((it->rhs <=> b) == 0) {
            it->rhs.value = b.value;
        }
    }
    return part1();
}
