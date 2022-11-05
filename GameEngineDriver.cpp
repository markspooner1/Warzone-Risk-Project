#include "GameEngine.h"
#include <iostream>
using namespace std;

// void testGameStates()
// {

//     // starts the startup phase then leads to the play phase once user enters gamestart

//     GameEngine startup;
//     startup.startupPhase();
// }

void testStartupPhase(){
    CommandProcessing *c = new CommandProcessing();
    GameEngine *g = new GameEngine();
    g->startupPhase(c);
}