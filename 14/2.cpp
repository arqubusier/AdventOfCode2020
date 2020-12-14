#include <iostream>
#include <cstdint>
#include <string>
#include <vector>
#include <map>
#include "../common.h"

using u64 = std::uint64_t;
using BitList = std::vector<std::size_t>;
using Memory = std::map<u64,u64>;

void GetMasks(std::string mask, u64 &mask1, BitList &bit_list) {
    u64 offset = mask.size() - 1;
    for (char c: mask) {
        switch (c) {
            case 'X':
                bit_list.push_back(offset);
                break;
            case '0': {
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

void WriteAllFloating(u64 address_in, u64 val, Memory &mem, BitList &bit_list) {
    // 1 << n-1 == "2 to the n"
    u64 combination_digits = bit_list.size();
    u64 last_combination = (1 << combination_digits) - 1;
    for (u64 combination = 0; combination <= last_combination; combination++) {
        u64 address = address_in;
        for (std::size_t combination_i = 0; combination_i < combination_digits; combination_i++) {
            u64 bit = static_cast<u64>(1) & (combination >> combination_i);
            if (bit == 0) {
                u64 bit_mask =  ~(1 << bit_list[combination_i]);
                address &= bit_mask;
            } else {
                u64 bit_mask = 1 << bit_list[combination_i];
                address |= bit_mask;
            }
        }
        std::cout << " c " << combination << " a " << address << std::endl;
        mem[address] = val;
    } 
}

int main() {
    Memory mem{};
    std::string mask, eq;
    
    // get "mask"
    std::cin >> mask;
    // get " = "
    while (std::cin >> mask) {
        u64 mask1 = 0;
        BitList bit_list{};

        // get actual bitmask
        std::cin >> mask;
        GetMasks(mask, mask1, bit_list);

        std::string address;
        while (std::cin >> address) {
            if (address == "mask") {
                break;
            }
            std::string index_str = address.substr(address.find('['));
            u64 address = std::stoi(index_str.substr(1));
            u64 val = 0;
            std::string eq;
            std::cin >> eq >> val;
            std::cout << std::dec << val << std::endl;

            address |= mask1;
            std::cout << std::dec << val << std::endl;
            WriteAllFloating(address, val, mem, bit_list);
        }
    }

    u64 sum = 0;
    for (auto m: mem) {
        sum += m.second;
    }

    std::cout << std::dec << sum << std::endl;
    return 0;
}
