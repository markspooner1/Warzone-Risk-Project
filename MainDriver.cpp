#include "Map.h"
#include "GameEngine.h"
#include "Player.h"
#include "Cards.h"
#include "Orders.h"
#include "CommandProcessing.h"
#include "LoggingObserver.h"
int main(){
    string input;
    cout << "1 for testStartupPhase\n2 for testMainGameLoop()\n3 for testLoggingObserver()\n4 for testCommandProcessor\n5 for testOrderExecution()" <<endl;
    cin >> input;
    if(input == "1"){
        testStartupPhase();
    }else if(input == "2"){
        testMainGameLoop();
    }else if(input == "3"){
        testLoggingObserver();
    }else if(input == "4"){
        testCommandProcessor();
    }else if(input == "5"){
        testOrdersExecution();
    }

}
