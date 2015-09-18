//**                                 **//
//                                     //
// PROGRAM NAME: Invoice.cc            //
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

//CONSTRUCTOR
Invoice::Invoice(string number, string description, int quantity, double price)
{
	setNumber(number);
	setDescription(description);
	setQuantity(quantity);
	setPrice(price);
}

//SETTERS & GETTERS
void Invoice::setNumber(string number)
{
	part_number = number;
}

void Invoice::setDescription(string description)
{
	part_description = description;
}

void Invoice::setQuantity(int quantity)
{
	if (quantity >= 0)
		part_quantity = quantity;
	else
	{
		part_quantity = 0;
		cout << "Quantity cannot be negative. Part Quantity has been set to 0" << endl;
	}
}

void Invoice::setPrice(double price)
{
	if (price >= 0)
		part_price = price;
	else
	{
		part_price = 0;
		cout << "Price cannot be negative. Part Price has been set to $0.00" << endl;
	}
}

string Invoice::getNumber()
{
	return part_number;
}

string Invoice::getDescription()
{
	return part_description;
}

int Invoice::getQuantity()
{
	return part_quantity;
}

double Invoice::getPrice()
{
	return part_price;
}

//INTERFACE
double Invoice::getInvoiceAmount()
{
	return (double)(part_quantity * part_price);
}

void Invoice::getPartInfo()
{
	cout << "Part Number: " << getNumber() << endl;
	cout << "Part Description: " << getDescription() << endl;
	cout << "Part Quantity: " << getQuantity() << endl;
	cout << "Part Price: $" << getPrice() << endl;
	cout << "Part Invoice: " << getInvoiceAmount() << endl;
}
