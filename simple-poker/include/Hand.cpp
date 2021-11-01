#include "Hand.h"


void Hand::setCards(int i, Card c){
	cards[i].setCard(c.getVal(), c.getSuit());
}

Card Hand::getCards(int i){
	return cards[i];
}

void Hand::increaseScore(int s){
	score += s;
}

int Hand::getScore(){
	return score;
}

void Hand::incTtlScore(int s){
	finalScore += s;
}

int Hand::getTtlScore(){
	return finalScore;
}

void Hand::setWithDrawn(bool b){
	hasWithDrawn = b;
}

bool Hand::getHasWithDrawn(){
	return hasWithDrawn;
}

