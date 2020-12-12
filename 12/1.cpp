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

void move(int dir, int val, int &x, int &y) {
    switch (dir) {
        case 0:
            x += val;
            break;
        case 1:
            y += val;
            break;
        case 2:
            x -= val;
            break;
        case 3:
            y -= val;
            break;
        default:
            std::cout << "wrong dir " << dir << std::endl;
            std::abort();
    }
}

int main () {
    char command;
    int val;
    int x = 0;
    int y = 0;
    int dir = 0;
    while (std::cin >> command) {
        std::cin >> val;

        switch (command) {
            case 'E':
                move(0, val, x, y);
                break;
            case 'N':
                move(1, val, x, y);
                break;
            case 'W':
                move(2, val, x, y);
                break;
            case 'S':
                move(3, val, x, y);
                break;
            case 'L':
                dir = (dir + val/90 ) % 4;
                break;
            case 'R':
                dir = (dir + 4 - val/90) % 4;
                break;
            case 'F':
                move(dir, val, x, y);
                break;
            default:
                std::cout << "wrong command " << command << std::endl;
                std::abort();
        }
    }
    
    int d = std::abs(x) + std::abs(y);
    std::cout << x << " " << y << std::endl;
    std::cout << d << std::endl;
}
