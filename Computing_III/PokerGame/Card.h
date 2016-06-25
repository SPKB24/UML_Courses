//**                                 **//
//                                     //
// PROGRAM NAME: Card.h                //
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

#ifndef CARD_H
#define CARD_H

#include <iostream>
#include <string>
using namespace std;

enum SUIT
{
    SPADES,
    HEARTS, 
    DIAMONDS, 
    CLUBS
};
static const string suitToString[] = { "SPADES", "HEARTS", "DIAMONDS", "CLUBS" };

//static const string SUITS[] = { ".", "SPADES", "HEARTS", "DIAMONDS", "CLUBS" };
static const string FACES[] = { ".", "A", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K" };

class Card
{
public:
	// Constructor
	Card(int _face = 1, SUIT _suit = SPADES);

	// Member Functions
	string toString() const;
	void changeCard(int _face, SUIT _suit);

	// Getter
	int getFace();
	SUIT getSuit();

	// Operator Overloading
	bool operator==(const Card& rhs); // Compare Operato
	

	friend ostream & operator<<(ostream &output, const Card &arg) 
	{
		cout << arg.toString() << endl;
		return output;
	}

private:
	int face; // 1 - 13
	SUIT suit; // 1 - 4
};

// Init Card, default to Ace of Spades
Card::Card(int _face, SUIT _suit) : face(_face), suit(_suit)
{
	if (_face < 1 || _face > 13) // Out of Bounds
		face = 1;

	if (_suit < 1 || _suit > 4)  // Out of Bounds
		suit = SPADES;
}

// return Card as String
string Card::toString() const
{
	return (FACES[face] + " of " + suitToString[suit]);
}

// Change card face and suit
void Card::changeCard(int _face, SUIT _suit)
{
	if (_face < 1 || _face > 13) // Out of Bounds
		return;

	if (_suit < 1 || _suit > 4)  // Out of Bounds
		return;

	face = _face;
	suit = _suit;
}

// Return face of a card
int Card::getFace()
{
	return face;
}

// Return suit of a card
SUIT Card::getSuit()
{
	return suit;
}

// Compare two Cards
bool Card::operator==(const Card& rhs)
{
	if (face == rhs.face && suit == rhs.suit)
		return true;

	return false;
}

#endif
