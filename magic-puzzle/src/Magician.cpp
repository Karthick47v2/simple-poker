#include "Magician.h"

Magician::Magician(): MagicianTeam(4) {}

void Magician::findHiddenCard() const{
    CardInfo userSelectedCards[getNoOfCards()];

    //User input
    for(int i = 0; i <getNoOfCards(); i++){
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
    }

    int secretCode;
    /* Check conditions according to
                        s => small m => medium l => large
        s m l = 1
        s l m = 2
        m s l = 3
        m l s = 4
        l s m = 5
        l m s = 6
    */
    if(userSelectedCards[1].getCardIndex() < userSelectedCards[2].getCardIndex() && userSelectedCards[1].getCardIndex() < userSelectedCards[3].getCardIndex()){
        if(userSelectedCards[2].getCardIndex() < userSelectedCards[3].getCardIndex()){
            secretCode = 1;
        }
        else{
            secretCode = 2;
        }
    }
    else if((userSelectedCards[1].getCardIndex() < userSelectedCards[2].getCardIndex() && userSelectedCards[1].getCardIndex() > userSelectedCards[3].getCardIndex()) || (userSelectedCards[1].getCardIndex() > userSelectedCards[2].getCardIndex() && userSelectedCards[1].getCardIndex() < userSelectedCards[3].getCardIndex())){
        if(userSelectedCards[2].getCardIndex() < userSelectedCards[3].getCardIndex()){
            secretCode = 3;
        }
        else{
            secretCode = 4;
        }
    }
    else if(userSelectedCards[1].getCardIndex() > userSelectedCards[2].getCardIndex() && userSelectedCards[1].getCardIndex() > userSelectedCards[3].getCardIndex()){
        if(userSelectedCards[2].getCardIndex() < userSelectedCards[3].getCardIndex()){
            secretCode = 5;
        }
        else{
            secretCode = 6;
        }
    }

    int magicNo = (userSelectedCards[0].getCardRankIndex() + secretCode) % 13;
    int hiddenCardIndex = magicNo * 4 + userSelectedCards[0].getCardSuitIndex();

    std::cout << "Hidden card is " << deck[hiddenCardIndex];
}

