//**                                 **//
//                                     //
// PROGRAM NAME: Polynomial.h          //
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

#ifndef POLYNOMIAL_H
#define POLYNOMIAL_H

#include <iostream>
#include "Term.h"
using namespace std;

class Polynomial
{
public:
	// DEFAULT CONSTRUCTOR
	// Allocates space for 1 term
	// Space for other terms allocated automatically in other functions
	Polynomial();

	// SETTER
	// int coeff - Term Coefficient
	// int exp - Term Exponent
	void addTerm(int coeff, int exp);

	void addTermCopy(int coeff, int exp);

	// GETTER
	int getSize() const;

	// ASSIGNMENT OPERATOR
	Polynomial& operator=(const Polynomial& arg); // I think...

	Polynomial operator+(const Polynomial& arg);

	Polynomial operator-(const Polynomial &arg);

	Polynomial operator*(const Polynomial& arg);

	Polynomial& operator+=(const Polynomial& arg);

	// Other Member Functions
	void printAll();
	
	void sortTerms();

	void swapTerms(int index1, int index2);

	bool hasExponent(int findExp) const;

	int indexLargestExp() const;

	// Destructor
	~Polynomial();

private:
	Term *ArrayPtr;
	int numTerms;
};


#endif
