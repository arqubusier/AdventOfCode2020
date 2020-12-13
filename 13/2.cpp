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
#include <climits>


struct Bus {
    std::uint64_t id;
    std::uint64_t offset;
};

using Buses = std::vector<Bus>;

int main() {
    std::uint64_t depart = 0;
    std::uint64_t offset = 0;
    std::cin >> depart;

    Buses buses{};
    while (true) {
        char sep = 0;

        if(std::cin.peek() == 'x') {
            std::cin >> sep;
        } else {
            std::uint64_t id;
            std::cin >> id;
            buses.push_back({id, offset});
        }

        offset++;
        if (!(std::cin >> sep)) {
            break;
        }
    }

    std::sort(buses.begin(), buses.end(), [](Bus const&a, Bus const&b){return a.id < b.id;});

    Bus slowest_bus = *buses.rbegin();
    std::uint64_t current = 0;
    std::uint64_t solution = 0;
    while (true) {
        auto bus = (buses.rbegin() + 1);
        bool found = true;
        current += slowest_bus.id;

        for (; bus != buses.rend(); bus++) {
            std::int64_t rel_offset = slowest_bus.offset - bus->offset;
            if (rel_offset > static_cast<std::int64_t>(current)) {
                found = false;
                break;
            }
            std::uint64_t expected =  current - rel_offset;
            if ((expected % bus->id) != 0) {
                found = false;
                break;
            }
        }

        if (found) {
            solution = current - slowest_bus.offset;
            break;
        }
    }

    std::cout << solution << std::endl;

    return 0;
}
