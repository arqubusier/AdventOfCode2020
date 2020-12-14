#include <iostream>
#include <cstdint>
#include <string>
#include <vector>
#include <map>

using u64 = std::uint64_t;


void GetMasks(std::string mask, u64 &mask0, u64 &mask1) {
    u64 offset = mask.size() - 1;
    for (char c: mask) {
        switch (c) {
            case 'X':
                break;
            case '0': {
                mask0 &= ~(static_cast<u64>(1) << offset);
                break;
                      }
            case '1': {
                mask1 |= static_cast<u64>(1) << offset;
                break;
                      }
        }
        offset--;
    }
}
int main() {
    u64 mask0 = -1;
    u64 mask1 = 0;
    std::string mask, eq;
    std::map<u64,u64> mem;
    
    // get "mask"
    std::cin >> mask;
    // get " = "
    while (std::cin >> mask) {
        mask0 = -1;
        mask1 = 0;

        // get actual bitmask
        std::cin >> mask;
        GetMasks(mask, mask0, mask1);
        std::cout << std::hex << mask0 << std::endl;
        std::cout << std::hex << mask1 << std::endl;

        std::string address;
        while (std::cin >> address) {
            if (address == "mask") {
                break;
            }
            std::string index_str = address.substr(address.find('['));
            u64 index = std::stoi(index_str.substr(1));
            std::cout << "i   " << index << std::endl;
            u64 val = 0;
            std::string eq;
            std::cin >> eq >> val;

            std::cout << "    " << val << std::endl;
            val &= mask0;
            val |= mask1;
            std::cout << "res " << val << std::endl;
            mem[index] = val;
        }
    }

    u64 sum = 0;
    for (auto m: mem) {
        sum += m.second;
    }

    std::cout << std::dec << sum << std::endl;
    return 0;
}
