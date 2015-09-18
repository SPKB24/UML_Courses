#ifndef POINT_H
#define POINT_H

#include <iostream>
using namespace std;

class Point
{
public:
	// Default Constructor
	Point(int _dimension = 2);

	// Int and Array Constructor
	Point(int _dimension, double *_array);

	// Copy Constructor
	Point(const Point& rhs);

	// Operator()
	double operator[] (size_t index);

	// Assignment Operator
	Point& operator=(const Point& arg);

	// Addition Operator
	Point operator+(const Point &arg);

	// Sum Equals operator
	Point &operator+=(const Point &arg);

	// Print out all coordinates in the point
	void printAll();

	// Destructor
	~Point();

	friend ostream & operator<<(ostream &output, const Point &arg)
	{
		for (int i = 0; i < arg.dimension; i++)
			cout << "Point " << i << " = " << arg.coordinates[i] << endl;

		return cout;
	}

private:
	double *coordinates;
	int dimension;
};

#endif
