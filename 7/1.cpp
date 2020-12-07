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


using ChildrenT = std::list<std::string>;
using RulesT = std::map<std::string, ChildrenT>;

void EventuallyContains(RulesT const& rules, std::string const &containee, std::set<std::string> &containers) {
    auto rule{rules.find(containee)};

    if (rule != rules.end()) {
        for (auto container: rule->second) {
            containers.insert(container);
            EventuallyContains(rules, container, containers);
        }
    }
}

int main() {

    std::string line{};
    RulesT rules{};
    while (std::getline(std::cin, line)){
        auto re_min = std::regex("(.*?) bags? contain [0-9]+ (.*?) bags?");
        auto re_rest = std::regex(", [0-9]+ (.*?) bags?");
        auto re_skip = std::regex("(.*?) bags? contain no other bags.");

        if (std::regex_match(line, re_skip)) {
            std::cout << " skip " << std::endl;
            continue;
        }

        std::smatch match_min{}; 
        std::regex_search(line, match_min, re_min);
        std::string container{match_min[1]};
        std::string containee{match_min[2]};
        rules[containee].push_back(container);
        std::cout << container << "," << containee << std::endl;

        std::string remainder{match_min.suffix()};
        while (remainder != ".") {
            std::smatch match_rest{}; 
            std::regex_search(remainder, match_rest, re_rest);
            std::string containee{match_rest[1]};
            rules[containee].push_back(container);
            remainder = match_rest.suffix();
            std::cout << "-" << containee << std::endl;
        }
    }
    
    std::set<std::string> containers;
    EventuallyContains(rules, "shiny gold", containers);
    std::cout << containers.size() << std::endl;
    return 0;
}
