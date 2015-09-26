#ifndef MATHVECTOR_H
#define MATHVECTOR_H

#include <iostream>
using namespace std;

class MathVector
{
public:
	// Int Constructor
	MathVector(int dimensions = 2)
	{
		if(dimensions < 1)
			dimensions = 2;
		
		// Create # Dimensional Array, user defined
		ArrPtr = new double[dimensions];

		if(ArrPtr == NULL)
			cout << "Error: Out of Memory" << endl;

		for(int i = 0; i < dimensions; i++)
			ArrPtr[i] = 0;	

		numOfDim = dimensions;
	}	

	// Int and Array Constructor
	MathVector(int dimensions, double *_array)
	{
		numOfDim = dimensions;
		ArrPtr = new double [numOfDim];

		if(ArrPtr == NULL)
			cout << "Error: Out of Memory" << endl;

		for(int i = 0; i < numOfDim; i++)
			ArrPtr[i] = _array[i];
	}

	// Set coordinates
	void set()
	{
		double value;
		for(int i = 0; i < numOfDim; i++)
		{
			cout << "Enter a value for index " << i << ": ";
			cin >> value;
			ArrPtr[i] = value;
		}

		cout << "Done" << endl;
	}

	void printArray()
	{
		for(int i = 0; i < numOfDim; i++)
			cout << "Index " << i << " = " << ArrPtr[i] << endl;
	}

	MathVector& operator=(const MathVector& rhs)
	{
		if(rhs.ArrPtr)
		{
			if(numOfDim = rhs.numOfDim)
				for(int i = 0; i < rhs.numOfDim; i++)
					ArrPtr[i] = rhs.ArrPtr[i];
		}
		else
			ArrPtr = NULL;
	}
	
private: 
	double *ArrPtr;
	int numOfDim;
};


#endif
