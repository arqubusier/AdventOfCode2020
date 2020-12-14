#include <iostream>
#include <cstdint>
#include <string>
#include <vector>

using u64 = std::uint64_t;


int main() {
    u64 mask0 = -1;
    u64 mask1 = 0;

    std::string mask;
    std::cin >> mask >> mask >> mask;
    std::cout << mask << std::endl;

    u64 offset = mask.size() - 1;
    for (char c: mask) {
        u64 val = 0;
        switch (c) {
            case 'X':
                break;
            case '0':
                val = ~(1 << offset);
                mask0 &= val;
                break;
            case '1':
                val = 1 << offset;
                mask1 |= val;
                break;
        }
        offset--;
    }
    std::cout << mask0 << std::endl;
    std::cout << mask1 << std::endl;

    std::vector<u64> mem;

    std::string address;
    while (std::cin >> address) {
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
    }
    return 0;
}
