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

template<int lower, int higher>
bool ValidInterval(std::string const& val) {
    int i = std::stoi(val);
    return (val.size() == 4) && (i >= lower) && (i <= higher);
}

int Height(std::string const& val) {
    auto re = std::regex("([0-9]+)(in|cm)");
    std::smatch match{}; 
    if (std::regex_match(val, match, re)) {
        int i = std::stoi(match[1]);
        if (match[2] == "cm") {
            return (150 <= i) && (193 >= i);
        } else {
            return (59 <= i) && (76 >= i);
        }
    } else {
        return false;
    }
}

int main(int argc, char* argv[]) {
    std::uint32_t valid = 0;
    std::string line{};
    KeySet all_keys{"byr", "iyr", "eyr", "hgt", "hcl", "ecl", "pid"};
    KeyValidators validators{
        {"byr", ValidInterval<1920,2002>},
        {"iyr", ValidInterval<2010,2020>},
        {"eyr", ValidInterval<2020,2030>},
        {"hgt", Height},
        {"hcl", [](std::string const& val)-> bool {
                auto re = std::regex("#[0-9a-f][0-9a-f][0-9a-f][0-9a-f][0-9a-f][0-9a-f]");
                return std::regex_match(val, re);
            }
        },
        {"ecl", [](std::string const& val)-> bool {
                auto re = std::regex("(amb|blu|brn|gry|grn|hzl|oth)");
                return std::regex_match(val, re);
            }
        },
        {"pid", [](std::string const& val)-> bool {
                auto re = std::regex("[0-9][0-9][0-9][0-9][0-9][0-9][0-9][0-9][0-9]");
                return std::regex_match(val, re);
            }
        },
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
