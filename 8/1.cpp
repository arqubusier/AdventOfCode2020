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

struct Instruction{
    std::string op;
    int arg;
    int count;
};

using ProgramT = std::vector<Instruction>;

int main() {
    std::string op;
    ProgramT program;

    while (std::cin >> op) {
        int arg;
        std::cin >> arg;

        Instruction instr{op, arg,0};
        program.push_back(instr);
    }

    int acc{0};
    std::size_t pc{0};
    while (true) {
        auto &instr = program[pc];

        if (1 <= instr.count) {
            break;
        } else if ("nop" == instr.op) {
            pc++;
        } else if ("jmp" == instr.op) {
            pc += instr.arg;
        } else if ("acc" == instr.op) {
            acc += instr.arg;
            pc++;
        }
        ++instr.count;
    }

    std::cout << acc << std::endl;
    return 0;
}
