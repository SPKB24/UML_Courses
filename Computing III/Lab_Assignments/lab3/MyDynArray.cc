//**                                 **//
//                                     //
// PROGRAM NAME: MyDynArray.cc         //
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
#include "MyDynArray.h"

using namespace std;

// will return an initialized array of size size_
T* initArray(size_t size_)
{
	T* temp = new T[size_];

	if (!temp)
	{
		cout << "Error: OUT OF MEMORY" << endl;
		return NULL;
	}

	for (size_t i = 0; i < size_; i++)
		temp[i] = 0;

	return temp;
}

/* default constructor; default size is 100 items */
MyDynArray::MyDynArray(size_t size_)
{
	cout << "** DEFAULT CONSTRUCTOR CALLED" << endl;

	if (size_ > 0)
		size = (size_t) size_;
	else
		size = 100;

	array_ptr = initArray(size);
}

/* get the current array size */
size_t MyDynArray::getSize() const
{	
	return size;
}

// put the element at the position specified by index
// if the position is out of range, increase the size of array accordingly
bool MyDynArray::set(T element, size_t index)
{
	cout << "** SET(): " << "try set Index: " << index << " = " << element << endl;

	while (index >= size) // Keep looping until index < size
	{
		T* temp;
		int multiple = 2;
		size_t newSize = size * multiple;

		/* Initialize array and confirm that it worked */
		if ((temp = initArray(newSize)) == NULL)
			return false;

		/* Copy Array_Ptr values into Temp */
		copy(array_ptr, array_ptr + (size), temp);
			
		delete[] array_ptr; // Deallocate Memory
		array_ptr = NULL;	// Ready to be initialized with larger size

		/* Initialize array and confirm that it worked */
		if ((array_ptr = initArray(newSize)) == NULL)
			return false;

		/* Copy Temp values back into Array_Ptr */
		copy(temp, temp + (newSize), array_ptr);

		size = newSize; // Change Size to new size

		delete[] temp; // Deallocate Memory
		temp = NULL;
	}

	/* At this point, index will be smaller than size */

	array_ptr[index] = element; // Set element to index
	
	return true;
}

// get the value at the position specified by index
T MyDynArray::get(size_t index) const
{
	if (index < size)
		return array_ptr[index];
	else
		cout << "The array does not have index " << index << endl;

	return (int) NULL;
}

// copy constructor: should do a deep copy
MyDynArray::MyDynArray(const MyDynArray& arg)
{
	cout << "** COPY CONSTRUCTOR CALLED" << endl;
	
	size = arg.size;

	if (arg.array_ptr)
	{
		array_ptr = new T[size];
		copy(arg.array_ptr + 0, arg.array_ptr + (size), array_ptr);
	}
	else
		array_ptr = NULL;
}

// assignment operator: should do a deep copy
MyDynArray& MyDynArray::operator=(const MyDynArray& rhs)
{
	cout << "** ASSIGNMENT OPERATOR CALLED" << endl;
	
	/* Arrays are the same, nothing needs to be done */
	if (this == &rhs)
		return *this;

	/* make sure array is empty before copying */
	if (array_ptr)
		delete[] this->array_ptr;

	if (rhs.array_ptr)
	{
		array_ptr = new T[rhs.size];
		copy(rhs.array_ptr + 0, rhs.array_ptr + (rhs.size), array_ptr);
	}
	else
		array_ptr = NULL;

	size = rhs.size;

	return *this;
}

// destructor
MyDynArray::~MyDynArray()
{
	cout << "** DESTRUCTOR CALLED" << endl;
	delete[] array_ptr;
	array_ptr = NULL;
}

