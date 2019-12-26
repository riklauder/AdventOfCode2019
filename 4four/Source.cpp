#include <iostream>
#include <vector>
#include <iomanip>
#include <algorithm>
#include <numeric>	
#include <string>

/*For part 1 input num=low range
                   v = high
For part 2 input num=low range(same)
				   v = low
				                  */
bool rules(int num, const int& v) {
	bool rule1 = false;
	bool rule2 = true;
	int last = 0;
	int lastdn = 0;

	while (num >= 10) {
		int d = num % 10;
		int dn = num / 10 % 10;
		if (num < v) {
			if ((d == dn)&&(d != last) && (last != lastdn))
				rule1 = true;
		}
		if (num >= v/10) {
			if ((d == dn) && (d == last))
				rule1 = false;
		}
		if (d < dn)
			rule2 = false;
		lastdn = dn;
		last = d;
		num /= 10;
	}
	return (rule1 && rule2);
}

bool rules2(const std::string& nums) {
	bool rule1 = false;
	bool rule2 = false;

	//const auto nums(std::to_string(num));
	std::string numsort(nums);
	std::sort(numsort.begin(), numsort.end());
	if (nums == numsort)
		rule2 = true;

	for (int i = 0; i < nums.size(); i++) {
		const int c = std::count(nums.begin(), nums.end(), nums[i]);
		if (c == 2)
			rule1 = true;
	}
	
	return (rule1 && rule2);
}

/*rules2 takes a very long time in dbug mode only
compile with g++ -O3 or make release in VS*/
int main() {
	const int low = 168630;
	const int high = 718098;
	const int range = high - low;
	int count=0;
	for (int i = low; i <= high; i++) {
		if (rules(i, high))
			count++;
	}
	std::cout << "low =" << low << " and high =" << high << std::endl;
	std::cout << "rannge of " << range << " possilbe passwords" << std::endl;
	std::cout << "apply rules to obtain " << count << " possible passwords=" << std::endl;
	std::cout << "part 2 - 2 adjacent numbers only" << std::endl;
	int count2 = 0;
	for (int i = low; i <= high; i++) {
		if (rules2(std::to_string(i)))
			count2++;
	}
	std::cout << "apply rules to obtain " << count2 << " possible passwords=" << std::endl;

}