#include <regex>
#include "day.hpp"
ret day::part1() {
    auto s = input[0];
    std::regex num("-?[0-9]+");
    auto num_begin = std::sregex_iterator(s.begin(), s.end(), num);
    auto num_end = std::sregex_iterator();

    int sum = 0;
    for (auto it = num_begin; it != num_end; ++it) {
        sum += std::stoi(it->str());
    }
    return sum;
}

namespace {
// quick hacky parser for the subset of json needed for part 2
struct json {
    std::string type = "base";
    virtual int sum() = 0;
    virtual ~json() = default;
};

struct num : json {
    std::string type = "num";
    int value;
    num(int v) : value(v) {}
    virtual int sum() { return value; }
};

struct str : json {
    std::string type = "str";
    std::string value;
    str(std::string v) : value(v) {}
    virtual int sum() { return 0; }
};

struct arr : json {
    std::string type = "arr";
    std::vector<std::shared_ptr<json>> content;
    virtual int sum() {
        int total = 0;
        for (auto ptr : content)
            total += ptr->sum();
        return total;
    }
};

struct obj : json {
    std::string type = "obj";
    std::map<std::shared_ptr<json>, std::shared_ptr<json>> content;
    virtual int sum() {
        int total = 0;
        for (auto [k, v] : content) {
            auto derived = v.get();
            auto pstr = dynamic_cast<str*>(derived);
            if (pstr && pstr->value == "red")
                return 0;
            total += v->sum();
        }
        return total;
    }
};

std::shared_ptr<json> parse(const std::string& data, size_t& pos) {
    switch (data[pos]) {
        case '"': {
            auto start = pos + 1;
            auto end = start;
            for ( ; data[end] != '"'; end++) ; // includes trailing "
            auto parsed = std::string{data, start, end - start};
            pos = end + 1; // the next position to parse
            return std::make_shared<str>(parsed);
        }
        case '-':
        case '0': case '1': case '2': case '3': case '4':
        case '5': case '6': case '7': case '8': case '9': {
            // call strtol manually because stoi takes a std::string
            const char *start = data.data() + pos;
            char *end;
            int parsed = std::strtol(start, &end, 0);
            pos += end - start;
            return std::make_shared<num>(parsed);
        }
        case '{': {
            obj parsed;
            pos++; // skip {
            while (data[pos] != '}') {
                auto key = parse(data, pos);
                pos++; // skip :
                auto value = parse(data, pos);
                parsed.content[key] = value;
                if (data[pos] == ',')
                    pos++;
            }
            pos++; // skip }
            return std::make_shared<obj>(parsed);
        }
        case '[': {
            arr parsed;
            pos++; // skip [
            while (data[pos] != ']') {
                auto value = parse(data, pos);
                parsed.content.push_back(value);
                if (data[pos] == ',')
                    pos++;
            }
            pos++; // skip ]
            return std::make_shared<arr>(parsed);
        }
    }
    return std::make_shared<num>(0); // not reached
}
}

ret day::part2() {
    auto s = input[0];

    size_t pos = 0;
    auto parsed = parse(s, pos);
    return parsed->sum();
}
