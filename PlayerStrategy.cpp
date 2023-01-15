#include "PlayerStrategy.h"
#include <algorithm>
using std::cin;
using std::cout;
#include <random>

    
PlayerStrategy::PlayerStrategy(Player *p, string name){
    this->player = p;
    this->name = name;
    this->hasIssued = false;
}
HumanPlayerStrategy::HumanPlayerStrategy(Player *p) : PlayerStrategy(p, "Human"){

}
HumanPlayerStrategy::HumanPlayerStrategy(const HumanPlayerStrategy& obj) : PlayerStrategy(obj.player, obj.name){ 
}
HumanPlayerStrategy& HumanPlayerStrategy::operator=(const HumanPlayerStrategy& obj){
    this->name = obj.name;
    this->player = obj.player;
    return *this;
}
ostream& operator << (ostream &out, const HumanPlayerStrategy& obj){
    out << "Player name " << obj.player->name << "| Type : " << obj.name << "\n";
    return out;
}
AggressivePlayerStrategy::AggressivePlayerStrategy(Player *p) : PlayerStrategy(p, "Aggressive"){

}
AggressivePlayerStrategy::AggressivePlayerStrategy(const AggressivePlayerStrategy& obj) : PlayerStrategy(obj.player, obj.name){ 
}
AggressivePlayerStrategy& AggressivePlayerStrategy::operator=(const AggressivePlayerStrategy& obj){
    this->name = obj.name;
    this->player = obj.player;
    return *this;
}
ostream& operator << (ostream &out, const AggressivePlayerStrategy& obj){
    out << "Player name " << obj.player->name << "| Type : " << obj.name;
    return out;
}
BenevolentPlayerStrategy::BenevolentPlayerStrategy(Player *p) : PlayerStrategy(p, "Benevolent"){

}
BenevolentPlayerStrategy::BenevolentPlayerStrategy(const BenevolentPlayerStrategy& obj) : PlayerStrategy(obj.player, obj.name){ 
}
BenevolentPlayerStrategy& BenevolentPlayerStrategy::operator=(const BenevolentPlayerStrategy& obj){
    this->name = obj.name;
    this->player = obj.player;
    return *this;
}
ostream& operator << (ostream &out, const BenevolentPlayerStrategy& obj){
    out << "Player name " << obj.player->name << "| Type : " << obj.name;
    return out;
}
NeutralPlayerStrategy::NeutralPlayerStrategy(Player *p) : PlayerStrategy(p, "Neutral"){

}
NeutralPlayerStrategy::NeutralPlayerStrategy(const NeutralPlayerStrategy& obj) : PlayerStrategy(obj.player, obj.name){ 
}
NeutralPlayerStrategy& NeutralPlayerStrategy::operator=(const NeutralPlayerStrategy& obj){
    this->name = obj.name;
    this->player = obj.player;
    return *this;
}
ostream& operator << (ostream &out, const NeutralPlayerStrategy& obj){
    out << "Player name " << obj.player->name << "| Type : " << obj.name;
    return out;
}
CheaterPlayerStrategy::CheaterPlayerStrategy(Player *p) : PlayerStrategy(p, "Cheater"){
    this->hasIssued = false;
}
CheaterPlayerStrategy::CheaterPlayerStrategy(const CheaterPlayerStrategy& obj) : PlayerStrategy(obj.player, obj.name){ 
}
CheaterPlayerStrategy& CheaterPlayerStrategy::operator=(const CheaterPlayerStrategy& obj){
    this->name = obj.name;
    this->player = obj.player;
    return *this;
}
ostream& operator << (ostream &out, const CheaterPlayerStrategy& obj){
    out << "Player name " << obj.player->name << "| Type : " << obj.name;
    return out;
}

//Only one that requires interaction
void HumanPlayerStrategy::issueOrder(Deck *d){
    int choice;
    int numorders = 0;
    if(this->player->reinforcement_pool > 0){
        cout << "\n----DEPLOY ORDER-----\n" << endl;
        cout << "Player: " << this->player->name << endl;
        cout << "Enter the Territory you would like to deplay your armies to according to the number associated" << endl;
        printTerritories(this->toDefend());
        cout << "\nChoice: ";
        cin >> choice;
        Territory *toDeployTo = this->toDefend().at(choice);
        cout << "How many armies would you like to deploy to " << toDeployTo->getName() << "? ";
        int armiesToSend;
        cin >> armiesToSend;
        if(armiesToSend <= this->player->reinforcement_pool){
            this->player->orderList->addOrder(new OrderDeploy(this->player, 0,armiesToSend, "Deploy", toDeployTo));
            cout << "Deploy order added by human player("<< this->player->name << ") On: " << toDeployTo->getName() << "\n"<<endl;
            this->player->reinforcement_pool -= armiesToSend;
        }
        else{
            cout << "You Entered an invalid amount " << endl;

        }
        numorders++;
    }
    else{
        cout << "Player: " << this->player->name << endl;

        string input;
        cout << "Do you wish to issue any Advance orders?(yes/no) ";
        cin >> input;
        cout << "\n----Advance ORDER----\n" << endl;
        if(input.compare("yes") == 0){
            string DefendOrAttack;
            cout << "Defend or Attack? ";
            cin >> DefendOrAttack;
            // TODO: checks to make sure player enters a valid number of armies
            // TODO: remove duplocates from toAttack()
            if(DefendOrAttack == "Defend"){
                cout << "Enter the source territory(The territory you wish to move armies from) according to the number associated\n" << endl;
                printTerritories(this->toDefend());
                cout << "Choice: ";
                cin >> choice;
                // choice var may cause issues
                Territory *source = this->toDefend().at(choice);
                cout << "\nYou chose" << source->getName() << endl;
                cout << "Enter the Target territory(The territory you wish to move armies to) according to the number associated\n" << endl;
                printTerritories(this->toDefend());
                cout << "Choice: ";
                cin >> choice;
                Territory *target = this->toDefend().at(choice);
                int armies;
                cout << "\n Enter the number of armies to move from " << source->getName() << " to " << target->getName() << ": "<< endl;
                cin >> armies;
                this->player->orderList->addOrder(new OrderAdvance(this->player,0,armies,"Advance",source,target));
            }else{
                cout << "Enter the source territory(The territory you wish to move armies from) according to the number associated\n" << endl;
                printTerritories(this->toDefend());
                cout << "Choice: ";
                cin >> choice;
                // choice var may cause issues
                Territory *source = this->toDefend().at(choice);
                cout << "\nYou chose" << source->getName() << endl;
                cout << "Enter the Target territory(The territory you wish to Attack) according to the number associated\n" << endl;
                printTerritories(this->toAttack());
                cout << "Choice: ";
                cin >> choice;
                Territory *target = this->toAttack().at(choice);
                int armies;
                cout << "\n Enter the number of armies to move from " << source->getName() << " to " << target->getName() << ": "<< endl;
                cin >> armies;
                this->player->orderList->addOrder(new OrderAdvance(this->player,0,armies,"Advance",source,target));
            }
            numorders++;
        }
    }
    if(numorders == 0){
        cout << "Player: " << this->player->name << endl;

        string input;
        if(this->player->getHand()->get_hand_vector()->size() > 0){
            cout << "You have the following cards: " << endl;
            for(Card *c: *this->player->getHand()->get_hand_vector()){
                        cout << *c->get_card_type() << endl << endl;
                    }        cout << "\nWould you like to use any of your cards?(yes/no) ";
            cin >> input;
            Card *c;
           
            if(input == "yes"){
                string cardChoice;
                cout << "Which card would you like to use?(enter in lowercase) ";
                cin >> cardChoice;
                for(Card *card: *this->player->getHand()->get_hand_vector()){
                    if(cardChoice == *card->get_card_type()){
                        cout << "made it here" << endl;
                        c = card;
                    }
                }   
                cout << "\n----CARD PLAYING-----\n" << endl;
                //TODO nullptr, diplomacy
                if(cardChoice == "bomb"){
                    cout << "Enter the territory you wish to use your Bomb Card on according to the number associated\n";
                    printTerritories(this->toAttack());
                    cin >> choice;
                    Territory *target = this->toAttack().at(choice);
                     cout << "here" << endl;

                    c->play(this->player, d,0, "bomb", target,target, 0);
                }else if(cardChoice == "blockade"){
                    cout << "Enter the territory you wish to use your Blockade Card on according to the number associated\n";
                    printTerritories(this->toDefend());
                    cin >> choice;
                    Territory *target = this->toDefend().at(choice);
                    c->play(this->player, d,0, "blockade", target,target, 0);
                }
                else if(cardChoice == "diplomacy"){
                    cout << "Enter the territory you wish to use the diplomacy card on according to the number associated\n";
                    printTerritories(this->toAttack());
                    cin >> choice; 
                    c->play(this->player, d, 0, "diplomacy", this->toAttack().at(choice), this->toAttack().at(choice),  0);
                }
                else if(cardChoice == "airlift"){
                    cout << "Enter the source territory according to the number associated\n";
                    printTerritories(this->toDefend());
                    cin >> choice;
                    Territory *source = this->toDefend().at(choice);
                    cout << "Enter the target territory according to the number associated\n";
                    printTerritories(this->toDefend());
                    cin >> choice;
                    Territory *target = this->toDefend().at(choice);
                    int armies;
                    cout << "\nEnter the number of army units to airlift from " << source->getName() << " to " << target->getName();
                    cin >> armies;
                    c->play(this->player, d, 0, "airlift", source, target, armies);
                }else if(cardChoice == "reinforcement"){
                    cout << "4 army units added to " << this->player->name << "'s reinforcement pool";
                    this->player->reinforcement_pool += 5;
                }
            }
            numorders++;
        }
    }

};

//Focuses on attack
//Deploys armies on its strongest territory
void AggressivePlayerStrategy::issueOrder(Deck *d){
    std::random_device rd;
    std::mt19937 gen(rd());
    int numorders = 0;
    if(this->player->getTerritories().size() == 0){
        cout << "Player " << this->player->name << " owns no territories and cannot issue any orders, this is likely due to the fact that there is a cheater in the game" << endl;
    }
    else if(this->player->reinforcement_pool > 0){
        cout << "\n----DEPLOY ORDER-----\n" << endl;
        Territory *strongest = this->toDefend().at(0);
        this->player->orderList->addOrder(new OrderDeploy(this->player, 0, this->player->reinforcement_pool, "Deploy", strongest));
        cout << "Deploy order added by Aggressive player("<< this->player->name << ") On: " << strongest->getName() << "\n" << endl;
        this->player->reinforcement_pool = 0;
        numorders++;
    }
    else if((this->toAttack().size() > 0)){
        cout << "\n----Advance ORDER-----\n" << endl;
        uniform_int_distribution<mt19937::result_type> dist(0, this->toAttack().size() - 1);
        Territory *target = this->toAttack().at(dist(gen));
        Territory *source = this->player->toDefend().at(0);
        int deployNum = source->army_units;
        cout << "Advance order added by Aggressive player("<< this->player->name << ") On: " << target->getName() << "\n" <<endl;
        this->player->orderList->addOrder(new OrderAdvance(this->player, 0, deployNum, "Advance", source, target));
    }
    else if(this->player->getHand()->get_hand_vector()->size() > 0){
        Card *c = this->player->getHand()->get_hand_vector()->at(0);
        cout << "\n----Card Playing-----\n" << endl;
                if(*c->get_card_type() == "bomb" && (this->toAttack().size() > 0)){
                    uniform_int_distribution<mt19937::result_type> dist(0, this->toAttack().size() - 1);
                    Territory *target = this->toAttack().at(dist(gen));
                    c->play(this->player, d,0, "bomb", target,target, 0);
                    cout << "Bomb order added by Aggressive player(" << this->player->name << ") On: " << target->getName() << "\n"<< endl;
                }
                else if(*c->get_card_type() == "Diplomacy" && (this->toAttack().size() > 0)){
                    uniform_int_distribution<mt19937::result_type> dist(0, this->toAttack().size() - 1);
                    c->play(this->player, d, 0, "diplomacy", this->toAttack().at(dist(gen)), this->toAttack().at(dist(gen)),  0);
                }
                else if(*c->get_card_type() == "airlift" && (this->toDefend().size() > 0)){
                    Territory *source = this->toDefend().at(0);
                    uniform_int_distribution<mt19937::result_type> dist1(0, this->toDefend().size() - 1);
                    Territory *target = this->toDefend().at(dist1(gen));
                    uniform_int_distribution<mt19937::result_type> dist2(0, source->army_units);
                    c->play(this->player, d, 0, "airlift", source, target, dist2(gen));
                    cout << "Blockade order added by Aggressive player(" << this->player->name << ") From: " << source->getName() << " to " << target->getName() <<endl;   
                }
                else if(*c->get_card_type() == "reinforcement"){
                    cout << "5 army units added to " << this->player->name << "'s reinforcement pool";
                    this->player->reinforcement_pool += 5;
                }
    }
};
void BenevolentPlayerStrategy::issueOrder(Deck *d){
    std::random_device rd;
    std::mt19937 gen(rd());
    if(this->player->getTerritories().size() == 0){
        cout << "Player " << this->player->name << " owns no territories and cannot issue any orders, this is likely due to the fact that there is a cheater in the game" << endl;
    }
    else if(this->player->reinforcement_pool > 0){
        cout << "\n----DEPLOY ORDER-----\n" << endl;
        Territory *weakest = this->toDefend().at(this->toDefend().size() - 1);
        uniform_int_distribution<mt19937::result_type> dist(1, this->player->reinforcement_pool);
        int deployNum = dist(gen);
        this->player->orderList->addOrder(new OrderDeploy(this->player, 0,deployNum, "Deploy", weakest));
        cout << "Deploy order added by Benevolent player("<< this->player->name << ") On: " << weakest->getName() << endl;
        this->player->reinforcement_pool -= deployNum;
    }else if(this->player->toDefend().size() > 0){
        cout << "\n----Advance ORDER-----\n" << endl;
        Territory *weakest = this->toDefend().at(this->toDefend().size() - 1);
        Territory *strongest = this->toDefend().at(0);
        uniform_int_distribution<mt19937::result_type> dist(1, strongest->army_units);
        int deployNum = dist(gen);
        cout << "Advance order added by Benevolent player("<< this->player->name << ") On: " << weakest->getName() << endl;
        this->player->orderList->addOrder(new OrderAdvance(this->player, 0, deployNum, "Advance", strongest, weakest));        
    }
    else if(this->player->getHand()->get_hand_vector()->size() > 0){
        Card *c = this->player->getHand()->get_hand_vector()->at(0);
         cout << "\n----Card Playing-----\n" << endl;
                if(*c->get_card_type() == "blockade" && (this->toDefend().size() > 0)){
                    uniform_int_distribution<mt19937::result_type> dist(0, this->toDefend().size() - 1);
                    Territory *target = this->toDefend().at(dist(gen));
                    c->play(this->player, d,0, "blockade", target,target, 0);   
                    cout << "Blockade order added by Benevolent player(" << this->player->name << ") On: " << target->getName() << endl;
                }
                else if(*c->get_card_type() == "Diplomacy" && (this->toAttack().size() > 0)){
                     uniform_int_distribution<mt19937::result_type> dist(0, this->toAttack().size() - 1);
                    c->play(this->player, d, 0, "diplomacy", this->toAttack().at(dist(gen)), this->toAttack().at(dist(gen)),  0);
                }
                else if(*c->get_card_type() == "airlift" && (this->toDefend().size() > 0)){
                    Territory *strongest = this->toDefend().at(0);
                    Territory *weakest = this->toDefend().at(this->toDefend().size() - 1);
                    uniform_int_distribution<mt19937::result_type> dist(1, strongest->army_units);
                    c->play(this->player, d, 0, "airlift", strongest, weakest, dist(gen));
                    cout << "Airlift order added by Benevolent player(" << this->player->name << ") On: " << weakest->getName() << endl;
                }
                else if(*c->get_card_type() == "reinforcement"){
                    cout << "5 army units added to " << this->player->name << "'s reinforcement pool";
                    this->player->reinforcement_pool += 5;
                }
    }

};
void NeutralPlayerStrategy::issueOrder(Deck *d){
    //Neutral player doesnt issue orders

};

void CheaterPlayerStrategy::issueOrder(Deck *d){
    if(!this->hasIssued){
        cout << "Cheater has conqured: ";
        for(Territory *t: this->toAttack()){
            if(!(t->owner->name == this->player->name)){
                t->owner->removeTerritory(t);
                this->player->addTerritory(t);
                t->owner = this->player;
                cout << t->getName() << ", ";
            }
        }
        cout << endl;
    }
   
}
vector<Territory*> HumanPlayerStrategy::toAttack(){
    vector<Territory*> toAttack;
    for(Territory *t: this->player->getTerritories()){
        for(Territory *neighour: t->getNeighbours()){
            if(neighour->owner->name != this->player->name){
                
                toAttack.push_back(neighour);
            }
        } 
    }
    cout << "\n";
     //Need to remove duplicates since 2 territories can share neighbours
    sort(toAttack.begin(),toAttack.end());
    return removeDuplicates(toAttack);

};

vector<Territory*> AggressivePlayerStrategy::toAttack(){
    vector<Territory*> toAttack;
    for(Territory *t: this->player->getTerritories()){
        for(Territory *neighour: t->getNeighbours()){
            if(neighour->owner->name != this->player->name){
                toAttack.push_back(neighour);
            }
        } 
    }
    return removeDuplicates(toAttack);
};
vector<Territory*> BenevolentPlayerStrategy::toAttack(){

    vector<Territory*> toAttack;
    for(Territory *t: this->player->getTerritories()){
        for(Territory *neighour: t->getNeighbours()){
            if(neighour->owner->name != this->player->name){
                toAttack.push_back(neighour);
            }
        } 
    }
    return removeDuplicates(toAttack);

};

vector<Territory*> NeutralPlayerStrategy::toAttack(){
    vector<Territory*> toAttack;

    return toAttack;

};
vector<Territory*> CheaterPlayerStrategy::toAttack(){
     vector<Territory*> toAttack;
    for(Territory *t: this->player->getTerritories()){
        for(Territory *neighour: t->getNeighbours()){
            if(neighour->owner->name != this->player->name){
                toAttack.push_back(neighour);
            }
        } 
    }
    //Need to remove duplicates since 2 territories can share neighbours
    return removeDuplicates(toAttack);
 

};

vector<Territory*> HumanPlayerStrategy::toDefend(){
    return this->player->getTerritories();

};
vector<Territory*> AggressivePlayerStrategy::toDefend(){
    vector<Territory*> toDefend = this->player->getTerritories();
    //Sort to make it easier to find strongest country
    //Using sort method from std::sort
    sort(toDefend.begin(), toDefend.end(), sortbyStrongest);
    
    return toDefend;
};
vector<Territory*> BenevolentPlayerStrategy::toDefend(){
    vector<Territory*> toDefend = this->player->getTerritories();
    sort(toDefend.begin(), toDefend.end(), sortbyStrongest);
    return toDefend;

};

vector<Territory*> NeutralPlayerStrategy::toDefend(){
    return this->player->getTerritories();

};
vector<Territory*> CheaterPlayerStrategy::toDefend(){
    return this->player->getTerritories();

};

bool sortbyStrongest(Territory *t1, Territory *t2){
    return (t1->army_units > t2->army_units);
};
void printTerritories(vector<Territory*> t){
    for(int i = 0; i < t.size(); i++){
        cout << t[i]->getName() << ": " << i << " || ";
    }
};
vector<Territory*> removeDuplicates(vector<Territory*> &t){
    for(Territory *t2: t){
        t.erase(unique(t.begin(), t.end()), t.end());
    }
    return t;
}

