/*
 position of first int - next int is op code
    #99 - program finished
    #1 adds numbers pos[op[1]]&[op[2]] stores valuein pos[op[3]]
    #2 multiplies pos[op[1]]&[op[2]] stores product in pos[op[3]]

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

int main() {
    std::vector<int> maindata;
    getData(maindata);
    std::vector<int> opcodes = {
        99, //halt
         1, //add
         2  //mul
    };
    const int instNumVal = 4;
    const int target = 19690720;
    int output = 0;
    int noun = 1;
    int verb = 1;
    int mxran = 99;


    for (int n = 49; n < mxran; n++) {
        for (int v = 99; v > 0; v--) {
            std::vector<int> data = maindata;
            noun = n;
            verb = v;
            //if (output - mxran > target) {
            //    std::cout << "\nOut > target n:v :" << n << ":" << v;
            //}
            alarmState(data, noun, verb);
            std::vector<int>::iterator posop;

            for (int i = 0; i < data.size() - instNumVal;) {
                posop = std::find(opcodes.begin(), opcodes.end(), data[i]);
                if (posop != opcodes.end()) {
                    if (data[i] == opcodes[1]) {
                        data[data[i + 3]] = add1(data[data[i + 1]], data[data[i + 2]]);
                    }
                    if (data[i] == opcodes[2]) {
                        data[data[i + 3]] = mul2(data[data[i + 1]], data[data[i + 2]]);
                    }
                    if (data[i] == opcodes[0]) {
                        output = data[0];
                        //std::cout << "\nopcode 99 at pos :" << i;
                        //std::cout << " Final Val @ pos 0 :" << data[0] << " noun and verb are  :" << std::endl;                 
                        if (output == target) {
                            std::cout << "out=target == output above" << std::endl;
                            std::cout << std::setw(2) << std::setfill('0') << noun;
                            std::cout << std::setw(2) << std::setfill('0') << verb << std::endl;
                            return 0;
                        }
                    }
                }
                else {
                    std::cout << "invalid input of opcode expect 1 2 or 99, got :" << data[i] << std::endl;
                    return 0;
                }
                i += instNumVal;
            }
        }
    }
}

