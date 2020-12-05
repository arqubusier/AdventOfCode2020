#include <cstddef>
#include <functional>
#include <iostream>
#include <string>
#include <cstdint>
#include <algorithm>
#include <sstream>
#include <vector>
#include <array>
#include <set>
#include <map>
#include <functional>
#include <regex>

int Num(std::string const &line, int step_init, char lower, char upper) {
    int step{step_init};
    int res{0};
    for (char c : line) {
        if (c == upper) {
            res += step;
        }
        step /= 2;
    }
    return res;
}

int main() {
    int id_max{0};
    std::vector<int> ids{};
    std::string line;

    while (std::cin >> line) {
        int row{Num(line.substr(0, 7), 64, 'F', 'B')};
        int col{Num(line.substr(7), 4, 'L', 'R')};
        int id{row * 8 + col};
        id_max = std::max(id_max, id);
        ids.push_back(id);
    }

    std::sort(ids.begin(), ids.end());
    for (int i = 1; i < ids.size(); ++i) {
        int id{ids[i]};
        if (1 < (id - ids[i-1])) {
            std::cout << id-1 << std::endl;
        }
    }

    std::cout << id_max << std::endl;

    return 0;
}
