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

struct ContainerCount{
    int count;
    std::string container;
};

using ChildrenT = std::list<ContainerCount>;
using RulesT = std::map<std::string, ChildrenT>;

int NContainers(RulesT const& rules, std::string const &containee) {
    int res{1};
    auto rule{rules.find(containee)};

    if (rule != rules.end()) {
        for (auto container_count: rule->second) {
            res += container_count.count * NContainers(rules, container_count.container);
        }
    }
    return res;
}

int main() {

    std::string line{};
    RulesT rules{};
    while (std::getline(std::cin, line)){
        auto re_min = std::regex("(.*?) bags? contain ([0-9]+) (.*?) bags?");
        auto re_rest = std::regex(", ([0-9]+) (.*?) bags?");
        auto re_skip = std::regex("(.*?) bags? contain no other bags.");

        if (std::regex_match(line, re_skip)) {
            std::cout << " skip " << std::endl;
            continue;
        }

        std::smatch match_min{}; 
        std::regex_search(line, match_min, re_min);
        std::string container{match_min[1]};
        int count{std::stoi(match_min[2])};
        std::string containee{match_min[3]};
        rules[container].push_back({count, containee});
        std::cout << container << "," << count << " " << containee << std::endl;

        std::string remainder{match_min.suffix()};
        while (remainder != ".") {
            std::smatch match_rest{}; 
            std::regex_search(remainder, match_rest, re_rest);
            int count{std::stoi(match_rest[1])};
            std::string containee{match_rest[2]};
            rules[container].push_back({count, containee});
            remainder = match_rest.suffix();
            std::cout << "-" << count << " " << containee << std::endl;
        }
    }
    
    int count = NContainers(rules, "shiny gold");
    std::cout << count - 1 << std::endl;
    return 0;
}
