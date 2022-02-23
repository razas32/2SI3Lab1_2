#include "HugeInteger.h"

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

HugeInteger::HugeInteger(std::vector<int>& h){  //constructor so i can pass vector ints into huge integer
	huge = h;
}

HugeInteger::HugeInteger(const std::string& val){

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
		isNegative = 0;
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

HugeInteger HugeInteger::add(const HugeInteger& h){


	int carry = 0, temp_sum = 0, i = 0, j = 0, k = 0;     //carry being our carry value, temp_sum being the sum of two corresponding indicies
	int huge_size = huge.size();                        //i j and k representing counters to keep our math organized
	int h_size = h.huge.size();                         //lastly, our two variables representing size of our huges


	vector<int> sum;

	if( (this->isNegative == 0 && h.isNegative == 0) || (this->isNegative == 1 && h.isNegative == 1) ){ //Algorithm for two positives or two negatives will be the same. Confirm negative or not at the end.

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
		if (sum[0] == 0 && sum.size() != 1){  //destroys leading 0s. destroyed in the single digit same number case so we have to make sure sum size isnt one
				sum.erase(sum.begin());
			}
		HugeInteger res = HugeInteger(sum);      // duplicate sum into res
		if (this->isNegative == 1 && h.isNegative == 1){ //if both numbers are negative, then we know result will be negative. Let isNegative equal 1.
			res.isNegative = 1;
		}
		return res;
	}

	else if(this->isNegative == 0 && h.isNegative == 1){ // positive + negative is the same thing is positive - positive so call subtract after making h positive
		HugeInteger hcopy(h);  //h is const cant edit fuck u
		hcopy.isNegative = 0;
		HugeInteger res = this->subtract(hcopy);
		return res;
	}
	else{
		HugeInteger hugecopy(*this);                      //dereference hugeint so i can use it as an object
		HugeInteger hcopy(h);                               //last case is negative(this) + positive(h) which is the same as h - huge.
		hugecopy.isNegative = 0;
		HugeInteger res = hcopy.subtract(hugecopy);
		return res;
	}

}
HugeInteger HugeInteger::subtract(const HugeInteger& h) {

	if (compareTo(h) == 0){                     // if numbers are equivalent, difference will be 0
		return HugeInteger("0");
	}
	if (this->isNegative == 0 && h.isNegative == 1){         //positive(huge) - negative(h) is the same as huge + h
		HugeInteger hugecopy(*this);
		HugeInteger hcopy(h);
		hcopy.isNegative = 0;                                //set h to positive and call add method
		HugeInteger res = hugecopy.add(hcopy);
		return res;
	}

	else if (this->isNegative == 1 && h.isNegative == 0){   //negative(huge) - positive(h) is the same as (huge + h)*-1

		HugeInteger hugecopy(*this);                //dereference so we can use
		HugeInteger hcopy(h);
		hugecopy.isNegative = 0;
		HugeInteger res = hugecopy.add(hcopy);
		res.isNegative = 1;
		return res;
	}

	int carry = 0, temp_diff = 0;           //initialize variables
	int huge_size = huge.size();
	int h_size = h.huge.size();

	vector <int> num1;
	vector <int> num2;

	vector <int> diff;

	if (huge_size != h_size){            //means theyre not the same length - algorithm needed to do computation
		if (huge_size < h_size){         //num 2 is set to the SHORTER value
			num2 = huge;
			num1 = h.huge;
		}
		else{
			num1 = huge;
			num2 = h.huge;
		}
	}
	else{
		if ((h.isNegative == 1 && this->isNegative == 1 && this->compareTo(h) > 0) || (h.isNegative == 0 && this->isNegative == 0 && this->compareTo(h) < 0)){ //num2 holds the SMALLER value

				num2 = huge;
				num1 = h.huge;
			}
			else{
				num2 = h.huge;
				num1 = huge;
			}
	}


	std::reverse(num1.begin(), num1.end());  //reverse both strings as it is needed for our algorithm implementation
	std::reverse(num2.begin(), num2.end());

	for (int i = 0; i < num2.size(); i++){          //loop through till the end of the smaller string finding out the difference one by one.

		temp_diff = num1[i] - num2[i] - carry;   //store it in a variable called temp diff

		if (temp_diff < 0){                      //if temp diff is negative, we know we will have a carry.
			temp_diff = temp_diff + 10;          // temp_diff needs to be appended so add 10 and store it.
			carry = 1;
		}
		else{
			carry = 0;
		}
		diff.push_back(temp_diff);               //append temp diff
	}

	for (int i = num2.size(); i < num1.size(); i++){            //drop the rest of our values down, remaining indicies after looping through the smaller number
		temp_diff = num1[i] - carry;

		if (temp_diff < 0){
			temp_diff = temp_diff + 10;
			carry = 1;
		}
		else{
			carry = 0;
		}
		diff.push_back(temp_diff);
	}
	std::reverse(diff.begin(), diff.end());           // we now have our difference integer vector, but we must reverse it to give us an actual number

	while (diff[0] == 0){                           //eliminate any leading 0's
			diff.erase(diff.begin());
		}
	HugeInteger res(diff);                             //duplicate difference to result

	if (compareTo(h) < 0){                  //in both remaining cases, + (-) + and - (-) -, if huge is smaller than h we will get a negative value. Therefore, set res.isNegative true.
		res.isNegative = 1;
	}
	return res;


}

HugeInteger HugeInteger::multiply(const HugeInteger& h) {

	int carry = 0, temp_prod = 0;             //initialize variables
	int h_size = h.huge.size();
	int huge_size = huge.size();

	int idx1 = 0;                             //initialize index counters
	int idx2 = 0;

	vector<int> product(h_size + huge_size, 0);   //initialize a integer vector with appropriate product size filled with 0's
	HugeInteger* res;                             //create a null pointer

	if (huge[0] == 0 || h.huge[0] == 0){          //if the first digit is 0, output will also be 0 cause x*0 = 0.
		return HugeInteger("0");
	}


	for (int i = (huge_size - 1); i >= 0; i--){   //iterate from the right side of the operand

		carry = 0;
		idx2 = 0;

		for (int j = (h_size - 1); j >= 0; j--){   //iterate from the right side of the operand
			temp_prod = huge[i] * h.huge[j] + product[idx1 + idx2] + carry;  //create a temp product which contains the digit we need at the end
			product[idx1 + idx2] = temp_prod % 10;  //digit is isolated for and appended
			carry = temp_prod/10;                //the carry value can be obtained by integer division of temp prod
			idx2++;                              //increment our index counter
		}
		if (carry > 0){
			product[idx1 + idx2] +=carry;        //now append our carry value into the next index
		}
		idx1++;                                  //increment second index counter
	}
	std::reverse(product.begin(), product.end());  //after looping is finished, we must reverse our product as it was made from left to right

	if (product[0] == 0){                          //get rid of leading 0's
		product.erase(product.begin());
	}

	HugeInteger* temp = new HugeInteger(product);  //creates a new HugeInteger of product and temp points to it
	res = temp;                                    // make res and temp point to the same thing

	 if ((this->isNegative == 1 && h.isNegative == 0) || (this->isNegative == 0 && h.isNegative == 1)){  //negative times positive is always negative

		 res->isNegative = 1;
	}

	return *res;    //dereference the pointer and return the object res was pointing to (product)
}

int HugeInteger::compareTo(const HugeInteger& h) {
	int flag = 0;
	int huge_size = huge.size();
	int h_size = h.huge.size();

	if (toString() == h.toString()){
		return 0;
	}

	if (isNegative == 0 && h.isNegative == 0){  //case where both are positive

		if (h_size > huge_size){
			flag = -1;
		}
		else if (h_size < huge_size){
			flag = 1;
		}
		else if (h_size == huge_size){
			if (h.huge[0] > huge[0]){
				flag = -1;
			}
			else{
				flag = 1;
			}
		}
	}

	else if (h.isNegative == 0 && isNegative == 1){  //cases when either one is positive and the other is negative
		flag = -1;
	}
	else if (h.isNegative == 1 && isNegative == 0){
		flag = 1;
	}
	else if (isNegative == 1 && h.isNegative == 1){ //case where both are negative

		if (h_size > huge_size){
			flag = 1;
		}
		else if (h_size < huge_size){
			flag = -1;
		}
		else if (h_size == huge_size){
			if (h.huge[0] > huge[0]){
				flag = 1;
			}
			else{
				flag = -1;
			}
		}
	}

	return flag;
}

std::string HugeInteger::toString() const{

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
