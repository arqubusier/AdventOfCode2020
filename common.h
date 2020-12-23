#include <string>
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

bool IsBlank(std::string const& str) {
    return (std::string::npos == str.find_first_not_of(" \n\t"));
}

using u64 = std::uint64_t;

void DiscardSpace() {
    for (char c; std::cin.peek() == ' '; std::cin.get(c)) {}
}
