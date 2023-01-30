/*
 * Lab1&2.cpp
 *
 *  Created on: Jan. 30, 2022
 *      Author: emma
 */

#include <iostream>
#include "TestHugeInteger.h"

using namespace std;

int main() {

    // when test failed, the size of number <= NUM_DISPLAY, display the number
    unsigned int num_display = 1000;
    // iterate the MAX_SIZE_ARRAY MAX_RUN times
    //unsigned int max_run = 50; I CHANGED THIS

    unsigned int max_run = 25;

    // use for generating invalid string for constructor 1 (with string input)
    unsigned int max_invalid_string = 5; //I changed this

    //unsigned int max_invalid_string = 1;

    // different size for test
    //I changed from this:
    //vector<int> max_size_array = {1,20,50,500,5000};

	//to this:
    vector<int> max_size_array = {1,20,50,500};


    double totalMark = 0;

    string demoLab = "Lab2"; // set to Lab1 or Lab2

    TestHugeInteger thi(num_display, max_run, max_invalid_string, max_size_array);

    if (demoLab == "Lab1"){
        totalMark += thi.testConstructorString();
        totalMark += thi.testConstructorNumber();
        totalMark += thi.testPositiveAddition();
    }else{
        totalMark += thi.testAdditionSubtraction();
        //std::cout<<"End here"<<std::endl;
        totalMark += thi.testCompareTo();
        totalMark += thi.testMultiplication();
    }

    cout << "******************************" << endl;
    cout << "*** FINAL TOTAL MARK IS " << totalMark << " ***" << endl;
    cout << "******************************" << endl;


	return 0;
}
