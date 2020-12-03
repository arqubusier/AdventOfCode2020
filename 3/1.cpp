#include <cstddef>
#include <functional>
#include <iostream>
#include <string>
#include <cstdint>
#include <algorithm>
#include <vector>

using MapType = std::vector<std::string>;
struct Stride {std::uint64_t x; std::uint64_t y;};

std::uint64_t TreeCount(MapType const &map, Stride const &stride) {
    std::uint64_t x_stride = stride.x;
    std::uint64_t y_stride = stride.y;
    std::uint64_t x_max = map[0].size();
    std::uint64_t x=0;
    std::uint64_t y=0;
    std::uint64_t tree_count=0;

    for (;;) {
        y += y_stride;
        if (map.size() <= y) {
            break;
        }
        x += x_stride;
        x %= x_max;

        if (map[y][x] == '#') ++tree_count;
    }

    return tree_count;
}

int main(int argc, char* argv[]) {
    std::vector<std::string> map{};

    for (std::string row{}; std::cin >> row ; map.push_back(row)) {
    }

    for (auto row: map) {
        std::cout << row << std::endl;
    }

     
    std::vector<Stride> strides {
        {1,1},
        {3,1},
        {5,1},
        {7,1},
        {1,2}
    };

    std::uint64_t product = TreeCount(map, strides[0]);
    strides.erase(strides.begin());
    for (auto stride : strides) {
        std::uint64_t tree_count = TreeCount(map, stride);
        std::cout << "tree_count " << tree_count << std::endl;
        product *= tree_count;
    }


    std::cout << "product " << product << std::endl;
    return 0;
}
