#include <iostream>
#include "Point.h"

using namespace std;

void testProg1() // Function checks | Everything should run smoothly
{
	double arr[] = { 3.2, 10, 5.35 }; // Array of values
	Point a(3); // Set to 3D by user input
	Point b(3, arr); // Set to 3D and filled with Array values
	Point c(3); // Set to 3D by user input

	a = b; // Asignment Operator
	c = a; // Assignment Operator
	c += c; // Sum equals Operator

	/* Print coordinates from all points */
	cout << endl << "Print Coordinates in Point a" << endl << a	
	     << endl << "Print Coordinates in Point b" << endl << b
	     << endl << "Print Coordinates in Point c" << endl << c << endl;
}

void testProg2() // Boundary and Fail Checks | Should catch exception
{
	double arr[] = { 3.2, 10, 5.35 };
	Point a;    // Set to 2D by default 
	Point b(3, arr); // Set to 3D by user input

	a = b; // Try assignment operator, should print error

	cout << endl << "Print Coordinates in Point a" << endl << a
		 << endl << "Print Coordinates in Point b" << endl << b << endl;
}

int main(int argc, char * argv[])
{
	cout << "********************" << endl
		 << "   TEST PROGRAM 1   " << endl
		 << "********************" << endl;
	testProg1();

	cout << endl;
	cout << "********************" << endl
		 << "   TEST PROGRAM 2   " << endl
		 << "********************" << endl;
	testProg2();

	return 0;
}
