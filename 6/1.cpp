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
#include "../common.h"

void line_anyone(std::set<char> &unique, int &group, std::string const &line) {
    for (char c : line) {
        auto res = unique.insert(c);
        if (res.second) {
            group++;
        }
    }
}

int line_all(std::set<char> unique, std::string &line) {

}

int main() {
    int sum{0};
    int group{0};
    std::set<char> unique;
    std::string line{};
    while (std::getline(std::cin, line)) {
        if (!IsBlank(line)) {
#if 1
            line_anyone(unique, group, line);
#else
            line_all();
#endif
        }
        std::cout << line << std::endl;

        if (IsBlank(line) || (std::char_traits<char>::eof() == std::cin.peek())) {
            std::cout << group << std::endl;
            sum += group;
            group = 0;
            unique.clear();
        }
    }

    std::cout << sum << std::endl;
}
