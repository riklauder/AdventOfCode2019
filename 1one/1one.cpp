
#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>
#include <fstream>
#include <sstream>
#include <limits>
#include <numeric>	
#include <iterator>
#include <string>
#include "BigInt.hpp"


void getData(std::vector<int>& d) {
	std::string s;
	std::ifstream file("input.txt");
	while (getline(file, s)) {
		int dd;
		std::stringstream dat(s);
		dat >> dd;
		d.push_back(dd);
	}
}

int calcfuelreq(int& x) {
	int fuelreq = std::floor(x/3);
	if (fuelreq > 2)
		fuelreq -= 2;
	return fuelreq;
}

BigInt calcadjustment(int& x) {
	BigInt fuelreqadj = calcfuelreq(x);
	int calcf = fuelreqadj.to_int();
	while ((calcf /3) > 2){
		calcf = calcfuelreq(calcf);
	if (calcf > 0)
		  fuelreqadj += calcf;
	}
	return fuelreqadj;
}

int main()
{
	std::vector<int> data;
	getData(data);

	unsigned long long totalfuelreq=0;
	for (auto x : data)
		totalfuelreq += calcfuelreq(x);
	std::cout << totalfuelreq << std::endl;
	std::cout << "adustments for fuel req:" << std::endl;
	BigInt adjfuelreq = 0;
	for (auto x : data)
		adjfuelreq += calcadjustment(x); 
	std::cout << "Adjusted: " << adjfuelreq;
	std::cout << " " << std::endl;
}

