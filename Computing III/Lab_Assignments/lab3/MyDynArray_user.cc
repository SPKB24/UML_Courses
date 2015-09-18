//**                                 **//
//                                     //
// PROGRAM NAME: MyDynArray_user.cc    //
//                                     //
// AUTHOR: Sohit Pal                   //
//                                     //
// ### ### # # ### ###     ###  #  #   //
// #   # # # #  #   #      # # # # #   //
// ### # # ###  #   #      ### ### #   //
//   # # # # #  #   #      #   # # #   //
// ### ### # # ###  #      #   # # ### //
//                                     //
// DATE: March 20, 2014                //
//                                     //
//**                                 **//

#include <iostream>
#include <string>
#include "MyDynArray.h"

using namespace std;

// Print the given array
void print(MyDynArray& a, string prefix = "")
{
	int arrSize = a.getSize();
	
	cout << "Get Function called " << arrSize << " times: ";

	for (int i = 0; i < arrSize; i++)
		cout << a.get(i) << " ";
	cout << endl;
}

// Program to test all functions with valid params
void runProgram()
{
	cout << "*****************************" << endl;
	cout << "********* PROGRAM 1 *********" << endl;
	cout << "*****************************" << endl;

	MyDynArray a(10); // Call Default Constructor
	MyDynArray b(10); // Call Default Constructor

	cout << "Size of Array a is " << a.getSize() << endl; 
	cout << "Size of Array b is " << b.getSize() << endl; // Get Size of b

	/* Fill in values for Array a | Should pass for all */
	for (size_t i = 0; i < a.getSize(); i++)
		a.set(i + 1, i);

	b = a; // Call Assignment Operator (same size for both)

	print(a, "a"); // Print a and b
	print(b, "b"); // They should be the same

	a.set(300, 13); // Set index 13 to 300

	MyDynArray c = a; // Call Copy Constructor

	print(a, "a"); // Print a and c
	print(c, "c"); // They should be the same

	//Destructors for DynArray's a, b, c should be called
}

// Program to test all functions with invalid params
void runProgram2()
{
	cout << endl;

	cout << "*****************************" << endl;
	cout << "********* PROGRAM 2 *********" << endl;
	cout << "*****************************" << endl;

	// Call Default Constructor
	MyDynArray a(10);

	// Out of bounds index | Should increase size
	a.set(300, 11);

	// Should show Array a with size = 20
	print(a, "a");

	// Call Default Construcor
	MyDynArray b(10);

	// Call Assignment Operator (different sizes)
	b = a; 

	cout << "Get Function called 1 time: ";
	
	// Out of bounds index | Should print error
	a.get(20); 

	cout << endl;

	//Destructors for DynArray's a, b should be called
}

int main()
{
	runProgram(); // Program to test all functions with valid params
	runProgram2(); // Program to test all functions with invalid params
	
	return 0;
}
