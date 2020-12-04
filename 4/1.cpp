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

bool IsBlank(std::string const& str) {
    return str.find_first_not_of(" \n\t");
}

bool IsValidPassport(std::string const& str) {
    std::vector<std::string> valids{"byr", "iyr", "eyr", "hgt", "hcl", "ecl", "pid", "cid"};

    for (auto valid : valids) {
        if (0 == valid.compare(0, 3, str)) {
            return true;
        }
    }
    return false;
}

int main(int argc, char* argv[]) {
    std::uint32_t valid = 0;
    std::string line{};
    std::set<std::string> all_keys{"byr", "iyr", "eyr", "hgt", "hcl", "ecl", "pid"};
    std::set<std::string> remaining{all_keys};
    while (std::getline(std::cin, line)){
        if (IsBlank(line)) {
            if (remaining.empty()) {
                std::cout << "valid-------------------" << std::endl;
                ++valid;
            } else {
                std::cout << "invalid-----------------" << std::endl;
                for (auto rem : remaining) {
                    std::cout << rem << " ";
                }
                std::cout << std::endl;
                std::cout << "invalid-----------------" << std::endl;
            }
            remaining = all_keys;
        } else {
            std::stringstream ss{line};
            std::string key_val;
            while (ss >> key_val) {
                std::string key{key_val.substr(0, 3)};
                remaining.erase(key);
            }
            std::cout << line << std::endl;
        }
    }

    if (remaining.empty()) {
        std::cout << "valid-------------------" << std::endl;
        ++valid;
    }

    std::cout << "valid " << valid << std::endl;
    return 0;
}
