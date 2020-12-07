#include <cstddef>
#include <functional>
#include <iostream>
#include <string>
#include <cstdint>
#include <algorithm>
#include <sstream>
#include <vector>
#include <array>
#include <set>
#include <map>
#include <functional>
#include <regex>

int main() {

    std::string line{};
    while (std::getline(std::cin, line)){
        auto re_min = std::regex("(.*) contain [0-9]+ ([^,\\.]*)");
        auto re_extra = std::regex(", [0-9]+ ([^,\\.]*)[.\\,]");

        std::smatch match_min{}; 
        std::regex_search(line, match_min, re_min);
        std::cout << match.size() << " " << match[1] << " " << match[2] << std::endl;

        while (!line.empty()) {
            std::smatch match_min{}; 
            std::regex_search(line, match_min, re_min);
            std::cout << match.size() << " " << match[1] << " " << match[2] << std::endl;
        }
    }
    return 0;
}
