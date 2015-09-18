#ifndef PERMUTATION_H
#define PERMUTATION_H

#include <iostream>
#include <vector>
#include <set>
#include <string>
using namespace std;

template <typename T>
class Permutation
{
public:
	// Initialize initialCount to 0
	Permutation() : initialCount(0) {}

	// Add value to initial vector
	void addToInitial(T value)
	{
		initialArray.push_back(value);
		initialCount++;
	}

	// print initial values
	void printInitial()
	{
		for (typename vector<T>::iterator it = initialArray.begin(); 
		                         it != initialArray.end(); it++)
			cout << *it << " ";

		cout << endl;
	}

	// permute initial values and add to Set
	void permute(int i = 0)
	{
		if (i == initialCount)
			addToSet();
		else
		{
			for (int j = i; j < initialCount; j++)
			{
				swapItems(i, j);
				permute(i + 1);
				swapItems(i, j);
			}
		}
	}

	// Return Permutations as 1 long string (with new lines chars)
	string printPermAsString()
	{
		int counter = 0;

		for (typename set<T>::iterator it = permList.begin(); it != permList.end(); it++)
			cout << ++counter << ".  " << *it << endl;

		return permListString;
	}



private:
	vector<T> initialArray; // Hold initial input from file
	set<T> permList;        // Hold permutations | will remove duplicates automatically
	int initialCount;       // Hold count of initial values
	string permListString;

	// Add Permutations to set
	// Will not insert duplicates
	void addToSet()
	{
		T temp;

		for (int i = 0; i < initialCount; i++)
			temp += initialArray[i] + " ";

		permList.insert(temp);
	}

	// Swap terms in initialArray in indx1 and indx2
	void swapItems(int indx1, int indx2)
	{
		// If equal, don't swap
		if (indx1 == indx2)
			return;

		// Else, swap
		T temp;
		temp = initialArray[indx1];
		initialArray[indx1] = initialArray[indx2];
		initialArray[indx2] = temp;
	}
};

#endif
