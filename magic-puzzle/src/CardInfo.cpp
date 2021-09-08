#include "CardInfo.h"

//As deck of cards is finite number put all decks for ease of access - make it as global var
std::string deck[] = {"AC","AD","AH","AS","2C","2D","2H","2S","3C","3D","3H","3S","4C","4D","4H","4S",
                  "5C","5D","5H","5S","6C","6D","6H","6S","7C","7D","7H","7S","8C","8D","8H","8S",
                  "9C","9D","9H","9S","10C","10D","10H","10S","JC","JD","JH","JS","QC","QD","QH","QS",
                  "KC","KD","KH","KS"};


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
