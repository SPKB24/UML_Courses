//**                                 **//
//                                     //
// PROGRAM NAME: Invoice.h             //
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

#include <string>

using namespace std;

#ifndef INVOICE_H
#define INVOICE_H

class Invoice
{
public:
	//CONSTRUCTORS
	Invoice() = default;
	Invoice(string number, string description, int quantity, double price);
	
	//SETTERS & GETTERS
	void setNumber(string number);
	void setDescription(string description);
	void setQuantity(int quantity);
	void setPrice(double price);

	string getNumber(void);
	string getDescription(void);
	int getQuantity(void);
	double getPrice(void);

	//INTERFACE
	double getInvoiceAmount(void);
	void getPartInfo();
private:
	string part_number;	 //holds part number
	string part_description; //holds part description
	   int part_quantity;	 //holds part quantity
	double part_price;	 //holds part price


};

#endif
