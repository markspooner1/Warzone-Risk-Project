#include <iostream>
#include <cctype>
#include <cstdlib>
#include "Orders.h"
using namespace std;
void testOrdersLists() {
	Order* order1 = new Order(8987, "Order Number 1");
	OrderAdvance* oAdvance1 = new OrderAdvance(2121, 667, "First arrival", "Quebec", "Ontario");
	OrderAdvance* oAdvance2 = new OrderAdvance(*oAdvance1);
	OrderAdvance* oAdvance3 = oAdvance1;
	OrderAdvance* oAdvance4 = new OrderAdvance();
	cout << *oAdvance1 << "\n" << *oAdvance2 << "\n" << *oAdvance3 << "\n" << *oAdvance4 << endl; //Printing the info of the deep-copies and the "empty" OrderAdvance objects
	OrderDeploy* oDeploy1 = new OrderDeploy(2222, 667, "GO", "TRANSYLVANIE");
	OrderAirlift* oAirlift = new OrderAirlift(1234, 3000, "FLIGHT", "America", "Europe");
	OrderBomb* oBomb = new OrderBomb(6036, "EXPLOSION", "Area 1");
	OrderBlockade* oBlock = new OrderBlockade(67034, "BLOCK", "Territory 2");
	OrderNegotiate* nego1 = new OrderNegotiate(111, "STOP", "France", "USA");
	(*oAdvance2).execute();
	OrdersList olist;
	(olist.ol).push_back(oAdvance1);
	(olist.ol).push_back(oBlock);
	(olist.ol).push_back(oAirlift);
	OrdersList olist2 = olist;
	for (auto it = (olist.ol).begin(); it != (olist.ol).end(); ++it)
		cout << ' ' << *(*it);
	cout << "/////////////////////////\n";
	for (auto it = (olist2.ol).begin(); it != (olist2.ol).end(); ++it)
		cout << ' ' << *(*it);
	olist.move();
	for (auto it = (olist.ol).begin(); it != (olist.ol).end(); ++it)
		cout << ' ' << *(*it);
	cout << "/////////////////////////\n";
	for (auto it = (olist2.ol).begin(); it != (olist2.ol).end(); ++it)
		cout << ' ' << *(*it);
	cout << "--------------------------\n";
	olist.remove();
	for (auto it = (olist.ol).begin(); it != (olist.ol).end(); ++it)
		cout << ' ' << *(*it);
	cout << "/////////////////////////\n";
	for (auto it = (olist2.ol).begin(); it != (olist2.ol).end(); ++it)
		cout << ' ' << *(*it);
	cout << "--------------------------\n";
	for (auto it = (olist.ol).begin(); it != (olist.ol).end(); ++it)
		(*it)->execute();
}
