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
#include <vector>
#include <fstream>
#include <sstream>
#include <limits>
#include <iterator>
#include <iomanip>
#include <string>
#include <cerrno>
#include <utility>
#include "BigInt.hpp";

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
    long long endprog = 0;
    int size = m.size();
    for (int i = 0; i < size; i++) {
        m.push_back(endprog);
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

BigInt add1(long long & a, long long & b) {
    return a + b;
}

BigInt mul2(long long& a, long long& b) {
    return a * b;
}

/*provides vecotr of parameter modes for opcode instructions
        with corresponding index*/
std::vector<long long > paramters(long long& opcode) {
    std::vector<long long> instMode;
    instMode.push_back(opcode % 10);
    for (int i = 1; i < 4; i++) {
        int pmode = std::pow(10, (i + 1));
        instMode.push_back(opcode / pmode % 10);
    }
    return instMode;
}

/*intcode conputer processses vector data that is loaded in
 int computer memory - provide data vector that is already
 stored in memory */
long long process(std::vector<long long>& data) {
    std::vector<int> opsize = {
             0, 4,  //[0]99-halt//[1]-add 
             4, 2,  //[2]-mul  //[3]-single input
             2, 3,  //[4]-output//[5]-jump true
             3, 4,  //[6]-jump flase//[7]-compare is less
             4, 2   //[8]-equals //[9]-relative
    };
    long long op;
    long long i=0;
    long long relBase = 0;
    BigInt ta;
    BigInt tt;
    int in=0;
    long long di, dii, diii;
    while (i < data.size()) {
        op = data[i];
        std::vector<long long> pval = paramters(op);
        op = pval[0];
        switch (op) {
        case ADD:
            ta = add1(data[pval[1] ? i + 1 : data[i + 1]], data[pval[2] ? i + 2 : data[i + 2]]);
            data[data[i + 3]] = ta.to_long_long();
            i += opsize[op];
            break;
        case MUL:
            tt = mul2(data[pval[1] ? i + 1 : data[i + 1]], data[pval[2] ? i + 2 : data[i + 2]]);
            data[data[i + 3]] = tt.to_long_long();
            i += opsize[op];
            break;
        case INPUT:
            std::cout << "input TEST ID:";
            std::cin >> in;
            data[data[i + 1]] = in;
            i += opsize[op];
            break;
        case OUTPUT:
            if (data[i + opsize[4]] == 99) {
                return data[data[i+1]];
            }
            i += opsize[op];
            break;
        case JPX:
            if (data[pval[1] ? i + 1 : data[i + 1]] != 0) {
                i = data[pval[2] ? i + 2 : data[i + 2]];
            } else {
                i += opsize[op];
            }
            break;
        case JNPX:
            if (data[pval[1] ? i + 1 : data[i + 1]] == 0) {
                i = data[pval[2] ? i + 2 : data[i + 2]];
            } else {
                i += opsize[op];
            }
            break;
        case LESSTHAN:
            if ((data[pval[1] ? i + 1 : data[i + 1]]) < (data[pval[2] ? i + 2 : data[i + 2]])) {
                data[data[i + 3]] = 1;
            }
            else {
                data[data[i + 3]] = 0;
            }
            i += opsize[op];
            break;
        case EQUAL:
            if ((data[pval[1] ? i + 1 : data[i + 1]]) == (data[pval[2] ? i + 2 : data[i + 2]])) {
                data[data[i + 2]] = 1;
            }
            else {
                data[data[i + 2]] = 0;
            }
            i += opsize[op];
            break;
        case RELATIVE:
            relBase += pval[1];
            i += opsize[op];
            break;
        case HALT:
            i = data.size()+1;
            break;
        default:
            std::cout << "opcode is:" << op << std::endl;
            i += 4;
            break;
        }
    }
    return data[0];
}


int main() {
    std::vector<long long> maindata;
    loadMemory(maindata);

    long long test = 34463338;
    long long test2 = 34463338;
    long long testresult = test * test2;
    std::cout << "test result is :" << testresult << std::endl;

    //std::cout << "part 1 output at p[0]" << std::endl;
    std::vector<long long> dt = maindata;
    std::cout << "Testing intcode computer BOOST keycode: part 1: " << process(dt) << std::endl;
    std::cout << std::endl;

    //std::vector<long long> dt2 = maindata;
    //std::cout << "Intcode diagnostic code part 2: "<< process(dt2) << std::endl;
    
}

