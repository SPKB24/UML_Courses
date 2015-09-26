//**                                 **//
//                                     //
// PROGRAM NAME: Poker.cc              //
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

#include <iostream>
#include "Hand.h"
#include "DeckOfCards.h"
#include "Card.h"
using namespace std;

// return score as string
string scoreFinder(int score)
{
	switch (score)
	{
	case 6:
		return "Straight";
	case 5:
		return "Flush";
	case 4:
		return "Four of a Kind";
	case 3:
		return "Three of a Kind";
	case 2:
		return "Two Pair";
	case 1:
		return "Pair";
	default:
		return "Nothing";
	}
}

void part3()
{
	cout << endl << "---PART 3---" << endl;

	DeckOfCards deck;
	Hand player1;
	Hand player2;

	int loopCount = 0;
	int p1Wins = 0;
	int p2Wins = 0;
	int ties = 0;

	// Shuffle Deck
	deck.shuffle();

	// while cards in deck
	while (deck.moreCards())
	{
		loopCount++;
		// Deal 5 cards to each hand
		for (int i = 0; i < HAND_SIZE; i++)
		{
			player1.addToHand(deck.dealCard());
			player2.addToHand(deck.dealCard());
		}
		
		if (player1.handCount() != 5 || player2.handCount() != 5) // if not full hand
		{
			loopCount--;
			break;
		}

		int p1Score = player1.handStatus();
		int p2Score = player2.handStatus();
		
		if (p1Score > p2Score)		
			p1Wins++;
		else if (p1Score < p2Score)
			p2Wins++;
		else
			ties++;

		player1.clearHand();
		player2.clearHand();
	}

	// Game Stats
	cout << endl << "***************************" << endl;
	cout << "** GAME STATS | " << loopCount << " Rounds **" << endl << endl;
	cout << "Player 1 Win  : " << p1Wins << endl;
	cout << "Player 2 Win  : " << p2Wins << endl;
	cout << "Tie Game      : " << ties << endl;

	cout << endl;
}

void part4()
{
	cout << "--PART 4--" << endl;

	DeckOfCards deck;
	Hand dealer;
	Hand opponent;

	int loopCount = 0;
	int dealerWins = 0;
	int dealerWinsSwitch = 0;
	int opponentWins = 0;
	int opponentWinsSwitch = 0;
	int ties = 0;
	int tiesSwitch = 0;

	// Shuffle Deck
	deck.shuffle();

	// while cards in deck
	while (deck.moreCards())
	{
		loopCount++;
	
		// Deal 5 cards to each hand
		for (int i = 0; i < HAND_SIZE; i++)
		{
			dealer.addToHand(deck.dealCard());
			opponent.addToHand(deck.dealCard());
		}

		if (dealer.handCount() != 5 || opponent.handCount() != 5) // if not full hand
		{
			loopCount--;
			break;
		}

		int dealerScore = dealer.handStatus();
		int opponentScore = opponent.handStatus();

		// Get stats for score BEFORE SWITCHING CARDS
		if (dealerScore > opponentScore)
			dealerWins++;
		else if (dealerScore < opponentScore)
			opponentWins++;
		else
			ties++;

		// Code for dealer switching cards...
		// 
		//			check score
		//				if 6 (straight)      	leave
		//				if 5 (flush)	        leave
		//				if 4 (four of a kind)	Replace first or last card
		//				if 3 (three of a kind)
		//					Replace first or last two card
		//				if 2 (Two Pair)
		//					Replace the one unpaired card
		//				if 1 (Pair)
		//					Replace first or last three card
		//				if 0 (Nothing)
		//					Check suits, replace as many unpaired suits as possible

		int mainNum = 0;
		int removed = 0;
		bool shouldBreak = false;

		switch (dealerScore)
		{
		case 6: // Straight
			// cannot improve this
			break;
		case 5: // Flush
			// can improve, but more chances of hurting, so leave it
			break;
		case 4: // Four of a Kind
			// cannot improve
			break;
		case 3: // Three of a Kind
			mainNum = 0;
			for (int i = 0; i < HAND_SIZE - 1; i++) // Find three of a kind number
			{
				if (dealer(i) == dealer(i + 1))
				{
					mainNum++;
					if (mainNum == 2)
						mainNum = dealer(i);
				}
				else
					mainNum = 0;
			}

			removed = 0;
			for (int j = 0; j < HAND_SIZE; j++) // Remove wastes
			{
				if (dealer(j) != mainNum)
				{
					removed++;
					dealer.clearHand(j);
					j--;
					if (removed == 2)
						break;
				}
			}

			if (removed == 2)
			{
				for (int k = 0; k < 2; k++)
					dealer.addToHand(deck.dealCard());
			}

			if (dealer.handCount() != 5)
			{
				loopCount--;
				shouldBreak = true;
			}
			break;
		case 2: // Two Pair
			/*if (dealer(0) == dealer(1))
				dealer.clearHand(4);
			else
				dealer.clearHand(0);

			dealer.addToHand(deck.dealCard());
			if (dealer.handCount() != 5)
			{
				cout << "OUT OF CARDS" << endl;
				loopCount--;
				break;
			}*/
			break;
		case 1: // Pair
			mainNum = 0;
			for (int i = 0; i < HAND_SIZE - 1; i++) // Find three of a kind number
			{
				if (dealer(i) == dealer(i + 1))
				{
					mainNum++;
					if (mainNum == 1)
						mainNum = dealer(i);
				}
				else
					mainNum = 0;
			}

			removed = 0;
			for (int j = 0; j < HAND_SIZE; j++) // Remove wastes
			{
				if (dealer(j) != mainNum)
				{
					removed++;
					dealer.clearHand(j);
					j--;
					if (removed == 3)
						break;
				}
			}

			if (removed == 3)
			{
				for (int k = 0; k < 3; k++)
					dealer.addToHand(deck.dealCard());
			}

			if (dealer.handCount() != 5)
			{
				loopCount--;
				shouldBreak = true;
			}

			break;
		default: // Nothing
			for (int i = 0; i < 3; i++)
			{
				dealer.clearHand(i);
				dealer.addToHand(deck.dealCard());
			}

			if (dealer.handCount() != 5)
			{
				loopCount--;
				shouldBreak = true;
			}

			break;
		}

		if (shouldBreak)
		{
			if (opponentWins)
				opponentWins--;
			else if (ties)
				ties--;
			break;
		}

		dealerScore = dealer.handStatus();
		opponentScore = opponent.handStatus();

		// Get stats for score AFTER SWITCHING CARDS
		if (dealerScore > opponentScore)
			dealerWinsSwitch++;
		else if (dealerScore < opponentScore)
			opponentWinsSwitch++;
		else
			tiesSwitch++;

		dealer.clearHand();
		opponent.clearHand();
	}

	// Game Stats
	cout << endl << "*****************************************" << endl;
	cout << "** GAME STATS BEFORE SWITCH | " << loopCount << " Rounds **" << endl << endl;
	cout << "Dealer Win    : " << dealerWins << endl;
	cout << "Opponent Win  : " << opponentWins << endl;
	cout << "Tie Game      : " << ties << endl;

	cout << endl << "** GAME STATS AFTER SWITCH | " << loopCount << " Rounds **" << endl << endl;
	cout << "Dealer Win    : " << dealerWinsSwitch << endl;
	cout << "Opponent Win  : " << opponentWinsSwitch << endl;
	cout << "Tie Game      : " << tiesSwitch << endl;
}

int main()
{
	part3(); // Play with two players, compare hands | Working

	part4(); // Dealer vs Player | Dealer will switch cards to improve chances

	// part5(); // Incomplete

	return 0;
}
