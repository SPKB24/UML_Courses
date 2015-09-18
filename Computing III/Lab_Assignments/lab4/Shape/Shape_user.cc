//**                                 **//
//                                     //
// PROGRAM NAME: Shape_user.cc         //
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
#include "Shape.h"

using namespace std;
#define ARR_SIZE_1 6
#define ARR_SIZE_2 2

typedef string Data;

void testCase1(void)
{
	// Allocate memory for an array of Shape pointers
	Shape** tester = new Shape*[ARR_SIZE_1];
	int count = 0;

	if (tester == NULL)
		cout << "Error: Out of Memory" << endl;

	// All given valid parameters
	Circle      _circle(50);
	Square      _square(5);
	Triangle    _triangle(100, 50);
	Sphere      _sphere(50);
	Cube        _cube(5);
	Tetrahedron _tetrahedron(5, 15, 5, 15, 5, 15, 5, 5);

	// Insert shapes into array
	tester[count++] = &_circle;
	tester[count++] = &_square;
	tester[count++] = &_triangle;
	tester[count++] = &_sphere;
	tester[count++] = &_cube;
	tester[count++] = &_tetrahedron;

	// Print out all information
	for (int i = 0; i < count; i++)
	{
		cout << "------------------------" << endl; // Format
		cout << " " << tester[i]->getName(); // Shape Name

		if (tester[i]->isTwoDimentional()) // Shape Type
			cout << " | 2D SHAPE" << endl;
		else
			cout << " | 3D SHAPE" << endl;

		cout << "------------------------" << endl; // Format
		cout << "SPECIFICATIONS" << endl;
		tester[i]->printSizes();

		cout << endl << "AREA = " << tester[i]->getArea() << endl;

		if (!tester[i]->isTwoDimentional())
			cout << "VOLUME = " << tester[i]->getVolume() << endl;

		cout << endl;
	}

	// Deallocate Memory
	delete[] tester;
	tester = NULL;
}

void testCase2(void)
{
	// Allocate memory for an array of Shape pointers
	Shape** tester = new Shape*[ARR_SIZE_2];
	int count = 0;

	if (tester == NULL)
		cout << "Error: Out of Memory" << endl;

	// _circle constructed with radius -4, which is invalid
	// radius should become 10 to avoid errors
	Circle _circle(-4);

	// _tetrahedron constructed with both valid and invalid values
	// All invalid values should become 10, valid should remain
	Tetrahedron _tetrahedron(0, 1, -4, 5, 23, -6, 2, -6);

	// Insert shapes into array
	tester[count++] = &_circle;
	tester[count++] = &_tetrahedron;

	// Print out all info, should work even with invalid params
	for (int i = 0; i < count; i++)
	{
		cout << "------------------------" << endl;
		cout << " " << tester[i]->getName();

		if (tester[i]->isTwoDimentional())
			cout << " | 2D SHAPE" << endl;
		else
			cout << " | 3D SHAPE" << endl;

		cout << "------------------------" << endl;
		cout << "SPECIFICATIONS" << endl;
		tester[i]->printSizes();

		cout << endl << "AREA = " << tester[i]->getArea() << endl;

		if (!tester[i]->isTwoDimentional())
			cout << "VOLUME = " << tester[i]->getVolume() << endl;

		cout << endl;
	}

	// Deallocate Memory
	delete[] tester;
	tester = NULL;
}

int main()
{
	cout << "**************************" << endl
		 << "TEST CASE 1 | VALID PARAMS" << endl
		 << "**************************" << endl;
	testCase1();

	cout << "****************************" << endl
		 << "TEST CASE 2 | INVALID PARAMS" << endl
		 << "****************************" << endl;
	testCase2();


	return 0;
}
