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

bool Execute(ProgramT program, int &acc) {
    std::size_t pc{0};
    while (true) {
        if (program.size() <= pc) {
            return true;
        }

        auto &instr = program[pc];

        if (1 <= instr.count) {
            return false;
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
}

int main() {
    std::string op;
    ProgramT program;

    while (std::cin >> op) {
        int arg;
        std::cin >> arg;

        Instruction instr{op, arg,0};
        program.push_back(instr);
    }

    int acc_final{0};

    for (std::size_t i=0; i<program.size(); ++i) {
        ProgramT program_copy{program};
        auto &instruction = program_copy[i];
        if ("jmp" == instruction.op) {
            instruction.op = "nop";
        } else if ("nop" == instruction.op) {
            instruction.op = "jmp";
        } else {
            continue;
        }

        int acc{0};
        if (Execute(program_copy, acc)) {
            acc_final = acc;
            break;
        }
    }

    std::cout << acc_final << std::endl;
    return 0;
}
