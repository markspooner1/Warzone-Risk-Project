#include "GameEngine.h"
//tournament -M <3D.map,Jackhammer.map,Moon.map,Vernon.map> -P <Aggressive,Neutral,Aggressive,Aggressive> -G <4> -D <50>
//tournament -M <LP.map,Taifa.map,pacman.map,Vernon.map,Hydroplane.map> -P <Aggressive,Cheater,Benevolent,Aggressive> -G <5> -D <50>
//tournament -M <Maryland.map,pacman.map,Vernon.map,Hydroplane.map> -P <Neutral,Aggressive,Benevolent,Aggressive,Benevolent,Aggressive> -G <4> -D <50>
void testTournament(){
    LogObserver *o = new LogObserver();
    CommandProcessing *c = new CommandProcessing();
    GameEngine *g = new GameEngine();
    g->addObserver(o);
    g->startupPhase(c);
}