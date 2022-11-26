#include "GameEngine.h"
#include "Map.h"
#include <iostream>
#include <string>
#include <fstream>
#include <regex>
#include <vector>
#include <list>
#include <iterator>
#include <algorithm>
#include <stack>
#include <random>
#include <sstream>
using namespace std;
// implementing encapsulation
GameEngine::GameEngine()
{
}
GameEngine::GameEngine(string stateNamee)
{
    this->stateName = new string(stateNamee);
}
GameEngine::GameEngine(const GameEngine &engine)
{
    this->stateName = engine.getStateName();
}
GameEngine &GameEngine::operator=(const GameEngine &t)
{
    this->stateName = new string(*(t.stateName));
    return *this;
}

GameEngine::~GameEngine()
{
    this->stateName = NULL;
}

string *GameEngine::getStateName() const
{
    return stateName;
}
void GameEngine::setStateName(string *stateNamee)
{
    GameEngine::stateName = stateNamee;
    // Notifies observers
    Notify(this);
}

// this funtion is for ILoggable class in LoggingObserver.h
std::string GameEngine::stringToLog()
{
    return "Game Engine new state: " + *getStateName();
}

ostream &operator<<(ostream &out, const GameEngine *engine)
{
    out << "State Name is: " << engine->getStateName();
    return out;
}


void GameEngine::startupPhase(CommandProcessing *c)
{
    this->deck = new Deck();
    this->num_players = 0;
    this->deck->initial_deck();
    vector<string *> states;
    this->setStateName(new string("start"));
    states.push_back(new string("start"));
    states.push_back(new string("maploaded"));
    states.push_back(new string("mapvalidated"));
    states.push_back(new string("playersadded"));
    int i = 0;
    this->setStateName(new string(" "));
    while (i < states.size())
    {
        if (states[i]->compare("mapvalidated") == 0 || states[i]->compare("playersadded") == 0)
        {
            while (this->getStateName()->compare("play") != 0 && num_players < 6)
            {
                cout << "**Current State**: " << *this->getStateName() << endl;
                cout << "Enter 2 - 6 players, startgame when ready" << endl;
                string nextstate = *states[i];
                c->getCommand(states[i]);
                this->setStateName(states[i]);
                if (this->getStateName()->compare("ERROR") == 0)
                {
                    *states[i] = nextstate;
                    continue;
                }
                readCommandList(c);
                c->gameCommands.clear();
            }
        }
        else
        {
            cout << "**Current State**: " << *this->getStateName() << endl;
            if (this->getStateName()->compare("play") == 0)
            {
                break;
            }
            string nextstate = *states[i];
            c->getCommand(states[i]);
            this->setStateName(states[i]);

          
           if (this->getStateName()->compare("ERROR") == 0)
                {
                    *states[i] = nextstate;
                    continue;
                }
            readCommandList(c);
            c->gameCommands.clear();
        }
        i++;
    }
}
void GameEngine::readCommandList(CommandProcessing *c)
{
    for (Command co : c->gameCommands)
    {
        cout << co.theCommand << endl;
        if(co.theCommand.find("tournament") != string::npos){
            vector<string> mapFiles;
            vector<string> playerstrats;
            this->winner = "draw";
            int games;
            string winners;
            string maps;
            processString(nthSubstr(1,co.theCommand, "<"), nthSubstr(1, co.theCommand, ">"), co.theCommand, mapFiles);
            processString(nthSubstr(2, co.theCommand, "<"), nthSubstr(2, co.theCommand, ">"), co.theCommand, playerstrats);
            games = stoi(co.theCommand.substr(nthSubstr(3 ,co.theCommand, "<") + 1, nthSubstr(3, co.theCommand, ">") - 1) );
            int numturns = stoi(co.theCommand.substr(nthSubstr(4 ,co.theCommand, "<") + 1, nthSubstr(4, co.theCommand, ">") - 1));
            this->turns = numturns;
            CommandProcessing *v2 = new CommandProcessing();
            for(string map: mapFiles){
                maps += map + "\n";
                maps += "----------\n";
                for(int i = 0; i < games; i++){
                    this->deck = new Deck();
                    this->num_players = 0;
                    this->deck->initial_deck();
                    Command loadMap = Command("loadmap<" + map + ">");
                    loadMap.saveEffect("maploaded");
                    v2->gameCommands.push_back(loadMap);
                    this->setStateName(new string("maploaded"));
                    readCommandList(v2);
                    v2->gameCommands.clear();

                    Command validatemap = Command("validatemap");
                    validatemap.saveEffect("validatemap");
                    v2->gameCommands.push_back(validatemap);
                    this->setStateName(new string("mapvalidated"));
                    readCommandList(v2);
                    v2->gameCommands.clear();
                    int k = 1;
                    for(string strat: playerstrats){
                        Command addplayer = Command("addplayer<" + strat + std::to_string(k) + ">");
                        addplayer.saveEffect("playersadded");
                        v2->gameCommands.push_back(addplayer);
                        this->setStateName(new string("playersadded"));
                        readCommandList(v2);
                        v2->gameCommands.clear();
                        k++;
                    }

                    Command start = Command("gamestart");
                    start.saveEffect("assignreinforcement");
                    this->setStateName(new string("assignreinforcement"));
                    v2->gameCommands.push_back(start);
                    readCommandList(v2);
                    v2->gameCommands.clear();
                   maps += "Game: "+ std::to_string(i + 1) + "-->" + this->winner + ", ";
                   Reset();
                }
                maps += "\n"; 
    
                
            }
            cout << maps << winners << endl;
           exit(0);
        }
        if ((co.theCommand.find("loadmap") != std::string::npos) && ((*this->getStateName()).compare("maploaded") == 0))
        {   
            cout <<"her33" << endl;
            string file = co.theCommand;
            string mp = file.substr(nthSubstr(1, file, "<"), nthSubstr(1, file, ">"));
            mp.erase(remove(mp.begin(), mp.end(), '<'), mp.end());
            mp.erase(remove(mp.begin(), mp.end(), '>'), mp.end());
            MapLoader *loadmap = new MapLoader();
            mp = ".mapFiles/" + mp;
            this->map = new Map();
            this->map = loadmap->readMapFile(mp);
        }
        else if ((co.theCommand.find("validatemap") != std::string::npos) && (this->getStateName()->compare("mapvalidated") == 0))
        {
            this->map->validate();
        }
        else if ((co.theCommand.find("addplayer") != std::string::npos) && (this->getStateName()->compare("playersadded") == 0))
        {

            string player_name = co.theCommand;

            player_name = player_name.substr(nthSubstr(1, player_name, "<"), nthSubstr(1, player_name, ">"));
            player_name.erase(remove(player_name.begin(), player_name.end(), '<'), player_name.end());
            player_name.erase(remove(player_name.begin(), player_name.end(), '>'), player_name.end());
            if(player_name.find("Aggressive") != std::string::npos){
                Player* p = new Player(player_name, this);
                p->ps = new AggressivePlayerStrategy(p);
                this->players.push_back(p);
                cout << "\nAggressive player added\n" << endl;
            }else if(player_name.find("Cheater") != std::string::npos){
                Player* p = new Player(player_name, this);
                p->ps = new CheaterPlayerStrategy(p);
                this->players.push_back(p);
                cout << "\nCheater player added\n" << endl;
            }else if(player_name.find("Benevolent") != std::string::npos){
                Player* p = new Player(player_name, this);
                p->ps = new BenevolentPlayerStrategy(p);
                this->players.push_back(p);
                cout << "\nBenevolent player added\n" << endl;
            }else if(player_name.find("Neutral") != std::string::npos){
                Player* p = new Player(player_name, this);
                p->ps = new NeutralPlayerStrategy(p);
                this->players.push_back(p);
                cout << "\nNeutral player added\n" << endl;
            }else{
                Player *p = new Player(player_name, this);
                p->ps = new HumanPlayerStrategy(p);
                cout <<"Normal Player added" << endl;
                this->players.push_back(p);
            }
            
        }
        else if ((co.theCommand.find("gamestart") != std::string::npos) && (this->getStateName()->compare("assignreinforcement") == 0))
        {
            // //Randomize territories
            this->setStateName(new string("play"));
            int total_territories = this->map->getTerritories().size();
            
            int terrPerPlayer = (total_territories/this->players.size());
            for (int i = 0; i < total_territories;)
            {
                for (int j = 0; j < this->players.size(); j++)
                {
                    if (i == this->map->getTerritories().size())
                        break;
                    this->players[j]->addTerritory(this->map->getTerritories()[i]);
                    i++;
                }
            }
            
            for (int i = 0; i < this->players.size(); i++)
            {
                cout << "\nPlayer: ";
                cout << this->players[i]->name << endl;
                cout << "Assigned Territories: \n"
                     << endl;
                for (int j = 0; j < this->players[i]->getTerritories().size(); j++)
                {
                    cout << this->players[i]->getTerritories()[j]->getName() << endl;
                }
            }

            shuffle(this->players.begin(), players.end(), random_device());
            // Give 50 army units to the players
            // let each player draw 2 cards
            for (Player *p : this->players)
            {   
                            cout << "test2" << endl;

                p->reinforcement_pool = 50;
                p->getHand()->set_cards_in_hand(this->deck->draw());
                p->getHand()->set_cards_in_hand(this->deck->draw());
                

            }
            cout << "test" << endl;
            for(Player *p: this->players){
                cout << "\nPlayer " << p->name << " drew cards: " << endl;
                for(Card *c: *p->getHand()->get_hand_vector()){
                    cout << *c->get_card_type() << endl << endl;
                }
            }
            this->mainGameLoop();   	
        }
    }
}
void GameEngine::mainGameLoop()
{

    bool winner = false;
    int totalTerritories;

    do
    {
        for(Player *p: this->players){
            cout << "\nPlayer " << p->name << " owns: \n";
            for(int i = 0; i < p->getTerritories().size(); i++){
                cout << p->getTerritories()[i]->getName() << ",";
            }
        }
        for (int i = 0; i < players.size(); i++)
        {   
            // check if there is a winner to terminate loop

            if (players[i]->getTerritories().size() == 0)
            {
                cout << "\nPlayer " << players[i]->name << " has been removed from the game" << endl;
                players.erase(players.begin() + i);
                cout << players.size() << endl;
                i--;
            }
        }
      

        totalTerritories = map->getTerritories().size();

        for (Player *p : this->players)
        {   
           
            if (p->getTerritories().size() >= totalTerritories)
            {
                winner = true;
                cout << "\n------------THE WINNER IS------------\n\n"<<  endl <<"\tPlayer: " << p->name << endl <<"\n\n---------------------------\n\n";
                this->winner = p->name;
                break;
            }
            else if(this->turnCounter == this->turns){
                cout << "draw " << endl;
                break;
            }
        }
     if(!winner){
         this->turnCounter++;
        reinforcementPhase();
        
        issueOrdersPhase();
        
        executeOrdersPhase();
     }
    } while (!winner && (this->turnCounter != this->turns));
}

void GameEngine::reinforcementPhase(){
        cout << "\n----REINFORCEMENT PHASE-----\n" << endl;

    vector<Continent*> continents = this->map->getContinents();
    vector<vector<Territory*>> all_territories_of_continents;

    //init of all_territories_of_continents using the continents
    for (size_t i; i<continents.size(); i++){
        all_territories_of_continents.at(i) = continents.at(i)->continent_members;
    }

    //loop over the players to assign reinforcement units
    for(Player* p: this->players){
        int armies = 0;
        vector<int> bonuses = {};
        vector<Territory*> territories_not_collected = {};

        //checking if a players controls a continent. if true, we collect the bonus of the continents controlled
        for (int i = 0; i < all_territories_of_continents.size(); ++i) {
            vector<Territory*> continent_temp = all_territories_of_continents.at(i);
            int found = 0;

            for (int j = 0; j < continent_temp.size(); ++j) {
                Territory* territory_temp = continent_temp.at(j);
                bool territory_found_in_the_player_territories = false;

                for (int k = 0; k < p->getTerritories().size(); ++k) {
                    if (territory_temp->getName() == p->getTerritories().at(k)->getName()){
                        found++;
                        territory_found_in_the_player_territories = true;
                    }
                }
                if (territory_found_in_the_player_territories == false){//Break from looping over this continent
                    break;
                }


            }
            if (found == continent_temp.size()){
                bonuses.push_back(continents.at(i)->getBonusValue());//collecting the bonuses
                for (int j = 0; j < continent_temp.size(); ++j) {
                    territories_not_collected.push_back(continent_temp.at(j));
                }
            }
        }
        int number_of_territories_not_collected = p->getTerritories().size() - territories_not_collected.size();

        int total_bonuses = 0;

        //sum the total bonuses
        for (int i = 0; i < bonuses.size(); ++i) {
            total_bonuses = total_bonuses + bonuses.at(i);
        }

        if ((total_bonuses + floor(number_of_territories_not_collected/3))<3){
            armies = 3;
        }else{
            armies = (total_bonuses + floor(number_of_territories_not_collected/3));
        }

        p->reinforcement_pool = armies;
        cout << p->name << " reinforced with " << p->reinforcement_pool << " armies" << endl;

    }
            cout << "\n----END OF REINFORCEMENT PHASE-----\n" << endl;

}

  issue_order_types convert(const string& word){
  if(word == "OrderAdvanceType") return OrderAdvanceType;
    else if(word == "OrderDeployType") return OrderDeployType;
    else if(word == "OrderBombType") return OrderBombType;
    else if(word == "OrderBlockadeType") return OrderBlockadeType;
    else if(word == "OrderAirliftType") return OrderAirliftType;
    else /*if(word == "OrderNegotiateType")*/ return OrderNegotiateType;
}


vector<string> split(string str, string deli)
{
    vector<string> list;
    int start = 0;
    int end = str.find(deli);
    while (end != -1) {
      list.push_back(str.substr(start, end - start)); 
        start = end + deli.size();
        end = str.find(deli, start);
    }
      list.push_back(str.substr(start, end - start)); 

   return list;
}

void GameEngine::issueOrdersPhase(){
    cout << "\n----ISSUE ORDERS PHASE-----\n" << endl;
    int ordersPerTurn = this->players.size()*5;
    int current_player = 0;
    for(int i = 0; i < this->players.size(); i++){
        this->players[i]->negotiationWith.clear();
        if(this->players[i]->ps->name == "Cheater"){
            this->players[i]->ps->hasIssued = false;
        }
    }
    for(int i = 0; i < ordersPerTurn; i++){
        this->players[current_player]->issueOrder(this->deck);
        //Cheater can only issue once per turn
        if(players[current_player]->ps->name == "Cheater"){
            players[current_player]->ps->hasIssued = true;
        }
        current_player++;
        if(current_player == this->players.size()){
           
            current_player = 0;
        }
    }
    cout << "\n----END OF ISSUE ORDERS PHASE-----\n" << endl;

  
    
}
   
void GameEngine::executeOrdersPhase(){
    cout << "\n----EXEC ORDERS PHASE-----\n" << endl;
    int i = 0;

    while(i < 5){

        for(Player *p : this->players){
            int before = p->getTerritories().size();
            if(p->orederptr == p->getOrders()->ol.size()){
                continue;
         
            }else{
                if(p->getTerritories().size() == 0) continue;
                p->getOrders()->ol.at(p->orederptr)->execute();
                p->orederptr++;
            }
            int after = p->getTerritories().size();
            if(after > before) {
                if(this->deck->deck_vector.size() > 0){
                    cout << p->name << " is drawing a card from the deck " << endl;
                    p->getHand()->set_cards_in_hand(this->deck->draw());
                }
            }
        }
          i++;
    }

    cout << "\n----END OF EXEC ORDERS PHASE-----\n" << endl;
}


bool search(vector<Player *> player, string command)
{
    for (int i = 0; i < player.size(); i++)
    {
        if (player[i]->name.compare(command) == 0)
        {
            return true;
        }
    }
    return false;
}
void GameEngine::processString(int del1, int del2,  string command, vector<string> &type){
            cout << command << endl;
            string process = command.substr(del1 + 1 , del2 - del1 - 1);
            stringstream ss(process);
            while( ss.good() ){
                string substr;
                getline( ss, substr, ',' );
                type.push_back(substr);
            }
}
void GameEngine::Reset(){
    delete this->map;
    for(Player *p: this->players){
        delete p;
    }
    this->winner = "draw";
    this->players.clear();
    this->turnCounter = 0;

}