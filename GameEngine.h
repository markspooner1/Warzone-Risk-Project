//
// Created by Warda Salem on 2022-09-22.
//

#ifndef COMP345_GAMEENGINE_H
#define COMP345_GAMEENGINE_H

#endif //COMP345_GAMEENGINE_H
#ifndef GAMEENGINE_H
#define GAMEENGINE_H


#include <iostream>
#include <vector>
#include "CommandProcessing.h"
#include "Player.h"
#include "LoggingObserver.h"
#include "Map.h"
class Map;
// istream and ostream are defined in the std namespace in the iostream library
using namespace std;

class GameEngine: public Subject, public ILoggable
{
  private: string* stateName;
  public:

  //default constructor
     GameEngine();
     //destructor
    ~GameEngine();
    //overloaded constructor
     GameEngine(string stateName);
     // copy constructor
     GameEngine(const GameEngine& engine);
     // assignment operator
     GameEngine& operator=(const GameEngine& t);
     // insertion operator
     friend ostream& operator<<(ostream& out, GameEngine engine);
     // getters
     string* getStateName() const;
     //setters
     void setStateName(string* stateName);
     void startupPhase(CommandProcessing* c);
     // A2 Part 3
     void mainGameLoop();
    void reinforcementPhase();
    void issueOrdersPhase();
    void executeOrdersPhase();
     void readCommandList(CommandProcessing* c);
     vector<Player*> players;
     Map *map;
     Deck* deck;
     int turns;
     string winner;
     int turnCounter;
     int num_players;
     void processString(int del1, int del2,  string command, vector<string> &type);
    //this funtion is for ILoggable class in LoggingObserver.h
    std::string stringToLog() override;
    void Reset();

};

class Startup

{
public:
    void loadmap();
    void validateMap();
    void addPlayer();

};

class Play
{
public:
    void assignReinforcement();
    void issueOrders();
    void executeorders();
    void endexecuteorders();
    void win();
};

class Subs
{
public:
    void printSubs(string str);

};

void testGameStates();
#endif


bool search(vector<Player*> player, string command);
void testStartupPhase();
void testMainGameLoop();
void testTournament();