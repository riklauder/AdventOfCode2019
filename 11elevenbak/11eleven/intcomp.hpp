
#include <iostream>
#include <numeric>	
#include <vector>
#include <deque>
#include <algorithm>
#include <cmath>
#include <charconv>
#include <execution>
#include <fstream>
#include <sstream>
#include <numeric>
#include <optional>
#include <limits>
#include <iterator>
#include <iomanip>
#include <string>
#include <utility>
#include <unordered_set>
#include <unordered_map>
#include <map>
#include <set>

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
    Day 11 - changes TBD
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

/*popuates intput int vector with input from file*/



class IntComp{
public:
    std::vector<long long> mem;

    
    /*replaces position 1 and 2 with values noun verb 
     input (data vector, noun, verb) */
    void alarmState(long long& noun, long long& verb) {
        mem[1] = noun;
        mem[2] = verb;
    }

    long long add1(long long & a, long long & b) {
        return a + b;
    }

    long long mul2(long long& a, long long& b) {
        return a * b;
    }

    /*provides vecotr of parameter modes for opcode instructions
            with corresponding index*/
    std::vector<long long > paramters(long long& opcode) {
        std::vector<long long> instMode;
        instMode.push_back(opcode % 100);
        for (int i = 1; i < 4; i++) {
            int pmode = std::pow(10, (i + 1));
            instMode.push_back(opcode / pmode % 10);
        }
        return instMode;
    }

    /*read parameter mode*/
    long long read(long long ip, long long mode) {
        if (mode == 0) {
            auto addr = mem[ip];
            return mem[addr];
        }
        if (mode == 1) {
            return mem[ip];
        }
        if (mode == 2) {
            auto addr = mem[ip] + rBase;
            return mem[addr];
        }
    }

    void write(long long ip, long long mode, long long value) {
        if (mode == 0) {
            auto addr = mem[ip];
            mem[addr] = value;
        }
        if (mode == 2) {
            auto addr = mem[ip] + rBase;
            mem[addr] = value;
        }
    }

    /*intcode conputer processses vector data that is loaded in
       int computer memory - provide <long long> vector that is already
       stored in memory 
       input = 1 or 2 based on part of puzzle input
       */
    long long process(long long input) {
        std::vector<int> opsize = {
                 0, 4,  //[0]99-halt//[1]-add 
                 4, 2,  //[2]-mul  //[3]-single input
                 2, 3,  //[4]-output//[5]-jump true
                 3, 4,  //[6]-jump flase//[7]-compare is less
                 4, 2   //[8]-equals //[9]-relative
        };
        long long op=0;
        long long i=0;
        
        long long arg1;
        long long arg2;
        
        mem.resize(mem.size() * 10);

        while (op != 99) {
            op = mem[i];
            std::vector<long long> pval = paramters(op);
            op = pval[0];
            switch (op) {
            case ADD:
                arg1 = read(i+1, pval[1]);
                arg2 = read( i+2 , pval[2]);
                write(i+opsize[op]-1, pval[3], add1(arg1, arg2));          
                i += opsize[op];
                break;
            case MUL:
                arg1 = read(i+1, pval[1]);
                arg2 = read( i+2, pval[2]);
                write(i+opsize[op]-1, pval[3], mul2(arg1, arg2));
                i += opsize[op];
                break;
            case INPUT:
                long long in;
                in = input;
                write( i+opsize[op]-1, pval[1], in);
                i += opsize[op];
                break;
            case OUTPUT:
                Output = read( i+1, pval[1]);
                std::cout << Output << ", ";
                i += opsize[op];
                break;
            case JPX:
                arg1 = read(i + 1, pval[1]);
                arg2 = read( i + 2, pval[2]);
                i = arg1 == 0 ? i+opsize[op] : arg2;
                break;
            case JNPX:
                arg1 = read(i + 1, pval[1]);
                arg2 = read( i + 2, pval[2]);
                i = arg1 != 0 ? i + opsize[op] : arg2;
                break;
            case LESSTHAN:
                arg1 = read( i + 1, pval[1]);
                arg2 = read( i + 2, pval[2]);
                write(i + opsize[op] - 1, pval[3], arg1 < arg2 ? 1 : 0);
                i += opsize[op];
                break;
            case EQUAL:
                arg1 = read( i + 1, pval[1]);
                arg2 = read(i + 2, pval[2]);
                write(i + opsize[op] - 1, pval[3], arg1 == arg2 ? 1 : 0);
                i += opsize[op];
                break;
            case RELATIVE:
                arg1 = read( i + 1, pval[1]);
                rBase += arg1;
                i += opsize[op];
                break;
            case HALT:
                if (Output == 0)
                    return mem[0];
                else return Output;
                break;
            default:
                std::cout << "opcode is i:op mem[i]" << i << ":" << op << " " << mem[i] << std::endl;
                i += 4;
                break;
            }

        }
        return Output;
    }

    IntComp(std::vector<long long>& data);

    private:
        long long Output = 0;
        long long rBase = 0;

};

IntComp::IntComp(std::vector<long long>& data): mem(data){}