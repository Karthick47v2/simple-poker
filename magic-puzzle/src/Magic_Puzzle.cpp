/*My kind of implementation for  'Puzzle 3: You Can Read Minds'.. You can get to know the problem 
from here, https://www.youtube.com/watch?v=zDHhHPZm2rc'*/

#include<iostream>
#include<string>
#include <vector>
#include <math.h>

//As deck of cards is finite number put all decks for ease of access - make it as global var
std::string deck[] = {"AC","AD","AH","AS","2C","2D","2H","2S","3C","3D","3H","3S","4C","4D","4H","4S",
                  "5C","5D","5H","5S","6C","6D","6H","6S","7C","7D","7H","7S","8C","8D","8H","8S",
                  "9C","9D","9H","9S","10C","10D","10H","10S","JC","JD","JH","JS","QC","QD","QH","QS",
                  "KC","KD","KH","KS"};

/*Structure for holding card name  i.e => {rank = 'A', suit = 'C'}
  We dont need to take rank as char array (coz 10 has 2 chars), coz
  we can just take 1 as there is not 1 bw A and 2 and also we order
  the cards according to deck array's index*/
  
struct Card{
    char rank;
    char suit[2];
    Card() {};
    Card(std::string str){
        rank = str[0];
        for(int i = 1; i < str.length(); i++){
            suit[i - 1] = str[i];
        }
    }
};

class CardInfo{
    private:   
        int cardIndex;                                                      //Card's index from deck array
        int cardSuitIndex;                                                  //Card suit's index (C = 0, D = 1, H = 2, S = 3)
        int cardRankIndex;                                                  //Card rank's index (A = 0, 2 = 1, ......K = 12)
    public:
        Card card;                                                          //Make card public for accessing its data easily
        CardInfo();                                                         //a default constructor
        void setCardInfo(int n, int m, int k);            //}
        int getCardIndex() const;                                           //} GETTERS
        int getCardSuitIndex() const;                                       //}         & SETTERS
        int getCardRankIndex() const;                                       //}
};

class MagicianTeam{
    private:
        const int noOfCards;
    public:
        MagicianTeam(int x);
        int getNoOfCards() const;
};

class Magician: public MagicianTeam{
    public:
        Magician();
        void findHiddenCard() const;
};

class Assistant: public MagicianTeam{
    public:
        Assistant();
        void orderCards() const;
};
	
 void getFirstCard(CardInfo cardInfo[], std::vector<int> pairedCardsIndex, int &secretCode);
 int findIndex(std::string str);
 void swap(int *a, int *b);
 void bubbleSort(int arr[], int n);
 void getHelperCards(int helperCards[], int secretCode);

CardInfo::CardInfo(): cardIndex(0), cardSuitIndex(0), cardRankIndex(0), card({'\0', '\0'}) {}

void CardInfo::setCardInfo(int n, int m, int k){
    cardIndex = n;
    cardSuitIndex = m;
    cardRankIndex = k;
}

int CardInfo::getCardIndex() const{
    return cardIndex;
}

int CardInfo::getCardSuitIndex() const{
    return cardSuitIndex;
}

int CardInfo::getCardRankIndex() const{
    return cardRankIndex;
}

MagicianTeam::MagicianTeam(int x) : noOfCards(x){
    std::cout << "Below shows 52 cards in a deck : ";
    for(int i = 0; i < sizeof(deck)/sizeof(deck[0]); i++){
        if(i % 12 == 0) std::cout << "\n";
        std::cout << deck[i] << "\t";
    }
    std::cout << "\n\n*Use the same naming convention*\n\n";
}

int MagicianTeam::getNoOfCards() const{
    return noOfCards;
}

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

/* As we are sorting only 3 numbers bubble sort
   is efficient
*/
void bubbleSort(int arr[], int n){
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n - 1; j++){
            if(arr[j] > arr[j + 1]){
                swap(&arr[j], &arr[j + 1]);
            }
        }
    }
}

void swap(int *a, int *b){
    int temp = *a;
    *a = *b;
    *b = temp;
}

void getFirstCard(CardInfo cardInfo[], std::vector<int> pairedCardsIndex, int &secretCode){
    int n = cardInfo[pairedCardsIndex[0]].getCardRankIndex() - cardInfo[pairedCardsIndex[1]].getCardRankIndex();
    secretCode = n -  floor(n / 13.0) * 13;
    int hintCard;
    if(secretCode > 0 && secretCode <= 6){
        hintCard = pairedCardsIndex[1];
    }
    else{
        hintCard = pairedCardsIndex[0];
        secretCode = -n - floor(-n / 13.0) * 13;
    }

    std::cout << "First card is " << cardInfo[hintCard].card.rank << cardInfo[hintCard].card.suit << ".\n";
}

void getHelperCards(int helperCards[], int secretCode){
    int card1, card2, card3;
    switch(secretCode){
        case 1:
            card1 = helperCards[0];
            card2 = helperCards[1];
            card3 = helperCards[2];
            break;
        case 2:
            card1 = helperCards[0];
            card2 = helperCards[2];
            card3 = helperCards[1];
            break;
        case 3:
            card1 = helperCards[1];
            card2 = helperCards[0];
            card3 = helperCards[2];
            break;
        case 4:
            card1 = helperCards[1];
            card2 = helperCards[2];
            card3 = helperCards[0];
            break;
        case 5:
            card1 = helperCards[2];
            card2 = helperCards[0];
            card3 = helperCards[1];
            break;
        default:
            card1 = helperCards[2];
            card2 = helperCards[1];
            card3 = helperCards[0];
            break;
    }
    std::cout << "Second Card is " << deck[card1] << "\n";
    std::cout << "Third Card is " << deck[card2] << "\n";
    std::cout << "Fourth Card is " << deck[card3] << "\n";
}

/*finding index and also MODIFYING val for
  countering duplicate issues */
int findIndex(std::string str){
    for(int i = 0; i < sizeof(deck)/sizeof(deck[0]); i++){
        if(str == deck[i]){
        	deck[i] += ".";
        	return i;
		} 
    }
    return -1;
}

int main(){
	
	char userInput;
    
    do{
		std::cout << "Assist \n(A)Magician Helper \n\t\tor \n(B)Magician ? \n";
		std::cin >> userInput;
	}while(userInput != 'A' && userInput != 'B');
	
	if(userInput == 'A'){
		Assistant assistant;
		assistant.orderCards();
	}
    else{
    	Magician magician;
    	magician.findHiddenCard();																			
	}
    return 0;
}
