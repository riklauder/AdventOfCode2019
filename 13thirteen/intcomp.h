#pragma once
/*
 **Op codes**
   (pos[0]) of each instruction
   example instructions 1,0,0,3 or 1,0,0,3,99
  Possilble Op Codes (1, 2, 3, 4, 5, 6, 7, 8, 9, 99)

**parameter modes**
  0 = position mode - standard original provides index of value
  1 = immeditate mode - parameter is the value
  2 = relative mode - base provided with offset parameter

RESULT:
    Day 9 - adding relative mode
*/


/*Op Codes*/
constexpr auto ADD = 1;      //#1 adds numbers pos[op[1]]&[op[2]] stores valuein pos[op[3]];
constexpr auto MUL = 2;      //#2 multiplies pos[op[1]]&[op[2]] stores product in pos[op[3]];
constexpr auto INPUT = 3;    //#3 takes single input stored at pos[op[1]];
constexpr auto OUTPUT = 4;   //#4 outputs value at op[1];
constexpr auto JPX = 5;      //#5 jump if op[1]!=0, op[2] else nothing
constexpr auto JNPX = 6;     //#6 jump if op[1]==0, op[2] else nothing;
constexpr auto LESSTHAN = 7; //#7 if op[1] < op[2] pos[op[3]] = 1 else 0;
constexpr auto EQUAL = 8;    //#8 if op[1]==op[2] pos[op[3]] = 1 else 0;
constexpr auto RELATIVE = 9; //#9 - sets relative base using offset op[1]   
constexpr auto HALT = 99;    //#99 - halt - program finished;

//#include <cstdio>
#include <iostream>
#include <fstream>
#include <sstream>
#include <iterator>
#include <string>
#include <queue>
#include <vector>
#include <charconv>
#include <utility>
//#pragma warning(disable : 4996)

namespace ic {

    static constexpr long long kModeDiv[] = { 10, 100, 1000, 10000 };

    struct IntcodeComputer {
        std::vector<long long> mem;
        std::vector<long long> out;
        long long ip = 0, rel = 0;

        bool load(std::string filename) {
            std::string s;
            std::ifstream file(filename);
            if (!file)
                return false;
            while (getline(file, s, ',')) {
                long long dd;
                std::stringstream dat(s);
                dat >> dd;
                mem.push_back(dd);
            }
            if (mem.size() < 128 * 1024)
                mem.resize(128 * 1024, 0ll);
            out.reserve(16);
            return true;
        }

        long long& pval(long long i) {
            long long mode = (mem[ip] / kModeDiv[i]) % 10;
            return mem[((mode == 1) ? (ip + i) : mem[ip + i]) + ((mode == 2) ? rel : 0)];
        }

        // return value: 0 = halted, 1 = need input
        int run(std::deque<long long>& input) {
            out.clear();
            while (1) {
                long long op = mem[ip];
                switch (op % 100) {
                case ADD: pval(3) = pval(1) + pval(2); ip += 4; break; // add
                case MUL: pval(3) = pval(1) * pval(2); ip += 4; break; // mul
                case INPUT: if (input.empty()) return 1; pval(1) = input.front(); input.pop_front(); ip += 2; break; // read
                case OUTPUT: out.push_back(pval(1)); ip += 2; break; // write
                case JPX: ip = (pval(1) != 0) ? pval(2) : (ip + 3); break; // jump if true
                case JNPX: ip = (pval(1) == 0) ? pval(2) : (ip + 3); break; // jump if false
                case LESSTHAN: pval(3) = (pval(1) < pval(2)) ? 1 : 0; ip += 4; break; // less than
                case EQUAL: pval(3) = (pval(1) == pval(2)) ? 1 : 0; ip += 4; break; // equals
                case RELATIVE: rel += pval(1); ip += 2; break; // set relative base
                default: return 0;
                }
            }
        }

        int run(long long val) {
            std::deque<long long> input{ val };
            return run(input);
        }

        int run() {
            std::deque<long long> input;
            return run(input);
        }

        int run(const char* str) {
            std::deque<long long> input;
            for (int i = 0; str[i] != '\0'; i++) {
                input.push_back(str[i]);
            }
            return run(input);
        }
    };

} // namespace vh