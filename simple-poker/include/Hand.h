#ifndef STACK_H
#define STACK_H

#include "Card.h"

// data struct to hold player
class Hand{
	private:
		Card cards[5];																// each player has 5 cards
		int score = 0;																// each round score
		int finalScore = 0;															// ttl score
		bool hasWithDrawn = false;													// var of indicating withdrawal
	public:
		void setCards(int i, Card c);												// setter - set each card
		void increaseScore(int s);													// score increment
		void incTtlScore(int s);													// increase final score
		void setWithDrawn(bool b);													// setter for withdrawn
		Card getCards(int i);														// getter - get each card
		int getScore();																// get score
		int getTtlScore();															// get final score
		bool getHasWithDrawn();														// getter for withdrawn
};

#endif
