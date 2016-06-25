//**                                 **//
//                                     //
// PROGRAM NAME: DeckOfCards.h         //
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

#ifndef DECKOFCARDS_H
#define DECKOFCARDS_H

#include <iostream>
#include <ctime>
#include <vector>
#include "Card.h"
using namespace std;

#define DECK_SIZE 52 // 52 Cards in a Deck
#define SUIT_SIZE 4  // 4 Possible suit options
#define FACE_SIZE 13 // 13 Possible card options

class DeckOfCards
{
public:
	// Constructor
	DeckOfCards();

	// Member Function
	void shuffle();
	Card dealCard();
	bool moreCards() const;

	friend ostream & operator<<(ostream &output, const DeckOfCards &arg)
	{
		for (int i = 0; i < DECK_SIZE; i++) {
			cout << arg.deck[i];
		}

		return output;
	}

private:
	vector<Card> deck; // All Cards stored here
	int currentCard;   // Representing the next card to deal
};

// Init Deck, add 52 cards to deck
DeckOfCards::DeckOfCards()
{
	currentCard = 1;

	// ADD ALL CARDS TO THE DECK IN ORDER
	int cardsCount = 0;
	Card addToDeck;

	for (int _suit = 1; _suit <= SUIT_SIZE; _suit++)
	{
		for (int _face = 1; _face <= FACE_SIZE; _face++)
		{
			addToDeck.changeCard(_face, _suit);
			deck.push_back(addToDeck);
		}
	}
}

// Shuffle all cards
void DeckOfCards::shuffle()
{
	for (int k = 1; k < DECK_SIZE; k++)
	{
		srand(time(NULL));
		int r = k + rand() % (DECK_SIZE - k);
		swap(deck[k], deck[r]);
	}
}

// Deal one card at a time
Card DeckOfCards::dealCard()
{
	if (moreCards())
		return deck[currentCard++];

	return NULL;
}

// Check to see deck status
bool DeckOfCards::moreCards() const
{
	if (currentCard == DECK_SIZE)
		return false;

	return true;
}

#endif
