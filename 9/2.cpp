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
#include <numeric>

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
    int const kTarget{90433990};
    //int const kTarget{127};
    int num{};
    while (std::cin >> num) {
        history.push_back(num);
    }

    History::iterator start = history.begin();
    History::iterator end = start + 1;

    while (true) {
        int sum = std::accumulate(start, end + 1, 0);

        if (start == history.end()) {
            std::cout <<  "None found " << std::endl;
            break;
        } else if (kTarget == sum) {
            break;
        } else if (kTarget < sum) {
            start++;
            end = start + 1;
        } else {
            end++;
        }
    }

    auto min_it = std::min_element(start, end);
    auto max_it = std::max_element(start, end);
    int min = *min_it;
    int max = *max_it;
    std::cout << min << " " << max << " " << min + max  << std::endl;
    return 0;
}
