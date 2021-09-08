#ifndef MAGICIANTEAM_H
#define MAGICIANTEAM_H

#include<iostream>
#include "CardInfo.h"

class MagicianTeam{
    private:
        const int noOfCards;
    public:
        MagicianTeam(int x);
        int getNoOfCards() const;
};

#endif
