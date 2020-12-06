#include <cstddef>
#include <functional>
#include <iostream>
#include <string>
#include <cstdint>
#include <cstdio>
#include <algorithm>
#include <sstream>
#include <vector>
#include <array>
#include <set>
#include <map>
#include <functional>
#include <regex>
#include <iterator>
#include "../common.h"

//#define part1
#define part2

void line_anyone(std::set<char> &unique, int &group, std::string const &line) {
    for (char c : line) {
        auto res = unique.insert(c);
        if (res.second) {
            group++;
        }
    }
}

void line_all(std::string &intersection, std::string const &line, bool &reset_intersection) {
    std::string line_sorted = line;
    std::sort(line_sorted.begin(), line_sorted.end());
    if (reset_intersection) {
        intersection = line_sorted;
        reset_intersection = false;
    } else {
        std::string res{};
        std::set_intersection(intersection.begin(), intersection.end(), 
                line_sorted.begin(), line_sorted.end(), std::back_inserter(res));
        intersection = res;
    }
}

int main() {
    int sum{0};
    int group{0};
    std::set<char> unique;
    std::string line{};
    std::string intersection{};
    bool reset_intersection{true};

    while (std::getline(std::cin, line)) {
        std::string line_sorted = line;
        std::sort(line_sorted.begin(), line_sorted.end());
        std::cout << line_sorted << std::endl;

        if (!IsBlank(line)) {
#ifdef part1
            line_anyone(unique, group, line);
#else
            line_all(intersection, line, reset_intersection);
#endif
        }

        if (IsBlank(line) || (std::char_traits<char>::eof() == std::cin.peek())) {
#ifdef part1
#else
            group = intersection.size();
#endif
            sum += group;
            std::cout << group << " " << sum << std::endl;
            group = 0;
#ifdef part1
            unique.clear();
#else
            intersection.clear();
            reset_intersection = true;
#endif
        }
    }

    std::cout << sum << std::endl;
}
