//**                                 **//
//                                     //
// PROGRAM NAME: Ex1.cc                //
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
using namespace std;

typedef int (*fPtr)(int);

// Increase value by 1
int increment(int val)
{
	return ++val;
}

// Decrease value by 1
int decrement(int val)
{
	return --val;
}

// Apply function to Arg
// funcPtr will point to a function
int apply(int arg, int(*funcPtr)(int))
{
	return funcPtr(arg);
}

int main(int argc, char * argv[])
{
	fPtr a = &increment; // Set a to point at increment function

	for (int i = 0; i < 2 ; i++)
	{
		if (i == 1)
			a = &decrement; // Set a to point at decrement function

		cout << a(25) << endl;
		cout << apply(5, a) << endl;
	}

	return 0;
}
