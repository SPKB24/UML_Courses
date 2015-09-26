//**                                 **//
//                                     //
// PROGRAM NAME: Term.h                //
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


#ifndef TERM_H
#define TERM_H

#include <iostream>
using namespace std;

class Term
{
public:
	// Default Constructor
	Term()
	{
		exponent = coefficient = NULL;
	}

	// Custom Constructor
	Term(int _coeff, int _exp) : coefficient(_coeff), exponent(_exp)
	{
		if (_exp <= 0)
		{
			exponent = 0;
			coefficient = 1;
		}
		else
			exponent = _exp;

		coefficient = _coeff;
	}
               
	// COMPARE TWO EXPONENTS
	// Returns:
	//	1 : this > b
	//	0 : this = b
	// -1 : this < b
	int compareExponents(Term &b)
	{
		if (coefficient > b.coefficient)
			return 1;
		if (coefficient == b.coefficient)
			return 0;
		if (coefficient < b.coefficient)
			return -1;

		return NULL;
	}

	// Getters
	int getExponent()
	{
		return exponent;
	}

	int getCoefficient()
	{
		return coefficient;
	}

	// Setters 
	void setExponent(int exp)
	{
		if (exp > 0)
			exponent = exp;
	}

	void setCoefficient(int coeff)
	{
		coefficient = coeff;
	}

	// Other Member Functions
	void printTerm()
	{
		if (coefficient == 0)
			cout << 0;
		else
		{
			if (exponent == 0)
			{
				cout << "+";
				cout << "(" << coefficient << ")";
			}
			else if (coefficient > 0)
			{
				cout << "+";
				cout << "(" << coefficient << "x^" << exponent << ")";
			}
			else if (coefficient < 0)
			{
				int temp = coefficient - (2 * coefficient);
				cout << "-";
				cout << "(" << temp << "x^" << exponent << ")";
			}
		}
	}

private:
	int exponent;
	int coefficient;
};

#endif
