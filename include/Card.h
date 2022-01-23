#ifndef CARD_H
#define CARD_H

#include <string>

enum Value {Two = 2, Three, Four, Five, Six, Seven, Eight, Nine, Ten, Jack, Queen, King, Ace};
enum Suit  {Hearts, Spades, Diamonds, Clubs};

// data struct to hold card info
class Card{
	private:
		Value val;
		Suit suit;
	public:
		Card();
		Card(Value v, Suit s);
		void setCard(Value v, Suit s);												// setter
		Value getVal();																// card
		Suit getSuit();																//    getters
		std::string getValName();													// get by
		std::string getSuitName();													//     name
};


#endif
