#include <iostream>
#include <cctype>
#include <cstdlib>
#include "Orders.h"
#include "GameEngine.h"

using namespace std;
void testOrdersLists() {
	CommandProcessing *c = new CommandProcessing();
    GameEngine *g = new GameEngine();
    g->startupPhase(c);
	g->mainGameLoop();
}
