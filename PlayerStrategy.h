#pragma once

#include "Player.h"
#include "Cards.h"
#include <vector>
class PlayerStrategy{
    public:
        PlayerStrategy(Player *p);
        Player *player;
        virtual void issueOrder(Deck *d) = 0;
        virtual vector<Territory*> toAttack() = 0;
        virtual vector<Territory*> toDefend() = 0;
};

class HumanPlayerStrategy: public PlayerStrategy{
    public:
        HumanPlayerStrategy(Player*);
        void issueOrder(Deck *d) override;
        vector<Territory*> toAttack() override;
        vector<Territory*> toDefend() override;
};

class AggressivePlayerStrategy: public PlayerStrategy{
     public:
        AggressivePlayerStrategy(Player*);
        void issueOrder(Deck *d) override;
        vector<Territory*> toAttack() override;
        vector<Territory*> toDefend() override;
};

class BenevolentPlayerStrategy: public PlayerStrategy{
     public:
        BenevolentPlayerStrategy(Player*);
        void issueOrder(Deck *d) override;
        vector<Territory*> toAttack() override;
        vector<Territory*> toDefend() override;
};


class NeutralPlayerStrategy: public PlayerStrategy{
     public:
        NeutralPlayerStrategy(Player*);
        void issueOrder(Deck *d) override;
        vector<Territory*> toAttack() override;
        vector<Territory*> toDefend() override;
};

class CheaterPlayerStrategy: public PlayerStrategy{
    public:
        CheaterPlayerStrategy(Player*);
        void issueOrder(Deck *d) override;
        vector<Territory*> toAttack() override;
        vector<Territory*> toDefend() override;
};

bool sortbyStrongest(Territory *t1, Territory *t2);
void printTerritories(vector<Territory*> t);