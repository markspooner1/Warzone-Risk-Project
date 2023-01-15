#pragma once

#include "Player.h"
#include "Cards.h"
#include <vector>
class PlayerStrategy{
    public:
        PlayerStrategy(Player *p, string name);
        Player *player;
        string name;
        bool hasIssued;
        virtual void issueOrder(Deck *d) = 0;
        virtual vector<Territory*> toAttack() = 0;
        virtual vector<Territory*> toDefend() = 0;
};

class HumanPlayerStrategy: public PlayerStrategy{
    public:
        HumanPlayerStrategy(Player*);
        HumanPlayerStrategy(const HumanPlayerStrategy& obj);
        HumanPlayerStrategy& operator=(const HumanPlayerStrategy& obj);
        friend ostream& operator <<(ostream& o, const HumanPlayerStrategy &obj);
        void issueOrder(Deck *d) override;
        vector<Territory*> toAttack() override;
        vector<Territory*> toDefend() override;

};

class AggressivePlayerStrategy: public PlayerStrategy{
     public:
        AggressivePlayerStrategy(Player*);
        AggressivePlayerStrategy(const AggressivePlayerStrategy& obj);
        AggressivePlayerStrategy& operator=(const AggressivePlayerStrategy& obj);
        friend ostream& operator <<(ostream& o, const AggressivePlayerStrategy &obj);
        void issueOrder(Deck *d) override;
        vector<Territory*> toAttack() override;
        vector<Territory*> toDefend() override;
};

class BenevolentPlayerStrategy: public PlayerStrategy{
     public:
        BenevolentPlayerStrategy(Player*);
        BenevolentPlayerStrategy(const BenevolentPlayerStrategy& obj);
        BenevolentPlayerStrategy& operator=(const BenevolentPlayerStrategy& obj);
        friend ostream& operator <<(ostream& o, const BenevolentPlayerStrategy &obj);
        void issueOrder(Deck *d) override;
        vector<Territory*> toAttack() override;
        vector<Territory*> toDefend() override;
};


class NeutralPlayerStrategy: public PlayerStrategy{
     public:
        NeutralPlayerStrategy(Player*);
        NeutralPlayerStrategy(const NeutralPlayerStrategy& obj);
        NeutralPlayerStrategy& operator=(const NeutralPlayerStrategy& obj);
        friend ostream& operator <<(ostream& o, const NeutralPlayerStrategy &obj);
        void issueOrder(Deck *d) override;
        vector<Territory*> toAttack() override;
        vector<Territory*> toDefend() override;
};

class CheaterPlayerStrategy: public PlayerStrategy{
    public:
       
        CheaterPlayerStrategy(Player*);
        CheaterPlayerStrategy(const CheaterPlayerStrategy& obj);
        CheaterPlayerStrategy& operator=(const CheaterPlayerStrategy& obj);
        friend ostream& operator <<(ostream& o, const CheaterPlayerStrategy &obj);
        void issueOrder(Deck *d) override;
        vector<Territory*> toAttack() override;
        vector<Territory*> toDefend() override;
};

bool sortbyStrongest(Territory *t1, Territory *t2);
void printTerritories(vector<Territory*> t);
vector<Territory*> removeDuplicates(vector<Territory*> &t);
void testPlayerStrategies();