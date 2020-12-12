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

u64 tribonacci(u64 n) {
    if (n == 0)
        return 1;
    if (n == 1)
        return 1;
    if (n == 2)
        return 2;

    return tribonacci(n-1) + tribonacci(n-2) + tribonacci(n-3);
}

int main() {
    // include charging port
    std::vector<u64> adapters{0};
    u64 num{};
    while (std::cin >> num) {
        adapters.push_back(num);
    }

    std::sort(adapters.begin(), adapters.end());
    // include device
    adapters.push_back(*adapters.rbegin() + 3);

    std::vector<u64> differences{adapters};
    std::adjacent_difference(adapters.begin(), adapters.end(), differences.begin());

    u64 ones_chain = 0;
    u64 total = 1;
    
    // Combinations of chains of ones
    for (u64 diff: differences) {
        if (diff != 1) {
            if (ones_chain >= 2) {
                u64 combinations = tribonacci(ones_chain);
                std::cout << combinations << std::endl;
                total *= combinations;
            }
            ones_chain = 0;
        } else {
            ones_chain += 1;
        }
    }

    // Combinations of pairs of (2,1) (1,2)
    auto i1 = differences.begin();
    auto i2 = i1 + 1;
    for (;
                i2 != differences.end() ; ++i1, ++i2) {
        if ( (*i1 == 1 && *i2 == 2) || (*i1 == 2 && *i2 == 1) ) {
            u64 combinations = 2;
            std::cout << combinations << std::endl;
            total *= combinations;
        }
    }

    std::cout << total << std::endl;

    return 0;
}
