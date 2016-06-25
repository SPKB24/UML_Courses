//**                                 **//
//                                     //
// PROGRAM NAME: Hand.h                //
//                                     //
// AUTHOR: Sohit Pal                   //
//                                     //
// ### ### # # ### ###     ###  #  #   //
// #   # # # #  #   #      # # # # #   //
// ### # # ###  #   #      ### ### #   //
//   # # # # #  #   #      #   # # #   //
// ### ### # # ###  #      #   # # ### //
//                                     //
// DATE: May 8, 2015                   //
//                                     //
//**                                 **//

#ifndef HAND_H
#define HAND_H

#include <vector>
#include <set>
#include "Card.h"
using namespace std;

#define HAND_SIZE 5

class Hand
{
public:
	// Constructor
	Hand();

	// Member Functions
	bool addToHand(Card add);
	int handStatus();		         // Return int | high = good hand, low = bad hand
	void clearHand(int index = 500); // Clear hand completely, 500 defaults to clearing all of hand
	int  handCount();                // return number of cards in hand
	void printHand(string type = "default"); // Most likely just temporary...

	// Status Finders
	bool isStraight();
	bool isFlush();
	bool isFourOfAKind();
	bool isThreeOfAKind();
	bool isTwoPair();
	bool isPair();

	// Operators
	int operator()(int index)
	{
		return mCards[index].getFace();
	}

private:
	vector<Card> mCards;

	void putInOrder(string type = "suit");
};

// init Hand, does nothing
Hand::Hand()
{}

// Insert Card into hand
bool Hand::addToHand(Card add)
{
	if (add == NULL)
		return false;

	if (mCards.size() == 5)
		return false;

	mCards.push_back(add);

	if (mCards.size() == 5)
		putInOrder(); // Order by Suit

	return true;
}

// check Hand Score (straight, flush, etc...)
int Hand::handStatus()
{
	putInOrder("face"); // Order by Face value

	if (isStraight())
		return 6;

	if (isFlush())
		return 5;

	if (isFourOfAKind())
		return 4;

	if (isThreeOfAKind())
		return 3;

	if (isTwoPair())
		return 2;

	if (isPair())
		return 1;

	return 0;
}

// Clear Hand contents
void Hand::clearHand(int index)
{
	if (index == 500)
	{
		if (mCards.size())
			mCards.clear();
	}
	else
	{
		if (index >= 0 && index < HAND_SIZE)
			mCards.erase(mCards.begin() + index);
	}
}

// Make sure hand has 5 cards
int Hand::handCount()
{
	return mCards.size();
}

// Re-order cards to put in order
// type "face" or "suit"
void Hand::putInOrder(string type)
{
	if (type != "suit" && type != "face") {
		cout << "Invalid parameter passed to putInOrder()" << endl;
		return;
	}


	vector< vector<Card> > suitVector;
	vector<Card> faceVector;

	if (type == "suit")
	{
		// Order each suit
		for (int _suit = 1; _suit < 5; _suit++)
		{
			for (int i = 0; i < HAND_SIZE; i++)
				if (_suit == mCards[i].getSuit())
					faceVector.push_back(mCards[i]);
			
			if (faceVector.size())
			{
				suitVector.push_back(faceVector);
				faceVector.clear();
			}
		}

		// Order faces in each suit
		for (int i = 0; i < suitVector.size(); i++)
			for (int j = 0; j < suitVector[i].size(); j++)
				for (int k = 0; k < suitVector[i].size()-1-j; k++)
					if (suitVector[i][k].getFace() > suitVector[i][k + 1].getFace())
						swap(suitVector[i][k], suitVector[i][k + 1]);

		mCards.clear();

		// Add all cards back to main vector
		for (int i = 0; i < suitVector.size(); i++)
			for (int j = 0; j < suitVector[i].size(); j++)
				mCards.push_back(suitVector[i][j]);
	}
	else if (type == "face")
	{
		for (int j = 0; j < mCards.size(); j++)
			for (int k = 0; k < mCards.size() - 1 - j; k++)
				if (mCards[k].getFace() > cards[k+1].getFace())
					swap(mCards[k], cards[k + 1]);
	}
	else
		cout << "You have entered an invalid type" << endl;
}

void Hand::printHand(string type)
{
	if (type == "face" || type == "suit")
		putInOrder(type);

	for (int i = 0; i < HAND_SIZE; i++)
		cout << mCards[i];

	cout << endl;
}

bool Hand::isStraight() // WORKING!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
{
	int currentFace = mCards[0].getFace();

	if (currentFace > 9) // Will be out of bounds
		return false;

	for (int i = 0; i < HAND_SIZE; i++)
	{
		if (currentFace != mCards[i].getFace())
			return false;

		currentFace++;
	}

	return true;
}

bool Hand::isFlush() // WORKING!!!!!!!!!!!!!!!!!!!!!!
{
	int majorSuit = mCards[0].getSuit();
	
	for (int i = 0; i < HAND_SIZE; i++)
		if (majorSuit != mCards[i].getSuit())
			return false;

	return true;
}

bool Hand::isFourOfAKind()
{
	int magicNumber = 4;

	vector< vector<int> > faceVector;
	        vector<int>   faceCount;

	for (int i = 0; i < HAND_SIZE - magicNumber + 1; i++)
	{
		for (int k = i; k < HAND_SIZE - 1; k++)
			if (mCards[i].getFace() == cards[k + 1].getFace())
				faceCount.push_back(mCards[i].getFace());

		if (faceCount.size())
		{
			faceVector.push_back(faceCount);
			faceCount.clear();

			if (faceVector[faceVector.size()-1].size() + 1 >= magicNumber)
				return true;
		}
	}

	return false;
}

bool Hand::isThreeOfAKind()
{
	int magicNumber = 3;

	vector< vector<int> > faceVector;
	        vector<int>   faceCount;

	for (int i = 0; i < HAND_SIZE - magicNumber + 1; i++)
	{
		for (int k = i; k < HAND_SIZE - 1; k++)
			if (mCards[i].getFace() == cards[k + 1].getFace())
				faceCount.push_back(mCards[i].getFace());

		if (faceCount.size())
		{
			faceVector.push_back(faceCount);
			faceCount.clear();

			if (faceVector[faceVector.size() - 1].size() +1 >= magicNumber)
				return true;
		}
	}

	return false;
}

bool Hand::isTwoPair()
{
	int magicNumber = 2;

	vector< vector<int> > faceVector;
	        vector<int>   faceCount;

	for (int i = 0; i < HAND_SIZE-1; i++) // Put all pairs into Vector of Vectors of Ints
	{
		for (int k = i; k < HAND_SIZE - 1; k++)
			if (mCards[i].getFace() == cards[k + 1].getFace())
				faceCount.push_back(mCards[i].getFace());

		if (faceCount.size())
		{
			if (faceVector.size())
				if (faceCount[0] != faceVector[faceVector.size() - 1][0])
					faceVector.push_back(faceCount);
			else
				faceVector.push_back(faceCount);

			faceCount.clear();
		}
	}

	if (faceVector.size())
		for (int i = 0; i < faceVector.size(); i++) // 0 1 2 <== INDEX
		{											// 2 1 2 <== NUMBER OF PAIRS
			if (faceVector[i].size() + 1 >= 2) // Found First Pair
			{
				for (int j = i+1; j < faceVector.size(); j++)
				{
					if (faceVector[j].size() + 1 >= 2) //Found Second Pair
						return true;
				}
				
			}
		}

	return false;
}

bool Hand::isPair()
{
	int magicNumber = 2;

	vector< vector<int> > faceVector;
	vector<int>   faceCount;

	for (int i = 0; i < HAND_SIZE - magicNumber + 1; i++)
	{
		for (int k = i; k < HAND_SIZE - 1; k++)
			if (mCards[i].getFace() == cards[k + 1].getFace())
				faceCount.push_back(mCards[i].getFace());

		if (faceCount.size())
		{
			faceVector.push_back(faceCount);
			faceCount.clear();

			if (faceVector[faceVector.size() - 1].size() + 1 >= magicNumber)
				return true;
		}
	}

	return false;
}

#endif
