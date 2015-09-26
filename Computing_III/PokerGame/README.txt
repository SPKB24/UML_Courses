README FOR POKER PROGRAM
************************
Sohit Pal
Computing III
May 8, 2015
************************

(By Submission Instruction Outline)

1. 
Created Card and DeckOfCards class to fit the needs of the game perfectly.
Also created Hand class to hold users current hand of cards, used to make 
operations easier and more global.

2.
Created functions to find if the hand was a straight, flush, 4 of a kind, etc...
Tested all, works perfectly.

3.
Created sub fuction to run two player game. Main function will automatically
run it.

	1. Deal 5 cards to each player.
	2. Check status for both.
	3. Compare status'.
	4. Add to stats.
	5. Repeat steps 1 - 4 until all cards run out.
	6. Print stats.

4. 
General template of this function goes as follows:
	
	1. Deal 5 cards to dealer and 5 cards to player.
	2. Check status for each.
	3. Compare status'. 
	4. Add to stats (for BEFORE SWITCH).
	5. Evaluate dealers hand to replace cards to improve winning chances.
		a. Straight    - No Improvements
		b. Flush       - No Improvements | More chances of hurting 
						   than gaining
		c. 4 of a kind - No Improvements | More chances of hurting 
						   than gaining
		d. 3 of a kind - Replace 2 cards | Hope to get 4 of a kind
		e. Two Pair    - Replace 1 card  | Hope to get 3 of a kind
		f. Pair        - Replace 3 cards | Hope to get atleast 3 of 
						   a kind
		g. Nothing     - Replace 3 cards | 3 is maximum allowed, hope
						   for anything...
	6. Replace cards and re-evaluate dealers hand.
	7. Add new scores to stats.
	8. Loop 1 - 7 until cards run out.
	9. Print stats.


DISCLAIMER: This has been slightly odd sometimes, sometimes it manages to 
	    hurt the dealer instead of help.

5. 
Unfinished. Ran out of time.
