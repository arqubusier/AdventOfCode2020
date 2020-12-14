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

int main() {
    int depart = 0;
    int earliest = INT_MAX;
    int earliest_id = 0;
    std::cin >> depart;
    while (true) {
        char sep = 0;

        if(std::cin.peek() == 'x') {
            std::cin >> sep;
        } else {
            int id = 0;
            std::cin >> id;
            
            int current = 0;
            for (; current < depart; current += id) {}
            if (current < earliest) {
                earliest = current;
                earliest_id = id;
            }
        }

        if (!(std::cin >> sep)) {
            break;
        }
    }

    std::int64_t product = earliest_id * (earliest - depart);
    std::cout << earliest_id << " " << earliest << " " << product << std::endl;
    return 0;
}
