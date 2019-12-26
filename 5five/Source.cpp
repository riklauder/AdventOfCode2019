/*
 Op codes (pos[0]) of each instruction
   example instructions 1,0,0,3 or 1,0,0,3,99 
  Possilble Op Codes (1, 2, 3, 4, 5, 6, 7, 8, 99)

0 = position mode - standard original
1 = immeditate mode
RESULT:
    input TEST ID:1
    diagnostic code processing: part 1: 2845163

    input TEST ID:5
    Intcode diagnostic code part 2: 9436229
*/
#include <iostream>
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

/*Op Codes*/
constexpr auto ADD = 1;      //#1 adds numbers pos[op[1]]&[op[2]] stores valuein pos[op[3]];
constexpr auto MUL = 2;      //#2 multiplies pos[op[1]]&[op[2]] stores product in pos[op[3]];
constexpr auto INPUT = 3;    //#3 takes single input stored at pos[op[1]];
constexpr auto OUTPUT = 4;   //#4 outputs value at op[1];
constexpr auto JPX = 5;      //#5 jump iff op[1]!=0 to op[2];
constexpr auto JNPX = 6;     //#6 jump iff op[1]==0 to op[2];
constexpr auto FIRSTCMP = 7; //#7 if op[1] < op[2] pos[op[3]] = 1 else 0;
constexpr auto EQUAL = 8;    //#8 equiv op[1]==op[2] pos[op[3]] = 1 else 0;
constexpr auto HALT = 99;    //#99 - halt - program finished;

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
int process(std::vector<int>& data) {
    std::vector<int> opsize = {
             0, 4,  //[0]99-halt//[1]-add 
             4, 2,  //[2]-mul  //[3]-single input
             2, 3,  //[4]-output//[5]-jump true
             3, 4,  //[6]-jump flase//[7]-compare is less
             4      //[8]-equals
    };
    int output = 0;
    int op;
    int i=0;

    while (i < data.size()) {
        op = data[i];
        std::vector<int> pval = paramterInstruction(op);
        op = pval[0];
        switch (op) {
        case ADD:
            data[data[i + 3]] = add1(data[pval[1] ? i + 1 : data[i + 1]], data[pval[2] ? i + 2 : data[i + 2]]);
            i += opsize[op];
            break;
        case MUL:
            data[data[i + 3]] = mul2(data[pval[1] ? i + 1 : data[i + 1]], data[pval[2] ? i + 2 : data[i + 2]]);
            i += opsize[op];
            break;
        case INPUT:
            int in;
            std::cout << "input TEST ID:";
            std::cin >> in;
            data[data[i + 1]] = in;
            i += opsize[op];
            break;
        case OUTPUT:
            if (data[i + opsize[4]] == 99) {
                return data[data[i + 1]];
            }
            i += opsize[op];
            break;
        case JPX:
            if (data[pval[1] ? i + 1 : data[i + 1]] != 0) {
                i = data[pval[2] ? i + 2 : data[i + 2]];
            }
            else {
                i += opsize[op];
            }
            break;
        case JNPX:
            if (data[pval[1] ? i + 1 : data[i + 1]] == 0) {
                i = data[pval[2] ? i + 2 : data[i + 2]];
            }
            else {
                i += opsize[op];
            }
            break;
        case FIRSTCMP:
            if (data[pval[1] ? i + 1 : data[i + 1]] < data[pval[2] ? i + 2 : data[i + 2]]) {
                data[data[i + 3]] = 1;
            }
            else {
                data[data[i + 3]] = 0;
            }
            i += opsize[op];
            break;
        case EQUAL:
            if (data[pval[1] ? i + 1 : data[i + 1]] == data[pval[2] ? i + 2 : data[i + 2]]) {
                data[data[i + 3]] = 1;
            }
            else {
                data[data[i + 3]] = 0;
            }
            i += opsize[op];
            break;
        case HALT:
            i = data.size() + 1;
            break;
        default:
            i += opsize[op];
            break;
        }
    }
    return data[0];
}


int main() {
    std::vector<int> maindata;
    getData(maindata);

    //std::cout << "part 1 output at p[0]" << std::endl;
    std::vector<int> dt = maindata;
    std::cout << "diagnostic code processing: part 1: " << process(dt) << std::endl;
    std::cout << std::endl;

    std::vector<int> dt2 = maindata;
    std::cout << "Intcode diagnostic code part 2: "<< process(dt2) << std::endl;
    
}

