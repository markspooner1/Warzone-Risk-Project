#include "LoggingObserver.h"
#include "Orders.h"
#include "GameEngine.h"
#include "CommandProcessing.h"

using namespace std;


void testLoggingObserver(){


    LogObserver* logObs = new LogObserver();

    //we need to add log observer to subject's observer-list
    Order* order = new Order(0, "First Order");
    Subject* subject1 = order;
    subject1->addObserver(logObs);


    //test for order issue and order execute
    OrdersList* ordersList = new OrdersList();
    ordersList->addOrder(order);
    order->execute();
    Player *p = new Player("a");

    Territory *t = new Territory("Some Place", "Some Place");
    t->owner = p;
    OrderBomb* orderBomb = new OrderBomb(p, 1, "OrderBomb", t);

    ordersList->addOrder(orderBomb);

    orderBomb->execute();

    Player *p1 = new Player("b");

    Territory *t2 = new Territory("Some Place2", "Some Place3");
    t2->owner = p1;
    OrderBomb* orderBomb2 = new OrderBomb(p1, 1, "OrderBomb", t2);
    ordersList->addOrder(orderBomb2);
    orderBomb2->execute();

    //test for game state change
    string *str1 = new string("start"), *str2 = new string("start");
  
    GameEngine* gameEngine = new GameEngine();
    gameEngine->setStateName(str1);
    gameEngine->setStateName(str2);

    //test for save command
    CommandProcessing* commandProcessing = new CommandProcessing();
    commandProcessing->saveCommand("some command", "some effect", str1);


    //test for save effect
    Command* command = new Command();
    command->saveEffect("another effect");

  
}