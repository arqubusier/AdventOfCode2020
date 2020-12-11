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

bool IsFree(Grid const& grid, int col, int row) {
    if (col >= 0 && col < grid[0].size() && row >= 0 && row < grid.size()) {
        return grid[row][col] == 'L';
    }
    return false;
}

bool IsOccupied(Grid const& grid, int col, int row) {
    if (col < 0 || col >= grid[0].size() || row < 0 || row >= grid.size()) {
        return false;
    }
    return grid[row][col] == '#';
}

bool Rule0Occupy(Grid const& grid, int col, int row) {
    if (IsOccupied(grid, col-1, row)) {
        return false;
    } else if (IsOccupied(grid, col+1, row)) {
        return false;
    } else if (IsOccupied(grid, col, row+1)) {
        return false;
    } else if (IsOccupied(grid, col-1, row)) {
        return false;
    }
    return true;
}

bool Rule1Occupy(Grid const& grid, int col, int row) {
    if (!IsOccupied(grid, col-1, row)) {
        return true;
    } else if (!IsOccupied(grid, col+1, row)) {
        return true;
    } else if (!IsOccupied(grid, col, row+1)) {
        return true;
    } else if (!IsOccupied(grid, col-1, row)) {
        return true;
    }
    return false;
}

void Print(Grid const& grid) {
    for (int row=0; row < grid[0].size(); ++row) {
        for (int col=0; col < grid[0].size(); ++col) {
            std::cout << grid[row][col];
        }
        std::cout << std::endl;
    }
}

int NSeats(Grid const& grid) {
    int sum{0};
    for (int row=0; row < grid[0].size(); ++row) {
        for (int col=0; col < grid[0].size(); ++col) {
            if (IsOccupied(grid, col, row)) {
                sum++;
            }
        }
    }
    return sum;
}

int main() {
    std::string line{};
    Grid grid;
    Grid grid_prev;
    while (std::cin >> line) {
       grid.push_back(line);
    }
    
    std::function<bool(Grid const&, int, int)> rule = Rule0Occupy;
    bool rule0 = true;
    bool change{false};
    int iter=0;
    do {
        Grid grid_prev = grid;
        change = false;
        for (int row=0; row < grid[0].size(); ++row) {
            for (int col=0; col < grid[0].size(); ++col) {
                char next = '#';
                char prev = grid_prev[row][col];

                if (prev == '.') {
                    continue;
                } else if (rule(grid, col, row)) {
                    next = '#';
                } else {
                    next = 'L';
                }
                if (prev != next) {
                    grid[row][col] = next;
                    change = true;
                }
            }
        }
        if (rule0) {
            rule = Rule1Occupy;
        } else {
            rule = Rule0Occupy;
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
