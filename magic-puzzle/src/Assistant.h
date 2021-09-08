#ifndef ASSISTANT_H
#define ASSISTANT_H

#include "MagicianTeam.h"

class Assistant: public MagicianTeam{
    public:
        Assistant();
        void orderCards() const;
};

#endif
