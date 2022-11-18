#include "PlayerStrategy.h"
#include <algorithm>
using std::cin;
using std::cout;
PlayerStrategy::PlayerStrategy(Player *p){
    this->player = p;
}
HumanPlayerStrategy::HumanPlayerStrategy(Player *p) : PlayerStrategy(p){

}
AggressivePlayerStrategy::AggressivePlayerStrategy(Player *p) : PlayerStrategy(p){

}
BenevolentPlayerStrategy::BenevolentPlayerStrategy(Player *p) : PlayerStrategy(p){

}
NeutralPlayerStrategy::NeutralPlayerStrategy(Player *p) : PlayerStrategy(p){

}
CheaterPlayerStrategy::CheaterPlayerStrategy(Player *p) : PlayerStrategy(p){

}


void HumanPlayerStrategy::issueOrder(Deck *d){
    cout << "\n----DEPLOY ORDERS-----\n" << endl;
    int choice;
    int numorders = 0;
    if(this->player->reinforcement_pool > 0){
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
            this->player->reinforcement_pool -= armiesToSend;
            this->player->orderList->addOrder(new OrderDeploy(this->player, 0,armiesToSend, "Deploy", toDeployTo));
            cout << "Deploy order added by human player("<< this->player->name << ") On: " << toDeployTo->getName() << endl;
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
        cout << "\n----Advance ORDERS----\n" << endl;
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
                // }else if(cardChoice == "Diplomacy"){
                //     cout << "Enter the territory you wish to use the diplomacy card on according to the number associated\n";
                //     printTerritories(this->toAttack());
                //     cin >> choice;
                //     Territory *target = this->toAttack().at(choice)
                //}
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
void AggressivePlayerStrategy::issueOrder(Deck *d){
    

};
void BenevolentPlayerStrategy::issueOrder(Deck *d){
    

};
void NeutralPlayerStrategy::issueOrder(Deck *d){
    

};
void CheaterPlayerStrategy::issueOrder(Deck *d){
    

};


vector<Territory*> HumanPlayerStrategy::toAttack(){
    vector<Territory*> toAttack;
    for(Territory *t: this->player->getTerritories()){
        for(Territory *neighour: t->getNeighbours()){
            if(neighour->owner->name != this->player->name){
                toAttack.push_back(neighour);
            }
        } 
    }
    return toAttack;

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
    return toAttack;

};
vector<Territory*> BenevolentPlayerStrategy::toAttack(){
    //idk what to do here since he never attacks
    vector<Territory*> toAttack;

    return toAttack;


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
    return toAttack;

};

vector<Territory*> HumanPlayerStrategy::toDefend(){
    return this->player->getTerritories();

};
vector<Territory*> AggressivePlayerStrategy::toDefend(){
    vector<Territory*> toDefend = this->player->getTerritories();
    //Sort to make it easier to find strongest country
    //Using sort method from std::sort
    sort(toDefend.begin(), toDefend.end(), sortbyStrongest);

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