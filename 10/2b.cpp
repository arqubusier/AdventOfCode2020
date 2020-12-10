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

bool ValidAdapter(Adapters::iterator first, Adapters::iterator second) {
    return 3 >= (*second - *first);
}
u64 Combinations(Adapters::iterator first, Adapters::iterator rest, Adapters::iterator end) {
    if (rest == end) {
        return 1;
    }

    u64 sum = 0;
    Adapters::iterator other = rest;
    for (; ValidAdapter(first, other) && other != end; other++) {
        sum += Combinations(other, other+1, end);
    }
    return sum;
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

    u64 total = Combinations(adapters.begin(), adapters.begin() + 1, adapters.end());


    std::cout << total << std::endl;

    return 0;
}
