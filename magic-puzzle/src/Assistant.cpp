#include "Assistant.h"

Assistant::Assistant(): MagicianTeam(5) {}

void Assistant::orderCards() const{
    CardInfo userSelectedCards[getNoOfCards()];

    int suitCount[] = {0,0,0,0};                                                            //count no of cards in each suit

    int hasPairSuitAtIndex;                                                                 //index of same suit(if any)

    for(int i = 0; i < getNoOfCards(); i++){
		int n;
		do{
			std::cout << "Enter card " << i + 1 <<  " name : ";
		    std::cin >> userSelectedCards[i].card.rank >> userSelectedCards[i].card.suit;
		    
		    std::string cardName  = "";
	    	cardName += userSelectedCards[i].card.rank;
	    	cardName += userSelectedCards[i].card.suit;
	    	
	    	n = findIndex(cardName);
		}while(n == -1);
		
	    userSelectedCards[i].setCardInfo( n, n % 4, n / 4);

        suitCount[n % 4]++;

        if(suitCount[n % 4] > 1){
            hasPairSuitAtIndex = n % 4;
        }
    }

    /*
        5 cards, there are only 4 suits so always one suit will
        appear more than 1 time, but there is also a chance
        where all cards can be in same suit so using vector
        will be a convenient way
    */

    std::vector<int> pairedCardsIndex;
    for(int i = 0; i < getNoOfCards(); i++){
        if(userSelectedCards[i].getCardSuitIndex() == hasPairSuitAtIndex){
            pairedCardsIndex.push_back(i);
        }
    }
    int secretCode = 0;

    /*
        No matter how many cards have same suit, we just need
        2 random same suit cards so in getFirstCard function
        we just focus on 0th and 1th index of pairedCardsIndex
        array.
    */

    getFirstCard(userSelectedCards, pairedCardsIndex, secretCode);

    int remainingCards = 3;
    int helperCards[remainingCards];

    for(int i = 0, j = 0; i < getNoOfCards(); i++){
        if(i != pairedCardsIndex[0] && i != pairedCardsIndex[1]){
            helperCards[j++] = userSelectedCards[i].getCardIndex();
        }
    }

    bubbleSort(helperCards, remainingCards);                                    //Sort remaining 3 cards so we can generate our secret code
    getHelperCards(helperCards, secretCode);
}
