#include "HugeInteger.h"

#include <iostream>
#include <vector>
#include <string>

using namespace std;

HugeInteger::HugeInteger(std::vector<int>& sum){
	huge = sum;
}

HugeInteger::HugeInteger(const std::string& val) {

	int i = 0;
	int n = val.length();
	if (n == 0){                                                  //String cannot be empty, so we need to throw an error if that's the case.
		throw std::invalid_argument("Invalid HugeInteger");
	}
	if(val[0]=='-'){                                              //If there is a negative sign at the beginning, let isNegative be 1
		isNegative = 1;
		i++;
	}
	else{                                                         //If there isn't a negative sign, let isPositive be 1
		isPositive = 1;
	}
	while(i < n){

		int a = (val[i] - '0');
		if(a>9||a<0){                                             //If the index value resides outside of bounds, throw an error
			throw std::invalid_argument("Invalid HugeInteger");
		}
		huge.push_back(a);                                        //append the integer values into our integer vector
		i++;
	}

}

HugeInteger::HugeInteger(int n) {

	if(n<=0){                                                  //Throw an exception if n is less than or equal to 0.
		throw std::invalid_argument("Invalid HugeInteger");
	}

	srand(time(0));                                            //set the seed for random number generator

	for(int i = 1; i <= n; i++){                               //Use a for loop to create the random integer huge
		huge.push_back(rand()%10);                             //Use modulus 10 to guarantee a value between 0-9
		if(i == 0 && huge[i] == 0){                            //However, the first number in our huge cannot be 0
			huge.insert(huge.begin(),1);                       //In case it is, we simply insert 1 at the start of the array
		}
	}

}

HugeInteger HugeInteger::add(const HugeInteger& h) {


	int carry = 0, temp_sum = 0, i = 0, j = 0, k = 0;     //carry being our carry value, temp_sum being the sum of two corresponding indicies
	int huge_size = huge.size();                        //i j and k representing counters to keep our math organized
	int h_size = h.huge.size();                         //lastly, our two variables representing size of our huges
	int sumsize = 0;

	vector<int> sum;

	if (huge_size >= h_size){                           //if our huge size is larger than or equal to h
		i = huge_size - 1;                              //starting from the very last index (like addition on paper)
		j = h_size - 1;
		k = huge_size -1;                              //k represents the size of our sum, so it must be the same as the larger array


		while(j>=0){                                      //loop until we run out of indicies for the smaller array
			temp_sum = huge[i] + h.huge[j] + carry;   //find the sum of the corresponding indicies with carry if needed and store it in temp_sum
			sum.insert(sum.begin(),(temp_sum%10));       //take mod 10 to guarantee one digit, and then convert back to a string character
			carry = temp_sum/10;                          //carry will be one if the number is between 10 and 19, and 0 if between 0 and 9

			i--;                                          //decrement all values and move to the next index
			k--;
			j--;
		}

		while(i>=0){                              //since i > j, there is remaining values at the start of our larger array
			temp_sum = huge[i] + carry;                 //use the same process to store them in temp_sum, using carry if needed
			sum.insert(sum.begin(),(temp_sum%10));       //append the to the corresponding index in character type
			carry = temp_sum/10;

			i--;                                          //decrement till i and k are 0, meaning our summation is finished
			k--;
		}
		if(carry == 1){
			sum.insert(sum.begin(),(carry));
		}
	}

	else if(h_size > huge_size){                      //this is essentially the exact same thing, but h is bigger than huge.
		j = huge_size - 1;                             //the only edits i must make to my code above is let i be the size of h instead of huge
		i = h_size - 1;
		k = h_size - 1;

		while(j>=0){
			temp_sum = huge[j] + h.huge[i] + carry;
			sum.insert(sum.begin(),(temp_sum%10));
			carry = temp_sum/10;

			i--;
			k--;
			j--;
		}

		while(i>=0){
			temp_sum = h.huge[i] + carry;
			sum.insert(sum.begin(),(temp_sum%10));
			carry = temp_sum/10;

			i--;
			k--;
		}

		if(carry == 1){
			sum.insert(sum.begin(),(carry));
		}

	}

	return HugeInteger(sum);
}

HugeInteger HugeInteger::subtract(const HugeInteger& h) {

	int carry = 0, temp_diff = 0, i = 0, j = 0, k = 0;
	int huge_size = huge.size();
	int h_size = h.huge.size();

	vector<int> difference;

	if (huge_size > h_size){
		i = huge_size - 1;
		j = h_size - 1;
		k = huge_size - 1;

		while (j >= 0){
			temp_diff = huge[i] - h.huge[j];
			if (temp_diff < 0){
				temp_diff = (temp_diff * -1);
				huge[i-1] = huge[i-1] - 1;
			}
		}
	}


	return HugeInteger("");
}

HugeInteger HugeInteger::multiply(const HugeInteger& h) {
	// TODO
	return HugeInteger("");
}

int HugeInteger::compareTo(const HugeInteger& h) {
	// TODO
	return 0;
}

std::string HugeInteger::toString() {

	string back_to_string = "";
	int n = huge.size();

	if(isNegative == 1){
		back_to_string.push_back('-');
	}

	for(int i = 0; i < n; i++){
		back_to_string.push_back(huge[i]+'0');
	}

	return back_to_string;
}
