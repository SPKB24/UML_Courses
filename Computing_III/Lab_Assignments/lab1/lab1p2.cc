//**                                 **//
//                                     //
// PROGRAM NAME: lab1p2.cc             //
//                                     //
// AUTHOR: Sohit Pal                   //
//                                     //
//  ##  #  # # ### ###     ##   #  #   //
// #   # # # #  #   #      # # # # #   //
//  #  # # ###  #   #      ##  ### #   //
//   # # # # #  #   #      #   # # #   //
// ##   #  # # ###  #      #   # # ### //
//                                     //
// DATE: February 5, 2014              //
//                                     //
//**                                 **//


#include <iostream>
/* This is used to input/output to/from the console */

using namespace std;

int main(int argc, char * argv[])
{

        cout << "------------------------------" << endl;
        cout << "lab1p2.cc | COMMAND LINE PRINT" << endl;
        cout << "------------------------------" << endl;	

	for(int i = 1; i < argc; i++)
		cout << argv[i] << endl;
	
	cout << "------------------------------" << endl;

	return 0;
}
