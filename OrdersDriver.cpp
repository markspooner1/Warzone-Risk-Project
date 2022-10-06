#include <iostream>
#include <cctype>
#include <cstdlib>
#include "Orders.h"
using namespace std;
std::vector<Order>::iterator;

int main() {
	cout << "Hello World\n";
	Order o1(int(46), "First Order");
	cout << o1;
	Order treas = o1;
	Order o2;
	OrdersList ol3;
	ol3.addOrder(o1);
	ol3.addOrder(treas);
	ol3.show();
	OrderAdvance od1(2121, 667, "First arrival", "Quebec", "Ontario");
	ol3.addOrder(od1);
	ol3.show();
	cout << endl;
	ol3.advance(2121);
	cout << "END OF ADVANCE TRY\n";
	o1.execute();
	cout << "The OrderID is " << o1.getOrderID() << "\n";
	cout << "The OrderID is " << treas.getOrderID() << "\n";
	cout << "The Order name is " << o1.getOrderName() << "\n";
	cout << "The Order name is " << treas.getOrderName() << "\n";
	treas.setOrderID(9);
	cout << "The OrderID is " << o1.getOrderID() << "\n";
	cout << "The OrderID is " << treas.getOrderID() << "\n";
	//cout << "The OrderID is " << o1.getOrderID() << "\n";
	cout << "The OrderID is " << o2.getOrderID() << endl;
	cout << "OD1 Info: \n" << od1.getOrderName() << " From " << od1.getSource() << " to " << od1.getTarget() << "\n";
	cout << od1.getUnits() << " UNITS INCOMING" << endl;
	OrderAdvance od2 = od1;
	cout << "OD2 Info: \n" << od2.getOrderName() << " From " << od2.getSource() << " to " << od2.getTarget() << "\n";
	cout << od2.getUnits() << " UNITS INCOMING" << endl;
	OrderAdvance od3 = OrderAdvance();
	cout << "OD3 Info: \n" << od3.getOrderName() << " From " << od3.getSource() << " to " << od3.getTarget() << "\n";
	cout << od3.getUnits() << " UNITS INCOMING" << endl;
	od3.advance();
	od1.execute();
	//Test for Deploy;
	OrderDeploy deploy1(2222, 667, "GO", "TRANSYLVANIE");
	deploy1.execute();
	deploy1.deploy();
	OrderDeploy dep2 = deploy1;
	dep2.execute();
	dep2.deploy();
	//Test for bomb
	OrderBomb ob1(6036, "EXPLOSION", "Area 1");
	ob1.execute();
	//Test for blockade
	OrderBlockade block1(67034, "BLOCK", "Territory 2");
	OrderBlockade block2 = OrderBlockade();
	OrderBlockade block3 = OrderBlockade(block1);
	block1.execute();
	block2.execute();
	block3.execute();
	//Test for airlift
	OrderAirlift oair(564, 1000000, "Dive", "Home", "ENDZONE");
	oair.execute();
	//Test for negotiate
	OrderNegotiate nego1(111, "STOP", "France", "USA");
	nego1.execute();
	return 0;
}
