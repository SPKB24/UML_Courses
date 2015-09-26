//**                                 **//
//                                     //
// PROGRAM NAME: MyDynArray.h          //
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

#ifndef MYDYNARRAY_H
#define MYDYNARRAY_H

typedef int T;  // specify the data type to be stored in the array

class MyDynArray 
{

private:

	// number of elements currently in the array
	size_t size;

	// array pointer
	T *array_ptr;

public:

	// constructor; default size is 100 items
	MyDynArray(int size_ = 100);

	// get the current array size
	size_t getSize() const;

	// put the element at the position specified by index
	// if the position is out of range, increase the size of array accordingly
	bool set(T element, size_t index);

	// get the value at the position specified by index
	T get(size_t index) const;

	// copy constructor: should do a deep copy
	MyDynArray(const MyDynArray& arg);

	// assignment operator: should do a deep copy
	MyDynArray& operator=(const MyDynArray& rhs);

	// destructor
	~MyDynArray();
};

#endif

