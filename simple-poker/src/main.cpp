#include <iostream>
#include <string>
#include <ctime>
#include <cstdlib>
#include <fstream>
#include "../include/Card.h"
#include "../include/Hand.h"

#define CARD_SIZE 52

// -----poker game-----
void shuffleNDistributed(Card deck[CARD_SIZE], int noOfPlayers, Hand hands[], int roundNo);
int playPoker(Hand hands[], int noOfPlayers, int roundNo);
void tieSituation(int noOfPlayers, int players[], Hand hands[], int count);

// -----scoring func-----
bool isStraightFlush(Hand hand);
bool isFourOfAKind(Hand hand);
bool isFullHouse(Hand hand);
bool isFlush(Hand hand);
bool isStraight(Hand hand);
bool isThreeOfAKind(Hand hand);
bool isTwoPairs(Hand hand);
bool isOnePair(Hand hand);

// -----helper func-----
void swap(Hand *hand, int i);
void displayScoreCard(Hand hands[], int noOfPlayers);
void showCards(Hand hand);
void logData(Hand hands[], int noOfPlayers, int roundNo);

// display score and probability
void displayScoreCard(Hand hands[], int noOfPlayers){
	std::cout << "\n\nPlayer\t\t" << "Score\n";
	
	for(int i = 0; i < noOfPlayers; i++){
		std::cout << "Player " << i + 1 << "\t\t" << hands[i].getTtlScore();
		if(hands[i].getHasWithDrawn()){
			std::cout << " (withdrawn)";
			hands[i].setWithDrawn(false);
		}
		std::cout  << "\n";
	}
	std::cout << "\n";
}

// swap cards on hand
void swap(Hand *hand, int i){
	Card c(hand -> getCards(i).getVal(), hand -> getCards(i).getSuit());
	hand -> setCards(i, Card(hand -> getCards(i + 1).getVal(), hand -> getCards(i + 1).getSuit()));
	hand -> setCards(i + 1, c);
}

// shuffle and distribute
void shuffleNDistribute(Card deck[CARD_SIZE], int noOfPlayers, Hand hands[], int roundNo){
	
	int dealerNo = rand() % noOfPlayers;											// hold which plr is dealer
	
	std::cout << "\nCurrently dealer is Player" << dealerNo + 1 << '\n';
	
	// shuffle
	std::cout << "Dealer shuffling cards...\n";
	for(int i = 0; i < CARD_SIZE; i++){
		int  j = rand() % CARD_SIZE;
		Card temp = deck[i];
		deck[i] = deck[j];
		deck[j] = temp;
	}	
	
	//instead of dropping 2 cards we consider, omitting first 2 elements for array
	int i = 2;
	
	//distribute
	std::cout << "Dealer distributing cards...\n";
	for(int j = 0; j < 5; j++){
		for(int k = 0; k < noOfPlayers; k++){
			hands[k].setCards(j, deck[i++]);
		}
	}
	
	std::cout << "Cards distributed among players\n";
	
	std::cout << "\nCards in dealer hand are ...\n";
	showCards(hands[dealerNo]);
	
	// sort cards in value order, as we need to chk Straight / SF - as only 5 elements bubble sort is effficient
	for(int k = 0; k < noOfPlayers; k++){
		for(int i = 0; i < 5; i++){
			for(int j = 0; j < 4; j++){	
				if(hands[k].getCards(j).getVal() > hands[k].getCards(j + 1).getVal()){
					swap(&hands[k], j);
				}	
			}
		}
	}
	
	for(int i = 0; i < noOfPlayers; i++){
		if(i == dealerNo) continue;
		char userInput;
		do{
			std::cout << "\nPlayer " << i + 1 << " .. Do you want to withdraw this round? (Y/N) :";
			std::cin >> userInput;
		}while(userInput != 'Y' && userInput != 'N');
		
		if(userInput == 'Y') hands[i].setWithDrawn(true);
	}
	
	int ind = playPoker(hands, noOfPlayers, roundNo);
	
	// for dealer inc 1 in final score (1 - 1 => 0)	
	// for winner inc 11  in ttlScore (11 - 1 => 10) (if he is not the dealer)
	hands[dealerNo].incTtlScore(1);	
	if(ind != dealerNo) hands[ind].incTtlScore(11);
	displayScoreCard(hands, noOfPlayers);
	logData(hands, noOfPlayers, roundNo);
}

// return index of winner
int playPoker(Hand hands[], int noOfPlayers, int roundNo){	
	int count = 0;																		// keep count of max score (to check tie)
	
	for(int i = 0; i < noOfPlayers; i++){
		if(hands[i].getHasWithDrawn()) continue;											// if withdrawn, skip player 
		
		if(isStraightFlush(hands[i])){
			hands[i].increaseScore(9);	
			count = 9;
		}
		else if(isFourOfAKind(hands[i])){
			hands[i].increaseScore(8);
			count = std::max(count, 8);
		}
		else if(isFullHouse(hands[i])){
			hands[i].increaseScore(7);
			count = std::max(count, 7);
		}
		else if(isFlush(hands[i])){
			hands[i].increaseScore(6);
			count = std::max(count, 6);
		}
		else if(isStraight(hands[i])){
			hands[i].increaseScore(5);
			count = std::max(count, 5);
		}
		else if(isThreeOfAKind(hands[i])){
			hands[i].increaseScore(4);
			count = std::max(count, 4);
		}
		else if(isTwoPairs(hands[i])){
			hands[i].increaseScore(3);
			count = std::max(count, 3);
		}
		else if(isOnePair(hands[i])){
			hands[i].increaseScore(2);
			count = std::max(count, 2);
		}
		else{
			hands[i].increaseScore(1);
			count = std::max(count, 1);
		}
	}
	
	// Tie check
	int players[noOfPlayers] = {0};						// 1 - same max score, 0 - no
	int noOfTiedPlayers = 0;							// keep count of no of tied players
	
	// marks players with same highscore (count)
	for(int i = 0; i < noOfPlayers; i++){
		if(count == hands[i].getScore()){
			players[i]++;
			noOfTiedPlayers++;
		}
	}
	
	// if tie situation
	if(noOfTiedPlayers > 1){					  		// it always will be 1 coz we are counting
		tieSituation(noOfPlayers, players, hands, count);// how many players have same high score so
	}											  		// if its 1 thats not tie sitation
	
	std::string cardOrder;
	
	switch(count){
		case 1:
			cardOrder = "High Card\n";
			break;
		case 2:
			cardOrder = "One Pair\n";
			break;
		case 3:
			cardOrder = "Two Pairs\n";
			break;
		case 4:
			cardOrder = "Three of A Kind\n";
			break;
		case 5:
			cardOrder = "Straight\n";
			break;
		case 6:
			cardOrder = "Flush\n";
			break;
		case 7:
			cardOrder = "Full House\n";
			break;
		case 8:
			cardOrder = "Four of A Kind\n";
			break;
		case 9:
			cardOrder = "Straight Flush\n";
			break;
	}
	
	// find final winner
	count = 0;										
	int ind = 0;										// store indeox of player array
	
	// find player with highscore and inc score
	// for everyone as -1
	for(int i = 0; i < noOfPlayers; i++){
		if(players[i] >= count){
			count = players[i];
			ind = i;
		}
		if(!hands[i].getHasWithDrawn()) hands[i].incTtlScore(-1);
	}
	
	std::cout << "\nWinner for Round " << roundNo << " is Player " << ind + 1 << " - " << cardOrder; 	
	std::cout << "\n Winners cards ...\n";
	
	showCards(hands[ind]);
	
	return ind;
}

void showCards(Hand hand){
	std::string s = "";
	for(int i = 0; i < 5; i++){
		std::cout << s << hand.getCards(i).getValName() << " of " << hand.getCards(i).getSuitName();
		s = ", ";
	}
	std::cout << "\n";
}

void tieSituation(int noOfPlayers, int players[], Hand hands[], int count){
	for(int i = 0; i < noOfPlayers; i++){
		if(players[i] == 0) continue;
		/*for all scenario we can just add all cards val 
		  and check the lead, but not for Straight and 
		  Straight Flush as the ACES can come up in end
		  or front ,,,, like in Straight Flush , A 2 3 4 5
		  and 2 3 4 5 6..as we put A - 14 in enum, it doesnt
		  show real winner*/
		  
		  if(hands[i].getCards(0).getVal() == 14 && (count == 9 || count  == 5)){		//if first card is A then he gets low score than others so we can skip it	
		  	  //do nothing
		  }
		  else{
		  	for(int j = 0; j < 5; j++){
		  		players[i] += hands[i].getCards(j).getVal();
			  }
		  }
		
	}
}

/*All 5 consecutive cards are in one suit
  it needs to fullfill conditions of straight 
  and flush*/
bool isStraightFlush(Hand hand){
	return (isFlush(hand) && isStraight(hand));
	
}

/*All 4 with same val
  cards are sorted in val order so, for 4 cards to be
  same (val) first and last - 1 needs to be same (so mid ones
  will be same) or second and last needs to be same.*/
bool isFourOfAKind(Hand hand){
	return (hand.getCards(0).getVal() == hand.getCards(3).getVal()
		|| hand.getCards(1).getVal() == hand.getCards(4).getVal());
}

/* 3s and 2s combination
   here also using same idea using in Four of a kind it is
   sorted so there is only 3 possibility, -3-2- , 1-3-1-,
   -2-3-  but 2nd possibility is not valid because first and 
   last are not same so we just need to chk for 1st n 3rd possiblity
   so, it must satisfy Three of A kind first*/
bool isFullHouse(Hand hand){
	return (isThreeOfAKind(hand) && (hand.getCards(3).getVal() == hand.getCards(4).getVal()
		|| hand.getCards(2).getVal() == hand.getCards(4).getVal()));
}

/*All 5 are same suit
  loop unitl different suit is identified
  if not, then its FLUSH*/
bool isFlush(Hand hand){
	for(int i = 0; i < 4; i++){
		if(hand.getCards(i).getSuit() != hand.getCards(i+1).getSuit()) return false;
	}
	return true;
}

/*All 5 are consecutive
  cards are already sorted so incase of Aces
  it will be last, so if it comes we can put it
  infront of 2 or at the end of King , therefore
  that check made first. then for other combinations
  just chk whether next one is one greater than prev*/
bool isStraight(Hand hand){
	if(hand.getCards(4).getVal() == 14){
		int ttl = 0;
		for(int i = 0; i < 4; i++){
			ttl += hand.getCards(i).getVal();
		}
		if(ttl == 14 || ttl == 46) return true;
		else return false;
	}
	else{
		for(int i = 0; i < 4; i++){
			if((hand.getCards(i).getVal() + 1) != hand.getCards(i + 1).getVal()) return false;
		}
	}
	return true;
}

/*All 3 cards with same val
  as cards are sorted Here there are three possibility
  -3-2-, -1-3-1-, -2-3- */
bool isThreeOfAKind(Hand hand){
	return (hand.getCards(0).getVal() == hand.getCards(2).getVal()
		|| hand.getCards(1).getVal() == hand.getCards(3).getVal()
		|| hand.getCards(2).getVal() == hand.getCards(4).getVal());
}

/*2 x 2 same val cards
  cards are sorted soPossibilities are -2-2-1-, -1-2-2-*/
bool isTwoPairs(Hand hand){
	return ((hand.getCards(0).getVal() == hand.getCards(1).getVal()
		&& hand.getCards(2).getVal() == hand.getCards(3).getVal())
		|| (hand.getCards(1).getVal() == hand.getCards(2).getVal()
		&& hand.getCards(3).getVal() == hand.getCards(4).getVal()));
}

/*One pair needs to be same
  Just loop through cards*/
bool isOnePair(Hand hand){
	for(int i = 0; i < 4; i++){
		if(hand.getCards(i).getVal() == hand.getCards(i + 1).getVal()) return true;
	}
	return false;
}

void logData(Hand hands[], int noOfPlayers, int roundNo){
	std::ofstream file;
	file.open("./log/log.txt", std::fstream::app);
	
	for(int i = 0; i < noOfPlayers; i++){
		file << "Round " << roundNo  << " Player " << i + 1 << " ";
		for(int j = 0; j < 5; j++){
			file << hands[i].getCards(j).getValName() << " of " << hands[i].getCards(j).getSuitName() << " ";
		}
		 file << hands[i].getTtlScore() << "\n";
	} 
	
	file.close();
}

int main(){
	
	srand((unsigned) time(NULL));

	//Initialize cards 
	Card deck[CARD_SIZE];
	int c = 0;
	
	//And assign values to them
	for(int i = Hearts; i <= Clubs; i++){
		for(int j = Two; j <= Ace; j++){
			deck[c++].setCard(static_cast<Value>(j), static_cast<Suit>(i));
		}
	}
	
	int noOfPlayers;
	
	std::cout << "How many players (2 - 10) :";
	std::cin >> noOfPlayers;
	
	while(std::cin.fail() || (noOfPlayers < 2 || noOfPlayers > 10)){
		std::cout << "Enter integer b/w 2 - 10 (range inclusive)\n";
		std::cin.clear();
		std::cin.ignore(100, '\n');
		std::cin >> noOfPlayers;
	}
	
	Hand* hands = new Hand[noOfPlayers];
	
	int noOfRounds;
	
	std::cout << "How many rounds :";
	std::cin >> noOfRounds;
	
	while(std::cin.fail() || noOfRounds < 0){
		std::cout << "Enter integer above 0 \n";
		std::cin.clear();
		std::cin.ignore(100, '\n');
		std::cin >> noOfRounds;
	}	

	//shuffle, drop and distribute
	int i = 1;
	while(i <= noOfRounds){
		shuffleNDistribute(deck, noOfPlayers, hands, i++);
	}
	
	//pause until key pressed first is for omiting key buffer
	getchar();
	getchar();
	
	//free hands memory block
	delete [] hands;	
	return 0;
}
