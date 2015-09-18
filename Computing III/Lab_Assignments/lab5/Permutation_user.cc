#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "Permutation.h"
using namespace std;

int main(int argc, char * argv[])
{
       /***********************************\
	           READ FROM FILE          
       \***********************************/
	Permutation<string> a;
	string input;
	while (cin >> input)
		a.addToInitial(input);

       /***********************************\
	          BEGIN PERMUTING           
       \***********************************/

	// Print permutated values
	// Should not contain duplicates
	a.permute();

	// Print to all permutations to file
	cout << a.printPermAsString();
	
	return 0;
}
