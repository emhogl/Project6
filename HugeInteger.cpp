#include "HugeInteger.h"
#include <exception> //for throwing exceptions
#include <cstdlib> //for random number


HugeInteger::HugeInteger(const std::string& val) { //DO
	// TODO
	positive=true;
	int stop;

	//if (val.size()>=2 && val[0]=='-' && val[1])
	if (val[0]=='-' && val.size()>1 && '1'<=val[1] && '9'>=val[1]) { //what if they enter just a -
	    positive=false;
	    stop=1;
	}
	else if ('1'<=val[0] && '9'>=val[0] && val.size()>1) {
	    stop=0;
	}

	else if ('0'<=val[0] && val.size()==1) {
	    stop=0;
	}

	else {
	    throw std::invalid_argument("Input is invalid, must enter a valid integer.");
	}

	for (int i=val.size()-1; i>=stop; i--) {

	    if ('0'<=val[i] && '9'>=val[i]) { //val within range of integer
	        int diff = val[i]-'0';
	        digits.push_back(diff);
	    }
	    else { //throw exception
	        throw std::invalid_argument("Input includes non-integer characters."); //think this works?
	    }

	}
}

HugeInteger::HugeInteger(int n) { //DO
	// TODO
	if (n<=0) {
	    throw std::invalid_argument("Cannot create an integer with less than or 0 numbers.");
	}

	else {
	    //"coin flip" for sign
    	if (rand()%2 == 0) {
    	    positive = true;
    	}
    	else {
    	    positive = false;
    	}

    	//random numbers for each

    	//srand()%10 //get 0-9
    	//srand()%8+1 //get 1-9

    	for (int i=0; i<n; i++) {
    	    if (i==n-1) { //first digit (stored last in vector) only between 1-9
    	        digits.push_back(rand()%9+1); //pushback goes to the end
    	    }
    	    else { //all other digits between 0-9
    	        digits.push_back(rand()%10);
    	    }
    	}
	}
}

HugeInteger HugeInteger::absAdd(const HugeInteger& num1, const HugeInteger& num2) { //only handles positive integer addition
	// TODO
	int upper; //stores larger size of two integers
	int lower; //stores smaller size of two integers

	int count = 0; //used for carrying the one

	int whichIsBigger = 0; //flag for which integer is bigger

	HugeInteger IntSum; //huge int to carry summation

	//Determine which integer is bigger
    if (num1.digits.size()>=num2.digits.size()) {
        upper = num1.digits.size();
        lower = num2.digits.size();
        whichIsBigger = 0; //0 if num1 huge integer is bigger
    }

    else {
        upper = num2.digits.size();
        lower = num1.digits.size();
        whichIsBigger = 1; //1 if num2 huge integer is bigger
    }

    //Addition up until last digit of smaller integer
    for (int i=0; i<lower; i++) {
	    int temp = num1.digits[i]+num2.digits[i]+count;

	    count=temp/10; //integer division rounds down; gives the carried one
	    temp=temp%10; //gives the remainder

	    IntSum.digits.push_back(temp); //push back the result of temp

	}

    //Addition for the remaining bigger number
	for (int j=lower; j<upper; j++) {

	    if (whichIsBigger==0) { //this huge integer is bigger
	        int temp = num1.digits[j]+count;

    	    count=temp/10; //integer division rounds down
    	    temp=temp%10; //gives the remainder

    	    IntSum.digits.push_back(temp);
	    }
	    else { //input huge integer is bigger
	        int temp = num2.digits[j]+count;

    	    count=temp/10; //integer division rounds down
    	    temp=temp%10; //gives the remainder

    	    IntSum.digits.push_back(temp);
	    }
	}

	//Adds final carried one if necessary
	if (count!=0) {
	    IntSum.digits.push_back(count);
	}

	//Return huge int carrying the sum
	return IntSum;
}


HugeInteger HugeInteger::absSubtract(const HugeInteger& num1, const HugeInteger& num2) { //only handles bigger/same number magnitude - smaller/same number magnitude
    int borrow=0;
    HugeInteger IntDiff;

    //assumes that num2 has a smaller magnitude
    for (unsigned int i=0; i<num2.digits.size(); i++) {
    	if ((num1.digits[i]-borrow)<num2.digits[i]) {
            IntDiff.digits.push_back((num1.digits[i]-borrow)+10 - num2.digits[i]);

            if (i+1<num1.digits.size() && num1.digits[i+1]==0) { //handles case where borrowing from a 0
            	borrow = -9;
            }
            else { //handles all other cases
            	borrow=1;
            }

        }
        else {
            IntDiff.digits.push_back((num1.digits[i]-borrow) - num2.digits[i]);

            if (num1.digits[i]==0 && borrow==-9) { //handles case when borrowed from 0
            	if (i+1<num1.digits.size() && num1.digits[i+1]==0) { //if the next digits is a 0, still need borrow -9
            		borrow = -9;
            	}
            	else { //otherwise just needs to borrow 1
            		borrow=1;
            	}
			}
			else { //no borrow required m
				borrow=0;
			}
        }
    }

    for (unsigned int j=num2.digits.size(); j<num1.digits.size(); j++) { //any extra digits
        IntDiff.digits.push_back(num1.digits[j]-borrow); //must still consider remaining borrow
        if (num1.digits[j]==0 && borrow==-9) { //handles 0 case
        	if (j+1<num1.digits.size() && num1.digits[j+1]==0) { //if the next number is also a 0, need borrow -9
        		borrow = -9;
        	}
        	else if (j+1<num1.digits.size() && num1.digits[j+1]!=0) { //if the next number is non-zero, can just borrow 1
        		borrow=1;
        	}
		}
		else { //otherwise, no borrow required
			borrow=0;
		}

    }

    //remove any 0 that are unnecessary in the front of the huge integer
    int k = IntDiff.digits.size()-1;
    while (IntDiff.digits[k] == 0 && k != 0) {
        IntDiff.digits.pop_back();
        k--;
    }

    return IntDiff; //return the difference
}

int HugeInteger::absVal(const HugeInteger& h)  { //compareTo function without considering sign

	//compare the size
	if (this->digits.size()<h.digits.size()) {
		return -1;
	}
	else if (this->digits.size()>h.digits.size()) {
		return 1;
	}
	else { //if the size is the same, loop through the digits to compare
		for (unsigned int i=1; i<=this->digits.size(); i++) {
			if (this->digits[this->digits.size()-i]<h.digits[h.digits.size()-i]) {
				return -1;
			}
			else if (this->digits[this->digits.size()-i]>h.digits[h.digits.size()-i]) {
				return 1;
			}
		}
	}
    return 0; //returns 0 if the numbers are the same (not considering the sign)
}

HugeInteger HugeInteger::add(const HugeInteger& h) { //change to handling negative
	// TODO
    HugeInteger intSum;

    //both positive
	if (positive==true && h.positive==true) {
	    intSum = absAdd(*this, h);
	    intSum.positive=true;
	}

	//this negative, input positive
    else if (positive==false && h.positive==true) {
	    if(absVal(h)>0) {  //this is bigger than h
	        intSum = absSubtract(*this, h);
	        intSum.positive = false;
	    }
	    else if (absVal(h)<0) { //h is bigger than this
	        intSum = absSubtract(h, *this);
	        intSum.positive = true;
	    }

	    else { //same number
	        intSum.digits.push_back(0); //number is just 0
	        intSum.positive=true; //consider positive
	    }

    }

    //this positive, input negative
    else if (positive==true && h.positive==false) {
	    if(absVal(h)>0) {  //this is bigger than h
	        intSum = absSubtract(*this, h);
	        intSum.positive = true;
	    }
	    else if (absVal(h)<0) { //h is bigger than this
	        intSum = absSubtract(h, *this); //h-this
	        intSum.positive = false;
	    }

	    else {
	        intSum.digits.push_back(0);
	        intSum.positive=true;
	    }

    }

	//both negative
	else if (positive==false && h.positive==false) {
        intSum = absAdd(h, *this); //h+this
        intSum.positive = false;
    }

	if (intSum.digits[0]==0 && intSum.digits.size()==1 && intSum.positive==false) {
		intSum.positive=true;
	}

	return intSum;
}

HugeInteger HugeInteger::subtract(const HugeInteger& h) { //this is 5, input is 10
	// TODO
	HugeInteger intDiff;

	//both positive
	if (positive==true && h.positive==true) {
	    if(absVal(h)>0) {  //this is bigger than h
	    	intDiff = absSubtract(*this, h); //this-h
	    	intDiff.positive = true;
	    }

	    else if (absVal(h)<0) { //h is bigger than this
	    	intDiff = absSubtract(h, *this); //h-this
	    	intDiff.positive = false;
	    }

	    else {
	    	intDiff.digits.push_back(0);
	    	intDiff.positive=true;
	    }
	}

	//this negative, input positive
    else if (positive==false && h.positive==true) {
    	intDiff = absAdd(*this, h);
    	intDiff.positive = false;
    }

    //this positive, input negative
    else if (positive==true && h.positive==false) {
    	intDiff = absAdd(*this, h);
    	intDiff.positive = true;
    }

	//both negative
	else {
	    if(absVal(h)>0) {
	    	intDiff = absSubtract(*this, h);
	    	intDiff.positive = false;

	    }
	    else if (absVal(h)<0) { //5 - 10 = -[10(input) - 5(this)]
	    	intDiff = absSubtract(h, *this);
	    	intDiff.positive = true;
	    }

	    else {
	    	intDiff.digits.push_back(0);
	    	intDiff.positive=true;
	    }
    }
	if (intDiff.digits[0]==0 && intDiff.positive==false && intDiff.digits.size()==1) {
		intDiff.positive=true;
	}
	return intDiff; //return difference
}

HugeInteger HugeInteger::multiply(const HugeInteger& h) {
	// TODO
	HugeInteger IntMult;

    if (digits[digits.size()-1]==0 || h.digits[h.digits.size()-1]==0) {
    	IntMult.digits.push_back(0);
    	IntMult.positive=true;
    	return IntMult;
    }

	int zeroCount = 0; //place value of where you want to start adding !!!
	int carry = 0;
	int value = 0;

	for (unsigned int i=0; i<digits.size(); i++) {
		HugeInteger temp; //creates temporary hugeint
		carry=0;
		for (int k=0; k<zeroCount; k++) { //zeroCount increases each time, so the number of zeroes increase each time
	       temp.digits.push_back(0);
	    }
	    for (unsigned int j=0; j<h.digits.size(); j++) {
	        int intermed = h.digits[j]*digits[i]+carry; //multiply and add carry
	        carry = intermed/10; //find carry
	        value = intermed%10; //find value to push back
	        temp.digits.push_back(value); //push back the value into the temp hugeint
	    	if (j==h.digits.size()-1 && carry!=0) { //add carry if it is nonzero and at the last place
	    		temp.digits.push_back(carry);
	    	}

	    }
	    IntMult = IntMult.add(temp); //adds temporary hugeint to the resulting hugeint
	    zeroCount++;

	}

	//determine sign
	if (positive == true && h.positive == true) {
	    IntMult.positive = true;
	}
	else if (positive == false && h.positive == false) {
	    IntMult.positive = true;
	}
	else {
	    IntMult.positive = false;
	}

	if (IntMult.digits[0]==0 && IntMult.positive==false && IntMult.digits.size()==1) { //make sure that a negative sign does not print
		IntMult.positive=true;
	}

	return IntMult; //return product
}


int HugeInteger::compareTo(const HugeInteger& h) {
	// TODO
	if (this->positive==false && h.positive==true){ //this is negative, h is positive
		return -1;
	}
	else if (this->positive==true && h.positive==false){ //this is positive, h is negative
		return 1;
	}
	else if (this->positive==true && h.positive==true){ //both positive --> most compare digits
		if (this->digits.size()<h.digits.size()) {
			return -1;
		}
		else if (this->digits.size()>h.digits.size()) {
			return 1;
		}
		else {
			for (unsigned int i=1; i<=this->digits.size(); i++) {
				if (this->digits[this->digits.size()-i]<h.digits[h.digits.size()-i]) {
					return -1;
				}
				else if (this->digits[this->digits.size()-i]>h.digits[h.digits.size()-i]) {
					return 1;
				}
			}
		}
	}

	else if (this->positive==false && h.positive==false){ //both negative --> must compare digits
		if (this->digits.size()>h.digits.size()) {
			return -1;
		}
		else if (this->digits.size()<h.digits.size()) {
			return 1;
		}
		else {
			for (unsigned int i=1; i<=this->digits.size(); i++) {
				if (this->digits[this->digits.size()-i]>h.digits[h.digits.size()-i]) {
					return -1;
				}
				else if (this->digits[this->digits.size()-i]<h.digits[h.digits.size()-i]) {
					return 1;
				}
			}
		}
	}
    return 0; //returns 0 if they are the same number
}



std::string HugeInteger::toString() {
	// TODO
	std::string number="";

	if (this->positive == false) {
		number = '-';
	}

	for (unsigned int i=1; i<=digits.size(); i++) {
	    number += (digits[digits.size()-i]+'0'); //+'0' makes it a string
	}

	return number;
}




