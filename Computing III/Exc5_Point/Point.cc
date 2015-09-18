#include <iostream>
#include "Point.h"

using namespace std;

Point::Point(int _dimension)
{
	cout << "DEFAULT CONSTRUCTOR CALLED" << endl;

	if (_dimension < 1)
		_dimension = 2;

	dimension = _dimension;

	coordinates = new double[dimension];

	if (coordinates == NULL)
		cout << "Error: Out of Memory" << endl;

	for (int i = 0; i < dimension; i++)
		coordinates[i] = 0;
}

// Int and Array Constructor
Point::Point(int _dimension, double *_array)
{
	cout << "CUSTOM CONSTRUCTOR CALLED" << endl;


	dimension = _dimension;
	coordinates = new double[dimension];

	if (coordinates == NULL)
		cout << "Error: Out of Memory" << endl;

	for (int i = 0; i < dimension; i++)
		coordinates[i] = _array[i];
}

// Copy Constructor
Point::Point(const Point& rhs)
{
	cout << "COPY CONSTRUCTOR CALLED" << endl;

	if (rhs.coordinates && dimension == rhs.dimension)
		for (int i = 0; i < rhs.dimension; i++)
			coordinates[i] = rhs.coordinates[i];
	else
		coordinates = NULL;
}

// Operator()
double Point::operator[] (size_t index)
{
	if (index >= 0 && index < dimension)
		return coordinates[index];

	return NULL;
}

// Assignment Operator
Point& Point::operator=(const Point& arg)
{
	cout << "OPERATOR= CALLED" << endl;

	if (dimension != arg.dimension)
        {
                cout << "ERROR: Dimension sizes do not match up" << endl;
                return *this;
        }

	if (arg.coordinates && dimension == arg.dimension)
		for (int i = 0; i < arg.dimension; i++)
			coordinates[i] = arg.coordinates[i];
	else
		coordinates = NULL;

	return *this;
}

// Addition Operator
Point Point::operator+(const Point &arg)
{
	cout << "OPERATOR+ CALLED" << endl;

	if (dimension != arg.dimension)
	{
		cout << "ERROR: Dimension sizes do not match up" << endl;
		return *this;
	}

	Point rval(dimension);

	for (int i = 0; i < dimension; i++)
		rval.coordinates[i] = coordinates[i] + arg.coordinates[i];

	return rval;
}

// Sum Equals operator
Point& Point::operator+=(const Point &arg)
{
	cout << "OPERATOR+= CALLED" << endl;

	if (dimension != arg.dimension)
        {
                cout << "ERROR: Dimension sizes do not match up" << endl;
                return *this;
        }

	for (int i = 0; i < dimension; i++)
		coordinates[i] += arg.coordinates[i];

	return *this;
}

// Print out all coordinates in the point
void Point::printAll()
{
	for (int i = 0; i < dimension; i++)
		cout << "Point " << i << " = " << coordinates[i] << endl;
}

// Destructor
Point::~Point()
{
	cout << "DESTRUCTOR CALLED" << endl;

	delete[] coordinates;
	coordinates = NULL;
}
