#ifndef MAGICIAN_H
#define MAGICIAN_H

#include "MagicianTeam.h"

class Magician: public MagicianTeam{
    public:
        Magician();
        void findHiddenCard() const;
};

#endif
