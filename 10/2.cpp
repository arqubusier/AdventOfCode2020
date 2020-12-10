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

using u64 = std::uint64_t;
using Adapters = std::vector<u64>;

u64 ValidRemovals(Adapters::iterator begin, Adapters:iterator end) {
}

int main() {
    // include charging port
    Adapters adapters{0};
    u64 num{};
    while (std::cin >> num) {
        adapters.push_back(num);
    }

    std::sort(adapters.begin(), adapters.end());
    // include device
    adapters.push_back(*adapters.rbegin() + 3);

    Adapters differences{adapters};
    std::adjacent_difference(adapters.begin(), adapters.end(), differences.begin());

    // Start with the longest valid chain
    // It's only possible to remove adapters where the difference is one
    // For each chain of adapters where all the differences are one.
    // Find the number of combinations of adapters that can be removed.
    u64 total = 1;
    Adapters::iterator ones_start = Adapters.begin();
    Adapters::iterator ones_end = Adapters.end();
    while (true) {
        ones_end++;
        if (ones_end == adapters.end()) {
            u64 combinations = ValidRemovals(ones_start, ones_end);
            std::cout << combinations << std::endl;
            total *= combinations;
            break;
        }

        if (*ones_end != 1) {
            if (ones_chain > 0) {
                u64 combinations = ValidRemovals(ones_start, ones_end);
                std::cout << combinations << std::endl;
                total *= combinations;
            }
            ones_start = ones_end + 1;
        }
    }

    std::cout << total << std::endl;

    return 0;
}
