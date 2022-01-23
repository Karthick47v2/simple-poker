#include "Card.h"

Card::Card() {}

Card::Card(Value v, Suit s) : val(v), suit(s){}

void Card::setCard(Value v, Suit s){
	val = v;
	suit = s;
}

Value Card::getVal(){
	return val;
}

Suit Card::getSuit(){
	return suit;
}	

std::string Card::getValName(){
	switch (val){
		case Two: return "Two";
		case Three: return "Three";
		case Four: return "Four";
		case Five: return "Five";
		case Six: return "Six";
		case Seven: return "Seven";
		case Eight: return "Eight";
		case Nine: return "Nine";
		case Ten: return "Ten";
		case Jack: return "Jack";
		case Queen: return "Queen";
		case King: return "King";
		default: return "Ace";
		}
}	

std::string Card::getSuitName(){
	switch (suit){
		case Clubs: return "Clubs";
		case Diamonds: return "Diamonds";
		case Hearts: return "Hearts";
		default: return "Spades";
	}
}
