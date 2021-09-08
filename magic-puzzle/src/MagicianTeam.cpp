#include "MagicianTeam.h"

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
