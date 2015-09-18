//**                                 **//
//                                     //
// PROGRAM NAME: Polynomial.cc         //
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
#include "Polynomial.h"
using namespace std;

/********************* HELPER FUNCTIONS BELOW *********************/

// Initialize Array
Term* initArray(int newSize)
{
	Term* newArray = new Term[newSize];

	if (!newArray)
	{
		cout << "Error: OUT OF MEMORY" << endl;
		return NULL;
	}

	return newArray;
}

// Resize Array 
Term* resizeArray(Term* &src, int oldSize, int newSize)
{
	Term* newArray = new Term[newSize];

	if (!newArray)
	{
		cout << "Error: OUT OF MEMORY" << endl;
		return NULL;
	}

	for (int i = 0; i < oldSize; i++)
		newArray[i] = src[i];

	return newArray;
}


/********************* CLASS FUNCTIONS BELOW *********************/

// Constructor
Polynomial::Polynomial() : numTerms(1)
{
	ArrayPtr = initArray(numTerms);
}

// Add term to Polynomial
void Polynomial::addTerm(int coeff, int exp)
{
	if (hasExponent(exp))
		return;

	Term temp(coeff, exp);

	if (ArrayPtr[numTerms - 1].getExponent() != NULL)
	{
		ArrayPtr = resizeArray(ArrayPtr, numTerms, numTerms + 1);
		numTerms++;
	}
	
	ArrayPtr[numTerms - 1] = temp;

	sortTerms();
}

// Add term to Polynomial - allow duplicate exponents
void Polynomial::addTermCopy(int coeff, int exp)
{
	Term temp(coeff, exp);

	if (ArrayPtr[numTerms - 1].getExponent() != NULL)
	{
		ArrayPtr = resizeArray(ArrayPtr, numTerms, numTerms + 1);
		numTerms++;
	}

	ArrayPtr[numTerms - 1] = temp;

	sortTerms();
}

// Return Array Size
int Polynomial::getSize() const
{
	return numTerms;
}

// OPERATORS
Polynomial& Polynomial::operator=(const Polynomial& arg)
{
	/* Arrays are the same, nothing needs to be done */
	if (this == &arg)
		return *this;

	/* make sure array is empty before copying */
	if (ArrayPtr)
		delete[] this->ArrayPtr;

	if (arg.ArrayPtr)
	{
		numTerms = arg.getSize();
		ArrayPtr = new Term[numTerms];
		for (int i = 0; i <numTerms; i++)
			ArrayPtr[i] = arg.ArrayPtr[i];
	}
	else
		ArrayPtr = NULL;

	return *this;
}

Polynomial Polynomial::operator+(const Polynomial &arg) 
{
	Polynomial* temp = new Polynomial; // Hold added values
	int exp;           // Common Exponents - temp
	int combinedCoeff; // Combined Coefficients - temp
 	int arg1 = indexLargestExp();     // Largest Exp in ArrayPtr, should be 0
	int arg2 = arg.indexLargestExp(); // Largest Exp in arg.ArrayPtr, should be 0
	int topValueArr1 = ArrayPtr[arg1].getExponent();     // Value of largest
	int topValueArr2 = arg.ArrayPtr[arg2].getExponent(); // Value of Largest

	/*cout << "OPERATOR+" << endl
		<< "Index of largest 1: " << arg1 << endl
		<< "Index of largest 2: " << arg2 << endl
		<< "Value of largest 1: " << topValueArr1 << endl
		<< "Value of largest 2: " << topValueArr2 << endl;*/

	if (topValueArr1 >= topValueArr2)
	{
		for (int i = topValueArr1; i > 1; i--)
		{
			if (ArrayPtr[arg1].getExponent() != NULL)
			{
				if (arg.ArrayPtr[arg1].getExponent() == ArrayPtr[arg1].getExponent())
				{
					combinedCoeff = ArrayPtr[arg1].getCoefficient()
						+ arg.ArrayPtr[arg1].getCoefficient();
					exp = ArrayPtr[arg1].getExponent();
					temp->addTerm(combinedCoeff, exp);
				}
				else
				{
					temp->addTerm(
						ArrayPtr[arg1].getCoefficient(),
						ArrayPtr[arg1].getExponent()
						);
					int j = 1;
					while (arg.ArrayPtr[arg1 + j].getExponent() > ArrayPtr[arg1+j+1].getExponent())
					{
						temp->addTerm(
							arg.ArrayPtr[arg1].getCoefficient(),
							arg.ArrayPtr[arg1].getExponent()
							);
						j++;
					}
				}
			}
			else if (arg.ArrayPtr[arg1].getExponent() != NULL)
			{
				temp->addTerm(
					arg.ArrayPtr[arg1].getCoefficient(),
					arg.ArrayPtr[arg1].getExponent()
					);
			}
			
			arg1++;
		}
	}
	else
	{
		for (int i = topValueArr2; i > 1; i--)
		{
			if (arg.ArrayPtr[arg1].getExponent() != NULL)
			{
				if (ArrayPtr[arg1].getExponent() == arg.ArrayPtr[arg1].getExponent())
				{
					combinedCoeff = arg.ArrayPtr[arg1].getCoefficient()
						+ ArrayPtr[arg1].getCoefficient();
					exp = arg.ArrayPtr[arg1].getExponent();
					temp->addTerm(combinedCoeff, exp);
				}
				else
				{
					temp->addTerm(
						arg.ArrayPtr[arg1].getCoefficient(),
						arg.ArrayPtr[arg1].getExponent()
						);
					int j = 1;
					while (ArrayPtr[arg1 + j].getExponent() > arg.ArrayPtr[arg1 + j + 1].getExponent())
					{
						temp->addTerm(
							ArrayPtr[arg1].getCoefficient(),
							ArrayPtr[arg1].getExponent()
							);
						j++;
					}
				}
			}
			else if (ArrayPtr[arg1].getExponent() != NULL)
			{
				temp->addTerm(
					ArrayPtr[arg1].getCoefficient(),
					ArrayPtr[arg1].getExponent()
					);
			}

			arg1++;
		}
	}

	return *temp;
}

Polynomial Polynomial::operator-(const Polynomial &arg)
{
	Polynomial* temp = new Polynomial; // Hold added values
	int exp;           // Common Exponents - temp
	int combinedCoeff; // Combined Coefficients - temp
	int arg1 = indexLargestExp();     // Largest Exp in ArrayPtr, should be 0
	int arg2 = arg.indexLargestExp(); // Largest Exp in arg.ArrayPtr, should be 0
	int topValueArr1 = ArrayPtr[arg1].getExponent();     // Value of largest
	int topValueArr2 = arg.ArrayPtr[arg2].getExponent(); // Value of Largest

	if (topValueArr1 >= topValueArr2)
	{
		for (int i = topValueArr1; i > 1; i--)
		{
			if (ArrayPtr[arg1].getExponent() != NULL)
			{
				if (arg.ArrayPtr[arg1].getExponent() == ArrayPtr[arg1].getExponent())
				{
					combinedCoeff = ArrayPtr[arg1].getCoefficient()
						- arg.ArrayPtr[arg1].getCoefficient();
					exp = ArrayPtr[arg1].getExponent();
					temp->addTerm(combinedCoeff, exp);
				}
				else
				{
					temp->addTerm(
						ArrayPtr[arg1].getCoefficient(),
						ArrayPtr[arg1].getExponent()
						);
					int j = 1;
					while (arg.ArrayPtr[arg1 + j].getExponent() > ArrayPtr[arg1 + j + 1].getExponent())
					{
						temp->addTerm(
							-arg.ArrayPtr[arg1].getCoefficient(),
							arg.ArrayPtr[arg1].getExponent()
							);
						j++;
					}
				}
			}
			else if (arg.ArrayPtr[arg1].getExponent() != NULL)
			{
				temp->addTerm(
					-arg.ArrayPtr[arg1].getCoefficient(),
					arg.ArrayPtr[arg1].getExponent()
					);
			}

			arg1++;
		}
	}
	else
	{
		for (int i = topValueArr2; i > 1; i--)
		{
			if (arg.ArrayPtr[arg1].getExponent() != NULL)
			{
				if (ArrayPtr[arg1].getExponent() == arg.ArrayPtr[arg1].getExponent())
				{
					combinedCoeff = arg.ArrayPtr[arg1].getCoefficient()
						- ArrayPtr[arg1].getCoefficient();
					exp = arg.ArrayPtr[arg1].getExponent();
					temp->addTerm(combinedCoeff, exp);
				}
				else
				{
					temp->addTerm(
						arg.ArrayPtr[arg1].getCoefficient(),
						arg.ArrayPtr[arg1].getExponent()
						);
					int j = 1;
					while (ArrayPtr[arg1 + j].getExponent() > arg.ArrayPtr[arg1 + j + 1].getExponent())
					{
						temp->addTerm(
							-ArrayPtr[arg1].getCoefficient(),
							ArrayPtr[arg1].getExponent()
							);
						j++;
					}
				}
			}
			else if (ArrayPtr[arg1].getExponent() != NULL)
			{
				temp->addTerm(
					-ArrayPtr[arg1].getCoefficient(),
					ArrayPtr[arg1].getExponent()
					);
			}

			arg1++;
		}
	}

	return *temp;
}

Polynomial Polynomial::operator*(const Polynomial &arg)
{
	Polynomial* temp = new Polynomial; // Hold added values
	Polynomial* temp2 = new Polynomial;// Hold added values
	int exp;           // Common Exponents - temp
	int combinedCoeff; // Combined Coefficients - temp
	int arg1 = indexLargestExp();     // Largest Exp in ArrayPtr, should be 0
	int arg2 = arg.indexLargestExp(); // Largest Exp in arg.ArrayPtr, should be 0
	int topValueArr1 = ArrayPtr[arg1].getExponent();     // Value of largest
	int topValueArr2 = arg.ArrayPtr[arg2].getExponent(); // Value of Largest

	for (int i = 0; i < numTerms; i++)
	{
		for (int k = 0; i < numTerms; k++)
		{
			temp->addTermCopy(
				ArrayPtr[i].getCoefficient()*arg.ArrayPtr[k].getCoefficient(),
				ArrayPtr[i].getExponent() + arg.ArrayPtr[k].getExponent()
				);
		}
	}
	int i = 0;
	while (i < 100)
	{
		int j = 1;
		while (temp->ArrayPtr[i].getExponent() == temp->ArrayPtr[i + j].getExponent())
		{
			temp2->addTerm(
				temp->ArrayPtr[i].getCoefficient() + temp->ArrayPtr[i + j].getCoefficient(),
				temp->ArrayPtr[i].getExponent()
				);
			j++;
		}
	}

	return *temp2;
}

Polynomial &Polynomial::operator+=(const Polynomial &arg)
{
	Polynomial* temp = new Polynomial; // Hold added values
	int exp;           // Common Exponents - temp
	int combinedCoeff; // Combined Coefficients - temp
	int arg1 = indexLargestExp();     // Largest Exp in ArrayPtr, should be 0
	int arg2 = arg.indexLargestExp(); // Largest Exp in arg.ArrayPtr, should be 0
	int topValueArr1 = ArrayPtr[arg1].getExponent();     // Value of largest
	int topValueArr2 = arg.ArrayPtr[arg2].getExponent(); // Value of Largest
	
	if (topValueArr1 >= topValueArr2)
	{
		for (int i = topValueArr1; i > 1; i--)
		{
			if (ArrayPtr[arg1].getExponent() != NULL)
			{
				if (arg.ArrayPtr[arg1].getExponent() == ArrayPtr[arg1].getExponent())
				{
					combinedCoeff = ArrayPtr[arg1].getCoefficient()
						+ arg.ArrayPtr[arg1].getCoefficient();
					exp = ArrayPtr[arg1].getExponent();
					temp->addTerm(combinedCoeff, exp);
				}
				else
				{
					temp->addTerm(
						ArrayPtr[arg1].getCoefficient(),
						ArrayPtr[arg1].getExponent()
						);
					int j = 1;
					while (arg.ArrayPtr[arg1 + j].getExponent() > ArrayPtr[arg1 + j + 1].getExponent())
					{
						temp->addTerm(
							arg.ArrayPtr[arg1].getCoefficient(),
							arg.ArrayPtr[arg1].getExponent()
							);
						j++;
					}
				}
			}
			else if (arg.ArrayPtr[arg1].getExponent() != NULL)
			{
				temp->addTerm(
					arg.ArrayPtr[arg1].getCoefficient(),
					arg.ArrayPtr[arg1].getExponent()
					);
			}

			arg1++;
		}
	}
	else
	{
		for (int i = topValueArr2; i > 1; i--)
		{
			if (arg.ArrayPtr[arg1].getExponent() != NULL)
			{
				if (ArrayPtr[arg1].getExponent() == arg.ArrayPtr[arg1].getExponent())
				{
					combinedCoeff = arg.ArrayPtr[arg1].getCoefficient()
						+ ArrayPtr[arg1].getCoefficient();
					exp = arg.ArrayPtr[arg1].getExponent();
					temp->addTerm(combinedCoeff, exp);
				}
				else
				{
					temp->addTerm(
						arg.ArrayPtr[arg1].getCoefficient(),
						arg.ArrayPtr[arg1].getExponent()
						);
					int j = 1;
					while (ArrayPtr[arg1 + j].getExponent() > arg.ArrayPtr[arg1 + j + 1].getExponent())
					{
						temp->addTerm(
							ArrayPtr[arg1].getCoefficient(),
							ArrayPtr[arg1].getExponent()
							);
						j++;
					}
				}
			}
			else if (ArrayPtr[arg1].getExponent() != NULL)
			{
				temp->addTerm(
					ArrayPtr[arg1].getCoefficient(),
					ArrayPtr[arg1].getExponent()
					);
			}

			arg1++;
		}
	}

	*this = *temp;

	return *this;
}

// Print out all Terms
void Polynomial::printAll()
{
	for (int i = 0; i < numTerms; i++)
	{
		ArrayPtr[i].printTerm();
	}
}

// Sort Terms
void Polynomial::sortTerms()
{
	for (int k = 0; k < numTerms; k++)
		for (int i = 0; i < numTerms - 1 - k; i++)
			if (ArrayPtr[i].getExponent() < ArrayPtr[i + 1].getExponent())
				swapTerms(i, i + 1);
}

// Swap two terms in array
void Polynomial::swapTerms(int index1, int index2)
{
	Term temp;

	temp = ArrayPtr[index1];
	ArrayPtr[index1] = ArrayPtr[index2];
	ArrayPtr[index2] = temp;
}

// Does the array have this exponent?
bool Polynomial::hasExponent(int findExp) const
{
	for (int i = 0; i < numTerms; i++)
	{
		if (ArrayPtr[i].getExponent() == findExp)
			return true;
	}

	return false;
}

// find index of largest exponent
int Polynomial::indexLargestExp() const
{
	int largestIndex = 0;

	//cout << "NUMBER OF TERMS: " << numTerms << endl;

	for (int i = 0; i < numTerms; i++)
	{
		if (ArrayPtr[i].getExponent() < ArrayPtr[i + 1].getExponent())
			largestIndex = i + 1;
	}

	return largestIndex;
}

// Destructor
Polynomial::~Polynomial()
{
	delete[] ArrayPtr;
	ArrayPtr = NULL;
 }
