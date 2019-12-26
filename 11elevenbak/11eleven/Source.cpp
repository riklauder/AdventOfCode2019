
#include <iostream>
#include "intcomp.hpp"

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

int main() {
    std::vector<long long> maindata;
    loadMemory(maindata);


    //std::vector<long long> test1 = { 109,1,204,-1,1001,100,1,100,1008,100,16,101,1006,101,0,99 };
    //std::cout << "Testing intcode computer BOOST keycode: part 1: " << process(test1) << std::endl;

    //std::vector<long long> tester2 = { 1102,34915192,34915192,7,4,7,99,0 };
    //std::cout << "Testing intcode computer BOOST keycode: part 1: " << process(tester2) << std::endl;

    //std::vector<long long> tester3 = { 104,1125899906842624,99 };
    //std::cout << "Testing intcode computer BOOST keycode: part 1: " << process(tester3) << std::endl;

    std::cout << "part 1 input 1 - part 2 input 2" << std::endl;
    std::vector<long long> dt = maindata;
    IntComp intcomp1(dt);
    long long part1 = intcomp1.process(1);
    std::cout << std::endl;

    std::cout << "part 2 input 2" << std::endl;
    std::vector<long long> dt2 = maindata;
    IntComp intcomp2(dt2);
    long long part2 = intcomp2.process(2);
    std::cout << std::endl;

    //std::vector<long long> dt2 = maindata;
    //std::cout << "Intcode diagnostic code part 2: "<< process(dt2) << std::endl;

}

