#ifndef HUGEINTEGER_H_
#define HUGEINTEGER_H_
#include <iostream>
#include <vector>
#include <string> //I don't think I need this

class HugeInteger
{
private:
	std::vector<int> digits; //contains digits in reverse order
	bool positive; //T positive, F negative
	//supports other cases
	int absVal(const HugeInteger& h);
	HugeInteger absAdd(const HugeInteger& num1, const HugeInteger& num2);
	HugeInteger absSubtract(const HugeInteger& num1, const HugeInteger& num2);


public:
	// Required methods
	HugeInteger() { //default constructor
	    digits = {};
	    positive = true;
	}

	HugeInteger(const std::string& val);
	HugeInteger(int n);



	int whichIsBigger(const HugeInteger& h);

    HugeInteger add(const HugeInteger& h);
	HugeInteger subtract(const HugeInteger& h);

	HugeInteger multiply(const HugeInteger& h);
	int compareTo(const HugeInteger& h);
	std::string toString();


};

#endif /* HUGEINTEGER_H_ */
