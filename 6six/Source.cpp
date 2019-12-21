/*Orbits
	direct orbit - AAA)BBB <- B orbits around A
	indirect BBB)AAA & CCC)BBB => A indirect orbit of C


*/
#include <iostream>
#include <vector>
#include <iomanip>
#include <algorithm>
#include <numeric>	
#include <string>
#include <cmath>
#include <fstream>
#include <sstream>
#include <limits>
#include <iterator>
#include <functional>
#include <utility>
#include <unordered_map>
#include <set>


void getData(std::vector<std::pair<std::string, std::string>>& data) {
	std::string s1;
	std::string	s2;
	std::ifstream file("input.txt");
	while (getline(file, s1, ')')) {
		getline(file, s2);
		data.push_back(std::make_pair(s1, s2));
	}
}

int main() {
	std::vector<std::pair<std::string, std::string>> data;
	getData(data);

	std::vector<std::string>::iterator sit;
	std::cout << "left\t right" << std::endl;

	for (int i = 0; i < data.size(); i++) {
			std::cout << data[i].first << "\t" << data[i].second << std::endl;

		}

}