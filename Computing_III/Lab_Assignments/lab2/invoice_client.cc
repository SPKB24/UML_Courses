//**                                 **//
//                                     //
// PROGRAM NAME: invoice_client.cc     //
//                                     //
// AUTHOR: Sohit Pal                   //
//                                     //
//  ##  #  # # ### ###     ##   #  #   //
// #   # # # #  #   #      # # # # #   //
//  #  # # ###  #   #      ##  ### #   //
//   # # # # #  #   #      #   # # #   //
// ##   #  # # ###  #      #   # # ### //
//                                     //
// DATE: March 2, 2014                 //
//                                     //
//**                                 **//

#include <iostream>
#include <string>
#include "Invoice.h"

using namespace std;

int main(int argc, char * argv[])
{
	//Custom Constructor
	Invoice a("5223442", "Hammer", 50, 99.99);
	
	//Default Constructor
	Invoice b;

	
	//INVOICE a
	cout << "-------- Invoice a --------" << endl;

	a.getPartInfo();

	cout << endl;

	
	//INVOICE b
	cout << "-------- Invoice b --------" << endl;

	b.setNumber("42");
	b.setDescription("Screw Driver");
	b.setPrice(-40);
	b.setQuantity(30);
	b.getPartInfo();

	cout << endl;

	b.setPrice(50);
	b.getPartInfo();

	return 0;
}
