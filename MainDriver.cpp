#include "Map.h"
#include "GameEngine.h"
#include "Player.h"
#include "Cards.h"
#include "Orders.h"
int main(){
    testLoadMaps();
    cout<< "\nEnd of TestLoadMaps()\n" << endl;
    cout<< "------------------------" << endl;
    testPlayers();
     cout<< "\nEnd of TestPlayers()\n" << endl;
    cout<< "------------------------" << endl;
    testCards();
     cout<< "\nEnd of TestCards()\n" << endl;
    cout<< "------------------------" << endl;
    testOrdersLists();
     cout<< "\nEnd of TestOrderLists()\n" << endl;
    cout<< "------------------------" << endl;
    testGameStates();
     cout<< "\nEnd of TestGameStates()\n" << endl;
    cout<< "------------------------" << endl;

}
