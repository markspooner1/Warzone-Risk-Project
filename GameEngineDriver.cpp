#include "GameEngine.h"
#include <iostream>
#include "LoggingObserver.h"
using namespace std;

// void testGameStates()
// {

//     // starts the startup phase then leads to the play phase once user enters gamestart

//     GameEngine startup;
//     startup.startupPhase();
// }

void testStartupPhase(){
    LogObserver *o = new LogObserver();
    CommandProcessing *c = new CommandProcessing();
    GameEngine *g = new GameEngine();
    g->addObserver(o);
    g->startupPhase(c);
}