/*
 Op codes (pos[0]) of each instruction
   example instruction 1,0,0,3 or 1,0,0,3,99 
    #99 - halt - program finished
    #1 adds numbers pos[op[1]]&[op[2]] stores valuein pos[op[3]]
    #2 multiplies pos[op[1]]&[op[2]] stores product in pos[op[3]]
    #3 single input stored at pos[op[1]]

**Part 1 Success output
    end of program value 99 reached at pos :172
    Final Val @ pos 0 :5098658
                    5098658
**Part 2 Q - determine what pair of inputs produces the output 19690720
    Answer is 5064 - output:
    out=target == output above
5064
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
/*replaces position 1 and 2 with the values noun verb 
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

std::vector<int> paramterInstruction(int opcode) {
    std::vector<int> instMode;
    instMode.push_back(opcode % 100);
    opcode /= 100;
    for (int i = 0; i < 3; i++) {
        instMode.push_back(opcode % 10);
        opcode /= 10;
    }
    return instMode;
}

/*intcode conputer processs function - provide copy of data vector
    p1noun and p2verb replace values at p[1] and p[2] */
int process(std::vector<int>& data, int p1noun, int p2verb) {
    int pos_mode = 0;//position mode value at pos[op[i]]
    int imm_mode = 1;//immediate mode value is face op[i]

    std::vector<int> opcodes = {
        99, //halt
         1, //add
         2, //mul
         3, //single input
         4  //output
    };
    std::vector<int> opinstsize = {
            0, //halt
             4, //add
             4, //mul
             2, //single input
             2  //output
    };

    int instructionSize = 4;
    int output = 0;

    alarmState(data, p1noun, p2verb);
    std::vector<int>::iterator positt;
    for (int i = 0; i < data.size() - instructionSize;) {
        if (data[i]== 1100 || data[i] == 0) {
            i++;
        }
        positt = std::find(opcodes.begin(), opcodes.end(), data[i]);
        std::vector<int> dval(5,0);
        int op = data[i];
        
        if (op > 9) {
            std::vector<int> instpam = paramterInstruction(op);
            op = instpam[0];
            for (int j = 1; j <= opinstsize[op]; j++) {
                if (instpam[j] == 0)
                    dval[j - 1] = data[data[i + j]];
                if (instpam[j] == 1)
                    dval[j - 1] = data[i + j];
            }
        } else {
            for (int j = 1; j <= opinstsize[op]; j++) 
                    dval[j - 1] = data[data[i + j]];
        }
            if (positt != opcodes.end()) {
            if (op == opcodes[1]) {
                data[data[opinstsize[op]-1]] = add1(dval[0], dval[1]);
                i += opinstsize[op];
            }
            if (op == opcodes[2]) {
                data[data[i + opinstsize[op] - 1]] = mul2(dval[0], dval[1]);
                i += opinstsize[op];
            }
            if (op == opcodes[3]) {
                int in;
                std::cout << "input:";
                std::cin >> in;
                data[data[i+1]] = in;
                i += (opinstsize[op]);
            }
            if (op == opcodes[4]) {
                int out = data[dval[0]];
                std::cout << "output:" << out << " ";
                i += (opinstsize[op]);
            }
            if (op == opcodes[0]) {
                int output = data[0];
                return output;
            }
        }
        else {
            std::cout << "invalid input of opcode expect 1 2 or 99, got :" << data[i] << std::endl;
            return 0;
        }
    }
    std::cout << "WARN:reached eof with no halt signal : returning 0" << std::endl;
    return 0;
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

