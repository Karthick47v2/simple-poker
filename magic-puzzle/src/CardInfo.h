#ifndef CARDINFO_H
#define CARDINFO_H

#include<string>
#include <vector>

extern std::string deck[52];

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
        void setCardInfo(int n, int m, int k);            					//}
        int getCardIndex() const;                                           //} GETTERS
        int getCardSuitIndex() const;                                       //}         & SETTERS
        int getCardRankIndex() const;                                       //}
};

//---Helper functions---
 void getFirstCard(CardInfo cardInfo[], std::vector<int> pairedCardsIndex, int &secretCode);
 int findIndex(std::string str);
 void swap(int *a, int *b);
 void bubbleSort(int arr[], int n);
 void getHelperCards(int helperCards[], int secretCode);

#endif
