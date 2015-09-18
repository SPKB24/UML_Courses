//**                                 **//
//                                     //
// PROGRAM NAME: Polynomial_user.cc    //
//                                     //
// AUTHOR: Sohit Pal                   //
//                                     //
// ### ### # # ### ###     ###  #  #   //
// #   # # # #  #   #      # # # # #   //
// ### # # ###  #   #      ### ### #   //
//   # # # # #  #   #      #   # # #   //
// ### ### # # ###  #      #   # # ### //
//                                     //
// DATE: April 15, 2015                //
//                                     //
//**                                 **//

#include <iostream>
#include "Polynomial.h"
using namespace std;

// Simply create polynomials and test
void test1()
{
	cout << "** TEST 1 **" << endl;

	Polynomial a; // Default Constructor

	//Set (coefficient, exponent)
	a.addTerm(   2,         6); // New Terms in order
	a.addTerm(   3,         4); // Largest Exp in front
	a.addTerm(   5,         2); // Smallest Exp in back

	cout << "A: ";
	a.printAll(); // Print out Polynomial A

	cout << endl;
}

// Create polynomials and try out operators
void test2()
{
	cout << endl << "** TEST 2 **" << endl;

	Polynomial a; // Default Constructor
	Polynomial b; // Default Constructor

	a.addTerm(2, 4); // New Terms in order
	a.addTerm(2, 3); // Largest Exp in front
	a.addTerm(2, 2); // Smallest Exp in back

	b.addTerm(2, 6); // Same as above
	b.addTerm(3, 4); 
	b.addTerm(5, 2); 

	cout << "A: ";
	a.printAll(); // Print out Polynomial A
	cout << endl;

	cout << "B: ";
	b.printAll(); // Print out Polynomial B
	cout << endl;

	cout << "A + B: ";
	(a+b).printAll(); // Print out Polynomial A + B
	cout << endl;

	cout << "A - B: ";
	(a-b).printAll(); // Print out Polynomial A - B
	cout << endl;

	cout << endl;
}

// Create Polynomials with boundary issues
void test3()
{
	cout << endl << "** TEST 3 **" << endl;

	Polynomial a; // Default Constructor
	Polynomial b; // Default Constructor

	a.addTerm( 2,  6); //  
	a.addTerm( 3,  4); // 
	a.addTerm( 5, -2); // Negative Exponents not allowed

	cout << "A: ";
	a.printAll(); // Print out Polynomial A
	cout << endl;

	b = a; // Assignment Operator

	cout << "B: ";
	b.printAll();
	cout << endl;

	cout << endl;
}

int main()
{
	test1();
	test2();
	test3();

	return 0;
}
