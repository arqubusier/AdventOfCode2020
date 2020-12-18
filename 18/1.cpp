#include "../common.h"

struct LhsExp {
    int lhs;
    char op;
};

using LhsExpressions = std::vector<LhsExp>;

int calc(LhsExp lhs, int rhs) {
    switch (lhs.op) {
        case '+':
            return lhs.lhs + rhs;
        case '*':
            return lhs.lhs * rhs;
        default:
            std::cout << "unknown op" << std::endl;
            std::abort();
            return 0;
    }
}

int main() {
    LhsExpressions saved{};
    int acc = 0;
    while(true) {
        // Find lhs
        for (char parens; std::cin.peek() == '('; std::cin >> parens) {}
        int lhs;
        if (!(std::cin >> lhs)) {
            break;
        }
        

        std::string opstr;
        std::cin >> opstr;

        // End of expression
        char next = std::cin.peek();
        if ( (next == ')') || (next == ' ') ) {
            auto exp = saved.back();
            saved.pop_back();
            acc = calc(exp, lhs);
            // consume left parentheses
            for (char parens; std::cin.peek() == ')'; std::cin >> parens) {}
        // Cannot compute result now
        } else if (next == '(') {
            saved.push_back({lhs, opstr[0]});
        } else {
            std::cout << "Unexpected input: " << next << std::endl;
            std::abort();
            return 1;
        }
    }
    
    std::cout << acc << std::endl;
    return 0;
}
