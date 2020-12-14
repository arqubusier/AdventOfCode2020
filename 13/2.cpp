#include "../common.h"

struct Bus {
    std::uint64_t id;
    std::uint64_t offset;
};

using Buses = std::vector<Bus>;

u64 GoldCoin(Bus const &bus, u64 t_start, u64 period) {
    u64 t = t_start;
    while (true) {
        u64 expected = t + bus.offset;
        // Is this a time when the bus would arrive?
        if ( ((expected % bus.id) == 0) && (expected >= bus.id)) {
            break;
        }
        t += period;
    }
    return t;
}

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

    u64 common_period = 1;
    u64 t = 0;
    auto bus = buses.begin();
    for (; bus  < buses.end(); bus++) {
        // Use the property that the smallest combined period is LCM(period1, ..., periodN).
        // For this input we are only using prime numbers, so LCM will just be multiplications.
        // We can reuse the starting point from the last iteration, since that is known to work for the
        // previous buses.
        t = GoldCoin(*bus, t, common_period);
        common_period *= bus->id;
    }

    std::cout << t << std::endl;

    return 0;
}
