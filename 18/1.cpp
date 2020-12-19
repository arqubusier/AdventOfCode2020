#include "../common.h"

struct LhsExp {
    u64 lhs;
    char op;
    std::size_t level; //parentheses level
};

using LhsExpressions = std::vector<LhsExp>;

u64 calc(LhsExp lhs, u64 rhs) {
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

void DiscardSpace() {
    for (char c; std::cin.peek() == ' '; std::cin.get(c)) {}
}
int main() {
    u64 sum = 0;
    while (true) {
        LhsExpressions saved{};
        u64 lhs = 0;
        std::size_t parens_level = 0;
        
        
        // first operand
        for (char parens; std::cin.peek() == '('; std::cin >> parens) {
            parens_level++;
        }
        
        if (!(std::cin >> lhs)) {
            break;
        }

        // successive operads
        while(true) {
            char op;
            char next;
            DiscardSpace();
            std::cin.get(op);
            if ((!std::cin) || (op == '\n')) {
                std::cout << lhs << std::endl;
                sum += lhs;
                break;
            }
            std::cin >> next;
            LhsExp lhs_exp{lhs, op, parens_level};

            // Cannot compute result now
            // Start over with a new rhs value.
            if ( next == '(') {
                saved.push_back(lhs_exp);
                parens_level++;
                for (char parens; std::cin.peek() == '('; std::cin >> parens) {
                    parens_level++;
                }

                std::cin >> lhs;
            // lhs and rhs are numbers -> compute result now
            // Finish all expressions that were waiting for closing parentheses.
            } else {
                std::cin.putback(next);
                u64 rhs;
                std::cin >> rhs;
                lhs = calc(lhs_exp, rhs);

                // consume parentheses
                for (char parens; std::cin.peek() == ')'; std::cin >> parens) {
                    parens_level--;
                    if (saved.size() > 0) {
                        auto exp = saved.back();
                        if (exp.level == parens_level) {
                            lhs = calc(exp, lhs);
                            saved.pop_back();
                        }
                    }
                }
            }

        }
    }
    std::cout << sum << std::endl;
    return 0;
}
