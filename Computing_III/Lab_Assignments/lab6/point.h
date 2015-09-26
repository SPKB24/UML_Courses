//**                                 **//
//                                     //
// PROGRAM NAME: point.h               //
//                                     //
// AUTHOR: Sohit Pal                   //
//                                     //
// ### ### # # ### ###     ###  #  #   //
// #   # # # #  #   #      # # # # #   //
// ### # # ###  #   #      ### ### #   //
//   # # # # #  #   #      #   # # #   //
// ### ### # # ###  #      #   # # ### //
//                                     //
// DATE: May 1, 2015                   //
//                                     //
//**                                 **//

#ifndef POINT_H
#define POINT_H

#include <iostream>
using namespace std;

/*

-------------------------  ------------------------- 
| 0,0 | 0,1 | 0,2 | 0,3 |  |  0  |  1  |  2  |  3  |
-------------------------  -------------------------
| 1,0 | 1,1 | 1,2 | 1,3 |  |  1  |  0  |  1  |  2  |
-------------------------  -------------------------
| 2,0 | 2,1 | 2,2 | 2,3 |  |  2  |  1  |  0  |  1  |
-------------------------  -------------------------
| 3,0 | 3,1 | 3,2 | 3,3 |  |  3  |  2  |  1  |  0  |
-------------------------  -------------------------

*/

class Point
{
public:
	// Default Constructor
	Point(int _dimension = 2)
	{
		if (_dimension < 1)
			_dimension = 2;

		dimension = _dimension;

		coordinates = new double[dimension];

		if (coordinates == NULL)
		{
			cout << "Error: Out of Memory" << endl;
			exit(1);
		}

		for (int i = 0; i < dimension; i++)
			coordinates[i] = 0;
	}

	// Int and Array Constructor
	Point(int _dimension, vector<double> _array)
	{
		dimension = _dimension;
		coordinates = new double[dimension];

		if (coordinates == NULL)
		{
			cout << "Error: Out of Memory" << endl;
			exit(1);
		}

		for (int i = 0; i < dimension; i++)
			coordinates[i] = _array[i];
	}

	// Copy Constructor
	Point(const Point& rhs)
	{
		if (coordinates)
			coordinates = NULL;

		if (coordinates == NULL)
		{
			coordinates = new double[rhs.dimension];
			dimension = rhs.dimension;
		}

		if (rhs.coordinates && dimension == rhs.dimension && coordinates)
			for (int i = 0; i < rhs.dimension; i++)
				coordinates[i] = rhs.coordinates[i];
		else
			coordinates = NULL;
	}

	// Assignment Operator
	Point& operator=(const Point& arg)
	{
		if (dimension != arg.dimension)
		{
			cout << "ERROR: Dimension numbers are not equivalent" << endl;
			exit(1);
		}

		if (arg.coordinates && dimension == arg.dimension)
			for (int i = 0; i < arg.dimension; i++)
				coordinates[i] = arg.coordinates[i];
		else
			coordinates = NULL;

		return *this;
	}

	// Addition Operator
	Point operator+(const Point &arg)
	{
		if (dimension != arg.dimension)
		{
			cout << "Dimensionality mismatch for Point operator+" << endl;
			exit(1);
		}

		Point rval(dimension);

		for (int i = 0; i < dimension; i++)
			rval.coordinates[i] = coordinates[i] + arg.coordinates[i];

		return rval;
	}

	// Print out all coordinates in the point
	void printAll()
	{
		for (int i = 0; i < dimension; i++)
			cout << coordinates[i] << " ";
		cout << endl;
	}

	double findAverage()
	{
		double sum = 0;

		for (int i = 0; i < dimension; i++)
			sum += coordinates[i];

		return sum/dimension;
	}

	int getDimension()
	{
		return dimension;
	}

	// Destructor
	~Point()
	{
		delete[] coordinates;
		coordinates = NULL;
	}

private:
	double *coordinates;
	int dimension;
};

#endif
