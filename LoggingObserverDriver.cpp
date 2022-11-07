#include "LoggingObserver.h"
#include "Orders.h"

using namespace std;


void testLoggingObserver(){
    LogObserver* logObs = new LogObserver();

    //test for order issue and order execute
    Order* order = new Order(0, "First Order");
    Subject* subject1 = order;
    subject1->addObserver(logObs);





    OrdersList* ordersList = new OrdersList();
    ordersList->addOrder(*order);
    order->execute();

    OrderBomb* orderBomb = new OrderBomb(1, "OrderBomb", "Some Place");
    ordersList->addOrder(*orderBomb);
    orderBomb->execute();
    

    delete logObs;
    delete ordersList;
    delete orderBomb;
    delete order;
}