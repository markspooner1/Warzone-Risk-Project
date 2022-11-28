//
// Created by Brahim Hamid oudjana on 2022-11-10.
//
#include "Orders.h"
#include "Map.h"
#include "Cards.h"
#include "Player.h"
#include <vector>
#include "GameEngine.h"



void testMainGameLoop(){
    LogObserver *o = new LogObserver();
    CommandProcessing *c = new CommandProcessing();
    GameEngine *g = new GameEngine();
    g->addObserver(o);
    g->startupPhase(c);
    g->mainGameLoop();
}


