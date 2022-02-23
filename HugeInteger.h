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
	

	vector<int> huge;



public:


	// Required methods
	HugeInteger(const std::string& val);
	HugeInteger(int n);

	HugeInteger(std::vector<int>& h);

	HugeInteger add(const HugeInteger& h);
	HugeInteger subtract(const HugeInteger& h);
	HugeInteger multiply(const HugeInteger& h);
	int compareTo(const HugeInteger& h);
	std::string toString() const;

	int isNegative = 0;
};

#endif /* HUGEINTEGER_H_ */
