#ifndef HUGEINTEGER_H_
#define HUGEINTEGER_H_
#include <iostream>

#include <vector>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

using namespace std;

class HugeInteger
{
private:
	
	int isPositive = 0;
	int isNegative = 0;
	vector<int> huge;



public:


	// Required methods
	HugeInteger(const std::string& val);
	HugeInteger(int n);
	HugeInteger(std::vector<int>& sum);
	HugeInteger add(const HugeInteger& h);
	HugeInteger subtract(const HugeInteger& h);
	HugeInteger multiply(const HugeInteger& h);
	int compareTo(const HugeInteger& h);
	std::string toString();
};

#endif /* HUGEINTEGER_H_ */
