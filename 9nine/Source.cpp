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
#include <iostream>
#include <numeric>	
#include <algorithm>
#include <cmath>
#include <charconv>
#include <vector>
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
#include <set>

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
void loadMemory(std::vector<long long>& m) {
    std::string s;
    std::ifstream file("input.txt");
    while (getline(file, s, ',')) {
        long long dd;
        std::stringstream dat(s);
        dat >> dd;
        m.push_back(dd);
    }
}

/*replaces position 1 and 2 with values noun verb 
 input (data vector, noun, verb) */
void alarmState(std::vector<long long>& d, int &noun, int& verb) {
    //std::cout << " pos1:" << d[1] << " changed to noun :" << noun;
    //std::cout << " pos2:" << d[2] << " changed to verb :" << verb << std::endl;
    d[1] = noun;
    d[2] = verb;
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
long long read(std::vector<long long>& mem, long long ip, long long mode, long long& rBase) {
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

void write(std::vector<long long>& mem, long long ip, long long mode, long long value, long long& rBase) {
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
long long process(std::vector<long long>& data, long long input) {
    std::vector<int> opsize = {
             0, 4,  //[0]99-halt//[1]-add 
             4, 2,  //[2]-mul  //[3]-single input
             2, 3,  //[4]-output//[5]-jump true
             3, 4,  //[6]-jump flase//[7]-compare is less
             4, 2   //[8]-equals //[9]-relative
    };
    long long op=0;
    long long i=0;
    long long relBase = 0;
    long long arg1;
    long long arg2;
    long long Output = 0;
    data.resize(data.size() * 10);

    while (op != 99) {
        op = data[i];
        std::vector<long long> pval = paramters(op);
        op = pval[0];
        switch (op) {
        case ADD:
            arg1 = read(data, i+1, pval[1], relBase);
            arg2 = read(data, i+2 , pval[2], relBase);
            write(data, i+opsize[op]-1, pval[3], add1(arg1, arg2), relBase);          
            i += opsize[op];
            break;
        case MUL:
            arg1 = read(data, i+1, pval[1], relBase);
            arg2 = read(data, i+2, pval[2], relBase);
            write(data, i+opsize[op]-1, pval[3], mul2(arg1, arg2), relBase);
            i += opsize[op];
            break;
        case INPUT:
            long long in;
            in = input;
            write(data, i+opsize[op]-1, pval[1], in, relBase);
            i += opsize[op];
            break;
        case OUTPUT:
            Output = read(data, i+1, pval[1],relBase);
            std::cout << Output << ", ";
            i += opsize[op];
            break;
        case JPX:
            arg1 = read(data, i + 1, pval[1], relBase);
            arg2 = read(data, i + 2, pval[2], relBase);
            i = arg1 == 0 ? i+opsize[op] : arg2;
            break;
        case JNPX:
            arg1 = read(data, i + 1, pval[1], relBase);
            arg2 = read(data, i + 2, pval[2], relBase);
            i = arg1 != 0 ? i + opsize[op] : arg2;
            break;
        case LESSTHAN:
            arg1 = read(data, i + 1, pval[1], relBase);
            arg2 = read(data, i + 2, pval[2], relBase);
            write(data, i + opsize[op] - 1, pval[3], arg1 < arg2 ? 1 : 0, relBase);
            i += opsize[op];
            break;
        case EQUAL:
            arg1 = read(data, i + 1, pval[1], relBase);
            arg2 = read(data, i + 2, pval[2], relBase);
            write(data, i + opsize[op] - 1, pval[3], arg1 == arg2 ? 1 : 0, relBase);
            i += opsize[op];
            break;
        case RELATIVE:
            arg1 = read(data, i + 1, pval[1], relBase);
            relBase += arg1;
            i += opsize[op];
            break;
        case HALT:
            if (Output == 0)
                return data[0];
            else return Output;
            break;
        default:
            std::cout << "opcode is i:op data[i]" << i << ":" << op << " " << data[i] << std::endl;
            i += 4;
            break;
        }

    }
    return Output;
}


int main() {
    std::vector<long long> maindata;
    loadMemory(maindata);

    long long test = 34463338;
    long long test2 = 34463338;
    long long testresult = test * test2;
    std::cout << "test result is :" << testresult << std::endl;

    
    //std::vector<long long> test1 = { 109,1,204,-1,1001,100,1,100,1008,100,16,101,1006,101,0,99 };
    //std::cout << "Testing intcode computer BOOST keycode: part 1: " << process(test1) << std::endl;

    //std::vector<long long> tester2 = { 1102,34915192,34915192,7,4,7,99,0 };
    //std::cout << "Testing intcode computer BOOST keycode: part 1: " << process(tester2) << std::endl;

    //std::vector<long long> tester3 = { 104,1125899906842624,99 };
    //std::cout << "Testing intcode computer BOOST keycode: part 1: " << process(tester3) << std::endl;

    std::cout << "part 1 input 1 - part 2 input 2" << std::endl;
    std::vector<long long> dt = maindata;
    long long part1 = process(dt, 1);
    std::cout << std::endl;

    std::cout << "part 2 input 2" << std::endl;
    std::vector<long long> dt2 = maindata;
    long long part2 = process(dt2, 2);
    std::cout << std::endl;

    //std::vector<long long> dt2 = maindata;
    //std::cout << "Intcode diagnostic code part 2: "<< process(dt2) << std::endl;
    
}

