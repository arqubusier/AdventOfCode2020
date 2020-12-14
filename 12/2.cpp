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

void rotate(int dir, int &x, int &y) {
    int xp, yp;
    switch (dir) {
        case 0:
            break;
        case 1:
            xp = -y;
            yp = x;
            break;
        case 2:
            xp = -x;
            yp = -y;
            break;
        case 3:
            xp = y;
            yp = -x;
            break;
        default:
            std::cout << "wrong dir " << dir << std::endl;
            std::abort();
    }

    x = xp;
    y = yp;
}

int main () {
    char command;
    int val;
    int wx = 10;
    int wy = 1;
    int x = 0;
    int y = 0;
    while (std::cin >> command) {
        std::cin >> val;

        switch (command) {
            case 'E':
                move(0, val, wx, wy);
                break;
            case 'N':
                move(1, val, wx, wy);
                break;
            case 'W':
                move(2, val, wx, wy);
                break;
            case 'S':
                move(3, val, wx, wy);
                break;
            case 'L':
                rotate( (val/90 ) % 4, wx, wy);
                break;
            case 'R':
                rotate( (4 - val/90 ) % 4, wx, wy);
                break;
            case 'F':
                for (int i=0; i < val; i++) {
                    x += wx;
                    y += wy;
                }
                std::cout << "w " << wx << " " << wy << std::endl;
                std::cout << "  " << x << " " << y << std::endl;
                std::cout << "-------------" << std::endl;
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
