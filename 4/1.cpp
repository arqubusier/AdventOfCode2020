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

using KeySet = std::set<std::string>;
using KeyValidators = std::map<std::string, std::function<bool(std::string const&)>>;

bool IsBlank(std::string const& str) {
    return str.find_first_not_of(" \n\t");
}



void UpdateKeys(KeyValidators const &validators, std::set<std::string> &remaining, std::string const &line) {
    std::stringstream ss{line};
    std::string key_val;
    while (ss >> key_val) {
        std::string key{key_val.substr(0, 3)};
        std::string val{key_val.substr(4)};
        if (validators.at(key)(val)) {
            remaining.erase(key);
        }
    }
    std::cout << line << std::endl;
}

int main(int argc, char* argv[]) {
    std::uint32_t valid = 0;
    std::string line{};
    KeySet all_keys{"byr", "iyr", "eyr", "hgt", "hcl", "ecl", "pid"};
    KeyValidators validators{
        {"byr", [](std::string const& val)-> bool {
                      int i = std::stoi(val);
                      return (i >= 1920) && (i <= 2020);}},
        {"iyr", [](std::string const& val)-> bool {return true;}},
        {"eyr", [](std::string const& val)-> bool {return true;}},
        {"hgt", [](std::string const& val)-> bool {return true;}},
        {"hcl", [](std::string const& val)-> bool {return true;}},
        {"ecl", [](std::string const& val)-> bool {return true;}},
        {"pid", [](std::string const& val)-> bool {return true;}},
        {"cid", [](std::string const&)-> bool {return true;}}
    };

    KeySet remaining{all_keys};
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
            UpdateKeys(validators, remaining, line);
        }
    }

    if (remaining.empty()) {
        std::cout << "valid-------------------" << std::endl;
        ++valid;
    }

    std::cout << "valid " << valid << std::endl;
    return 0;
}
