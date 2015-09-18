//**                                 **//
//                                     //
// PROGRAM NAME: lab1p5.cc             //
//                                     //
// AUTHOR: Sohit Pal                   //
//                                     //
//  ##  #  # # ### ###     ##   #  #   //
// #   # # # #  #   #      # # # # #   //
//  #  # # ###  #   #      ##  ### #   //
//   # # # # #  #   #      #   # # #   //
// ##   #  # # ###  #      #   # # ### //
//                                     //
// DATE: February 5, 2014              //
//                                     //
//**                                 **//

#include <iostream> /* This is used to input/output to/from the console */
#include <cmath>    /* This is used to find the power of a base using the pow() function */
#include <stdio.h>  /* This is used to find  EOF */
using namespace std;

int main(int argc, char * argv[])
{
	int base, power;                          // Hold values for base/power number
	bool basePass = false, powerPass = false; // To dicate that user gave correct input for base and power

	cout << "------------------------" << endl;
        cout << "lab1p4.cc | POWER FINDER" << endl;
        cout << "------------------------" << endl;
	
	cout << "Please enter a base number: ";
	
	while(!basePass)
	{
		cin >> base;
		
		if(!cin.fail() && (cin.peek() == EOF || cin.peek() == '\n'))
			basePass = true;
		else //Clear Buffer and try again
		{
			cin.clear();
			cin.ignore(256, '\n');
			cout << "Error, please enter a base number: ";
		}
	}

	cout << "Please enter a power to raise " << base << " by: ";
	
	while(!powerPass)
	{	
		cin >> power;
	
		if(!cin.fail() && (cin.peek() == EOF || cin.peek() == '\n'))
			powerPass = true;
		else //Clear Buffer and try again
		{
			cin.clear();
			cin.ignore(256, '\n');
			cout << "Error, please enter a power to raise " << base << " by: ";
		}
	}

	cout << "Your answer is " << pow(base, power) << endl;

	cout << "------------------------" << endl;

	return 0;
}
