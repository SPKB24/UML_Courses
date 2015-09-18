//**                                 **//
//                                     //
// PROGRAM NAME: lab1p3.cc             //
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

#include <iostream> 
// Used to input/output to/from the console

#include <stdio.h>  
// Used to find EOF

using namespace std;

int findFactorial(int num);
// Find the factorial of any number given as parameter num
// ex. findFactorial(5) will return 120 with parameter num = 5

int main(int argc, char * argv[])
{
	int userChoice;     // Holds number that user wants to find factorial of
	bool isInt = false; // To dictate that user gave correct input for userChoice

	cout << "---------------------" << endl;
        cout << "lab1p3.cc | FACTORIAL" << endl;
        cout << "---------------------" << endl;

	cout << "Enter a number: ";

	while (!isInt)
	{
		cin >> userChoice;

		if (!cin.fail() && (cin.peek() == EOF || cin.peek() == '\n'))
			isInt = true;
		else //Clear Buffer and try again
		{
			cin.clear();
			cin.ignore(256, '\n');
			cout << "Error, Please enter a number: ";
		}
	}

	if (userChoice <= 16)
		cout << "The factorial of " << userChoice << " is "
		     << findFactorial(userChoice) << "." << endl;
	else
		cout << "The factorial of " << userChoice << " is "
		     << "a very large number." << endl;

	cout << "---------------------" << endl;

	return 0;
}

int findFactorial(int num) /* This function is used to find the factorial of an int num */
{
	int answer = 1;

	for (int i = 1; i <= num; i++)
		answer = answer * i;

	return answer;
}

