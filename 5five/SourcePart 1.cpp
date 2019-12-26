/*
 Op codes (pos[0]) of each instruction
   example instruction 1,0,0,3 or 1,0,0,3,99 
    #99 - halt - program finished
    #1 adds numbers pos[op[1]]&[op[2]] stores valuein pos[op[3]]
    #2 multiplies pos[op[1]]&[op[2]] stores product in pos[op[3]]
    #3 takes single input stored at pos[op[1]]
    #4 outputs value at op[1]
    #5 jump iff op[1]!=0 to op[2]
    #6 jump iff op[1]==0 to op[2]
    #7 if op[1] < op[2] pos[op[3]] = 1 else 0
    #8 equiv op[1]==op[2] pos[op[3]] = 1 else 0

0 = position mode - standard original
1 = immeditate mode
*/
#include <iostream>
#include <cstdlib>
#include <numeric>	
#include <algorithm>
#include <vector>
#include <cmath>
#include <fstream>
#include <sstream>
#include <limits>
#include <iterator>
#include <iomanip>
#include <string>

#define ADD 1
#define MUL 2
#define INPUT 3
#define OUTPUT 4
#define JPX 5
#define JNPX 6
#define FIRSTCMP 7
#define EQUAL 8

/*popuates intput int vector with input from file*/
void getData(std::vector<int>& d) {
    std::string s;
    std::ifstream file("input.txt");
    while (getline(file, s, ',')) {
        int dd;
        std::stringstream dat(s);
        dat >> dd;
        d.push_back(dd);
    }
}

/*replaces position 1 and 2 with values noun verb 
 input (data vector, noun, verb) */
void alarmState(std::vector<int>& d, int &noun, int& verb) {
    //std::cout << " pos1:" << d[1] << " changed to noun :" << noun;
    //std::cout << " pos2:" << d[2] << " changed to verb :" << verb << std::endl;
    d[1] = noun;
    d[2] = verb;
}

int add1(int& a, int& b) {
    int r = a + b;
    return r;
}

int mul2(int& a, int& b) {
    int r = a * b;
    return r;
}

std::vector<int> paramterInstruction(int& opcode) {
    std::vector<int> instMode;
    instMode.push_back(opcode % 10);
    for (int i = 1; i < 4; i++) {
        int pmode = std::pow(10, (i + 1));
        instMode.push_back(opcode / pmode % 10);
    }
    return instMode;
}

/*intcode conputer processs function - provide copy of data vector
    p1noun and p2verb replace values at p[1] and p[2] */
int process(std::vector<int>& data, int p1noun, int p2verb) {
    std::vector<int> opcodes = {
        99, 1, //halt   //add
         2, 3, //mul    //single input
         4, 5, //output //
         6, 7, //       // 
         8
    };
    std::vector<int> opsize = {
            0, //halt
             4, //add
             4, //mul
             2, //single input
             2  //output
    };
    int output = 0;
    int op;

    //alarmState(data, p1noun, p2verb);
    std::vector<int>::iterator positt;
    int i=0;
    while (i < data.size()){
        op = data[i];
        std::vector<int> pval = paramterInstruction(op);
        op %= 10;
        positt = std::find(opcodes.begin(), opcodes.end(), op);
        
        if (positt != opcodes.end()) {
            if (op == opcodes[1]) {
                data[data[i+3]] = add1(data[pval[1] ? i + 1 : data[i + 1]], data[pval[2] ? i + 2: data[i + 2]]);
                i += opsize[op];
            }
            if (op == opcodes[2]) {
                data[data[i+3]] = mul2(data[pval[1] ? i + 1: data[i+1]], data[pval[2] ? i + 2: data[i+2]]);
                i += opsize[op];
            }
            if (op == opcodes[3]) {
                int in;
                std::cout << "input:";
                std::cin >> in;
                data[data[i+1]] = in;
                i += opsize[op];
            }
            if (op == opcodes[4]) {
                if (data[i + opsize[4]] == 99) {
                    return data[data[i + 1]];
                }
                i += opsize[op];
            }
            if (op == opcodes[0]) {
                i = data.size() + 1;
          }
     }
        else {
            std::cout << "invalid input of opcode expect 1 2 or 99, got :" << data[i] << std::endl;
            i += opsize[1];
        }
    }
    return data[0];
}

void part2(std::vector<int>& data, const int& target) {
    int noun;
    int verb;
    int mxran = 99;
    int output = -1;

    for (int n = 49; n < mxran; n++) {
        for (int v = 99; v > 0; v--) {
            std::vector<int> dt2 = data;
            output = process(dt2, n, v);
            if (output == target) {
                std::cout << "out=target == output above" << std::endl;
                std::cout << std::setw(2) << std::setfill('0') << n;
                std::cout << std::setw(2) << std::setfill('0') << v << std::endl;
                return;
            }
        }
    }
}

int main() {
    std::vector<int> maindata;
    getData(maindata);

    //std::cout << "part 1 output at p[0]" << std::endl;
    std::vector<int> dt = maindata;
    std::cout << process(dt, maindata[1], maindata[2]) << std::endl;

    //const int target = 19690720;
    //std::cout << "part 2 target is " << target << std::endl;
    
    //part2(maindata, target);
   
}

