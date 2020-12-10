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

int main() {
    // include charging port
    std::vector<int> adapters{0};
    int num{};
    while (std::cin >> num) {
        adapters.push_back(num);
    }

    std::sort(adapters.begin(), adapters.end());
    // include device
    adapters.push_back(*adapters.rbegin() + 3);

    std::vector<int> differences{adapters};

    std::adjacent_difference(adapters.begin(), adapters.end(), differences.begin());
    auto ones = std::count(differences.begin(), differences.end(), 1);
    auto threes = std::count(differences.begin(), differences.end(), 3);
    std::cout << ones << " " << threes << " " << ones*threes << std::endl;
    return 0;
}
