#include "../common.h"


int const A = -1;
int const B = -2;
using SubRules = std::vector<std::vector<int>>;
using Rules = std::vector<SubRules>;

bool Valid(std::string::iterator &in, Rules const &rules, std::size_t rule_start) {
    SubRules sub_rules = rules[rule_start];
    for (auto sub_rule: sub_rules) {
        // Assume that "a" and "b" appear alone
        if (sub_rule[0] == A) {
            if (*in == 'a') {
                in++;
                return true;
            }
            return false;
        } else if (sub_rule[0] == B) {
            if (*in == 'b') {
                in++;
                return true;
            }
            return false;
        }

        // Try rule on iterator copy in case of mismatch
        // Only update iterator if rule mathces
        std::string::iterator in_copy = in;
        bool match = true;
        for (int rule: sub_rule) {
            if (!Valid(in_copy, rules, static_cast<std::size_t>(rule))) {
                    match = false;
                    break;
            }
        }
        if (match) {
            in = in_copy;
            return true;
        }
    }
    return false;
}

int main() {
    Rules rules{};
    std::string line;
    // Setup rules
    while (true) {
        std::getline(std::cin, line);
        if (IsBlank(line)) {
            break;
        }
        std::stringstream ss{line};

        std::size_t rule;
        char sep;
        ss >> rule >> sep;
        if (rule >= rules.size()) {
            rules.resize(rule + 1);
        }

        SubRules &subrules = rules[rule];
        subrules.emplace_back();
        std::string str;
        while (ss >> str) {
            if (str == "|") {
                subrules.emplace_back();
            } else if (str == "\"a\""){
                subrules.back().push_back(A);
            } else if (str == "\"b\""){
                subrules.back().push_back(B);
            } else {
                subrules.back().push_back(std::stoi(str));
            }
        }
    }

    int valid = 0;
    // Validate
    while (std::getline(std::cin, line)) {
        std::cout << line;
        std::string::iterator in = line.begin(); 
        // Manual soloution for problem input
        // Input must consist of At least two chunks of 42
        // followed by at least one chunk of 31 but less then the number of leading 42
        std::string test = "aabba";
        std::string::iterator in2 = test.begin();
        int y = 0;
        int x = 0;
        while ((in != line.end()) && Valid(in, rules, 42)) {
            y++;
        }
        while ((in != line.end()) && Valid(in, rules, 31)) {
            x++;
        }
        if ((in == line.end()) && (y > x) && (x > 0)) {
            valid++;
            std::cout << " valid";
        }
        std::cout << std::endl;
    }
    std::cout << valid << std::endl;
}
