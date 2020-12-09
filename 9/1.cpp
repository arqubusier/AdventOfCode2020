#include <cstddef>
#include <functional>
#include <iostream>
#include <string>
#include <cstdint>
#include <algorithm>
#include <sstream>
#include <vector>
#include <array>
#include <list>
#include <set>
#include <map>
#include <functional>
#include <regex>

using History = std::vector<int>;

bool XmasValid(History const &history, int num) {
    bool res = false;

    for (std::size_t i = 0; i < history.size(); ++i) {
        for (std::size_t j = 0; j < history.size(); ++j) {
            if (i == j) {
                continue;
            }
            if (num == (history[i] + history[j])) {
                res = true;
                break;
            }
        }
    }
    return res;
}

int main() {
    History history{};

    int num{};
    while (std::cin >> num) {
        history.push_back(num);
        if (history.size() == 25) {
            break;
        }
    }


    while (std::cin >> num) {
        if (!XmasValid(history, num)) {
            break;
        }

        history.erase(history.begin());
        history.push_back(num);
    };

    std::cout << num << std::endl;
    return 0;
}
