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

using Grid = std::vector<std::string>;

bool InBounds(Grid const& grid, int x, int y) {
    return !(x < 0 || static_cast<std::size_t>(x) >= grid[0].size()
            || y < 0 ||  static_cast<std::size_t>(y) >= grid.size());
}

bool Find(Grid const& grid, int x, int y, int dx, int dy, char target) {
    int xn = x;
    int yn = y;
    while (true) {
        xn += dx;
        yn += dy;
        if (!InBounds(grid, xn, yn)) {
            return false;
        } 
        char v = grid[yn][xn];
        if (v == '.') {
            continue;
        } else if ( v == target) {
            return true;
        } else {
            return false;
        }
    }
}

char Rule0(Grid const& grid, int x, int y) {
    if (grid[y][x] != 'L') {
        return grid[y][x];
    }
    for (int dx = -1; dx <= 1; dx++) {
        for (int dy = -1; dy <= 1; dy++) {
            if (dy == 0 && dx == 0) {
                continue;
            }
            if (Find(grid, x, y, dx, dy, '#')) {
                return 'L';
            }
        }
    }

    return '#';
}

char Rule1(Grid const& grid, int x, int y) {
    if (grid[y][x] != '#') {
        return grid[y][x];
    }
    int occupied=0;
    for (int dx = -1; dx <= 1; dx++) {
        for (int dy = -1; dy <= 1; dy++) {
            if (dy == 0 && dx == 0) {
                continue;
            }
            if (Find(grid, x, y, dx, dy, '#')) {
                occupied++;
            }
            if (occupied == 5) {
                return 'L';
            }
        }
    }

    return '#';
}

void Print(Grid const& grid) {
    for (std::size_t y=0; y < grid.size(); ++y) {
        for (std::size_t x=0; x < grid[0].size(); ++x) {
            std::cout << grid[y][x];
        }
        std::cout << std::endl;
    }
}

int NSeats(Grid const& grid) {
    int sum{0};
    for (std::size_t y=0; y < grid.size(); ++y) {
        for (std::size_t x=0; x < grid[0].size(); ++x) {
            if (grid[y][x] == '#') {
                sum++;
            }
        }
    }
    return sum;
}

int main() {
    std::string line{};
    Grid grid;
    while (std::cin >> line) {
       grid.push_back(line);
    }
    
    std::function<char(Grid const&, int, int)> rule = Rule0;
    bool rule0 = true;
    bool change{false};
    int iter=0;
    do {
        Grid grid_prev = grid;
        change = false;
        for (std::size_t y=0; y < grid.size(); ++y) {
            for (std::size_t x=0; x < grid[0].size(); ++x) {
                char next = '#';
                char prev = grid_prev[y][x];

                if (prev == '.') {
                    continue;
                } else {
                    next = rule(grid_prev, x, y);
                }
                if (prev != next) {
                    grid[y][x] = next;
                    if (!change) {
                        change = true;
                    }
                }
            }
        }
        if (rule0) {
            rule = Rule1;
        } else {
            rule = Rule0;
        }
        rule0 = !rule0;

        iter++;
        std::cout << iter << std::endl;
        Print(grid);
    } while(change);
    std::cout << std::endl;

    Print(grid);
    std::cout << NSeats(grid) << std::endl;
    return 0;
}
