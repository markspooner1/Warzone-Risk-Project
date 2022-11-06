#include "Orders.h"

using namespace std;

void testLoggingObserver(){


    Subject* subject = new Subject();
    subject->addObserver(new LogObserver());


    //test for order issue and order execute
    Order* order = new Order(0, "First Order");
    OrdersList* ordersList = new OrdersList();
    ordersList->addOrder(order);
    order->execute();




}