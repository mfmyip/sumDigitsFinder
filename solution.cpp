#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cmath>
using namespace std;

class Solution { 
	vector<int> digits;

	// get number of digits of int n
	int numDigits(int n) {
		if (!(n / 10)) {
			return 1;
		} else {
			return 1 + numDigits(n/10);
		}
	}

	// get vector version of int n, with,
	// [0] being the least digit
	void getArr(int n) {
		int len = numDigits(n);
		for (int i = 0; i < len; ++i) {
			digits.push_back(n % 10);
			n = n / 10;
		}
	}

	// sums all the elements in digits (up to max index, from min index)
	int sumArr(int min = 0,int max = -1) {
		if (max == -1) {
			max = digits.size() - 1;
		}

		int sum = 0;
		for (int i = min; i <= max; ++i) {
			sum = sum + digits.at(i);
		}
		return sum;
	}

	// given an array length, finds the smallest possible n-digit number satisfying
	// that the digits add up to input x. 
	// Once found, constructs and returns an array of that number.
	int * findSmallest(int m, int len) {
		int * ret = new int[len];
		for (int i = 0; i < len; i++) {
			if (m > 9) { // 9 because highest digit
				ret[i] = 9;
				m -= 9;
			} else {
				ret[i] = max(0, m);
				m -= 9;
			}	
		}
		return ret;
	}

	// concatanates all values in digits,
	// e.g: [3, 2, 1] -> 123
	int concatArr() {
		int ret = 0;
		for (int i = 0; i < digits.size(); i++) {
			ret = ret + digits.at(i)* pow(10, i);
		}
		return ret;
	}

	public: int solution(int);
};

int Solution::solution(int n) {
	getArr(n); // produce our digits
	int expected = sumArr();
	//cout << "input given: " << n << endl;
	//cout << "\texpected result: " << expected << endl;

	int i = 1;	// start from index at 1 to compare with the 0th digit, 
			  			//no need to compare the 0th digit as increasing it would change the value of the sum
							// unless we only have 1 element
	if (digits.size() == 1) {
		i = 0;
	}
	while(i > 0) {
		// finds the index at which we do our operation
		if (digits[i] < digits[i - 1]) {
			break;
		} else if (digits[i] == digits[i - 1]) {
			if (0 < digits[i] && digits[i] < 9) {
				break;
			}
		}
		if (i == digits.size() - 1) { // base case
			break;
		}
		i++;
	}
	//cout << "\tindex to work on: " << i << endl;
	if (digits[i] < 9 && digits[i] < expected) { 
		// if our i-th digit is less than 9, simply adding 1, 
		// then finding the smallest max (for indices 0 to (i-1)) will yield the result
		digits[i]++;
		int comp = expected - sumArr(i);
		//cout << "\tcomparison val: " << comp << endl;
		int * tempArr = findSmallest(comp, i); // gets the array w the number we need to insert
		for (int j = 0; j < i; j++) {
			digits[j] = tempArr[j];
		}
	} else { // the value is 9, then we need to add a new digit
		digits.push_back(1);
		int comp = expected - 1;
		//cout << "\tcomparison val: " << comp << endl;
		int * tempArr = findSmallest(comp, i + 1); // gets the array w the number we need to insert
		
		for (int j = 0; j < i + 1; j++) {
			digits[j] = tempArr[j];
		}
	}
	int final = concatArr();
	//cout << "\tresult: " << final << endl;

	digits.clear();
	return final;
}

// expects argc = 3,
// 1st arg being the filename
// 2nd arg being the vaue of input
// 3rd arg being the number of times to loop the check
int main (int argc, char *argv[]) {
	Solution soln;

	int check = soln.solution(stoi(argv[1]));
	for (int i = 0; i < stoi(argv[2]); i++) {
		cout << check << endl;
		check = soln.solution(check);
	}
	return 0;
}