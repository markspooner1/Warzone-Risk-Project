#include <iostream>
#include <cctype>
#include <cstdlib>
using namespace std;
#include "OrdersList.h"

Order::Order(int ID,string name){
	this->OrderID = new int(ID);
	this->name = new string(name);
}

Order::Order() {
	this->OrderID = new int(0);
	this->name = new string("No name");
}

Order::Order(const Order &copyed) {
	this->OrderID = new int(*(copyed.OrderID));
	this->name = new string(*(copyed.name));
}

Order& Order::operator =(const Order& o) {
	this->OrderID = new int(*(o.OrderID));
	this->name = new string(*(o.name));
	return *this;
}


int Order::getOrderID() {
	return *OrderID;
}

void Order::setOrderID(int ID) {
	this->OrderID = new int(ID);
}

string Order::getOrderName() {
	return *name;
}

void Order::setOrderName(string nom){
	this->name = new string(nom);
}

void Order::execute() {
	if (validate()) {
		cout << "Order has been executed";
	}
}

bool Order::validate() {
	cout << "Order validity check...\n";
	return true;
}

OrderAdvance::OrderAdvance(int ID, int numofUnits, string name, string source, string target): Order(ID,name) {
	this->numberOfunits = new int(numofUnits);
	this->SourceTerritory = new string(source);
	this->TargetTerritory = new string(target);
}

OrderAdvance::OrderAdvance() : Order() {
	this->numberOfunits = new int(0);
	this->SourceTerritory = new string("default");
	this->TargetTerritory = new string("default");
}
OrderAdvance& OrderAdvance::operator=(const OrderAdvance& dep){
	Order::operator= (dep);
	this->numberOfunits = new int(*(dep.numberOfunits));
	this->SourceTerritory = new string(*(dep.SourceTerritory));
	this->TargetTerritory = new string(*(dep.TargetTerritory));
	return *this;
}

OrderAdvance::OrderAdvance(const OrderAdvance& dep) : Order(dep) {
	this->numberOfunits = new int(*(dep.numberOfunits));
	this->SourceTerritory = new string(*(dep.SourceTerritory));
	this->TargetTerritory = new string(*(dep.TargetTerritory));
}


int OrderAdvance::getUnits() {
	return *numberOfunits;
}

string OrderAdvance::getTarget() {
	return *TargetTerritory;
}
string OrderAdvance::getSource() {
	return *SourceTerritory;
}

void OrderAdvance::advance() {
	cout << "ORDER NUMBER " << getOrderID() << ": BEGIN OPERATION " << getOrderName() << endl;
	cout << "Arrival of " << getUnits() << " units to " << getTarget() << " coming from " << getSource() << endl;
}
void OrderAdvance::execute() {
	if (validate()) {
		cout << "Order has been executed\n";
	}
	else
		cout << "Order has not been executed" << endl;
}

bool OrderAdvance::validate() {
	cout << "Order validity check...\n";
	if (getSource() != getTarget()) {
		return true;
	}
	else {
		cout << "Order is invalid XXX Abort execution!" << endl;
		return false;
	}
	
}
//////////////////////////////////
OrderDeploy::OrderDeploy(int ID, int numofUnits, string name, string target) : Order(ID, name) {
	this->numberOfunits = new int(numofUnits);
	this->TargetTerritory = new string(target);
}

OrderDeploy::OrderDeploy() : Order() {
	this->numberOfunits = new int(0);
	this->TargetTerritory = new string("default");
}
OrderDeploy& OrderDeploy::operator=(const OrderDeploy& dep) {
	Order::operator= (dep);
	this->numberOfunits = new int(*(dep.numberOfunits));
	this->TargetTerritory = new string(*(dep.TargetTerritory));
	return *this;
}

OrderDeploy::OrderDeploy(const OrderDeploy& dep) : Order(dep) {
	this->numberOfunits = new int(*(dep.numberOfunits));
	this->TargetTerritory = new string(*(dep.TargetTerritory));
}


int OrderDeploy::getUnits() {
	return *numberOfunits;
}

string OrderDeploy::getTarget() {
	return *TargetTerritory;
}


void OrderDeploy::deploy() {
	cout << "ORDER NUMBER " << getOrderID() << ": BEGIN OPERATION " << getOrderName() << endl;
	cout << "Deployment of " << getUnits() << " units to " << getTarget() << endl;
}
void OrderDeploy::execute() {
	if (validate()) {
		cout << "Order has been executed\n";
	}
	else
		cout << "Order has not been executed" << endl;
}

bool OrderDeploy::validate() {
	cout << "Order validity check...\n";
	if (true) {
		return true;
	}
	else {
		cout << "Order is invalid XXX Abort execution!" << endl;
		return false;
	}

}
//////////////////////////////////
OrderBomb::OrderBomb(int ID, string name, string target) : Order(ID, name) {
	this->TargetTerritory = new string(target);
}

OrderBomb::OrderBomb() : Order() {
	this->TargetTerritory = new string("default");
}
OrderBomb& OrderBomb::operator=(const OrderBomb& dep) {
	Order::operator= (dep);
	this->TargetTerritory = new string(*(dep.TargetTerritory));
	return *this;
}

OrderBomb::OrderBomb(const OrderBomb& dep) : Order(dep) {
	this->TargetTerritory = new string(*(dep.TargetTerritory));
}

string OrderBomb::getTarget() {
	return *TargetTerritory;
}


void OrderBomb::bomb() {
	cout << "ORDER NUMBER " << getOrderID() << ": BEGIN OPERATION " << getOrderName() << endl;
	cout << getTarget() <<" has been bombed successfully!! Half of the units were wiped out!"<< endl;
}
void OrderBomb::execute() {
	if (validate()) {
		bomb();
		cout << "Order has been executed\n";

	}
	else
		cout << "Order has not been executed" << endl;
}

bool OrderBomb::validate() {
	cout << "Order validity check...\n";
	if (true) {
		cout << "Order is valid\n";
		return true;
	}
	else {
		cout << "Order is invalid XXX Abort execution!" << endl;
		return false;
	}

}
//////////////////////////////////
OrderBlockade::OrderBlockade(int ID, string name, string target) : Order(ID, name) {
	this->TargetTerritory = new string(target);
}

OrderBlockade::OrderBlockade() : Order() {
	this->TargetTerritory = new string("default");
}
OrderBlockade& OrderBlockade::operator=(const OrderBlockade& dep) {
	Order::operator= (dep);
	this->TargetTerritory = new string(*(dep.TargetTerritory));
	return *this;
}

OrderBlockade::OrderBlockade(const OrderBlockade& dep) : Order(dep) {
	this->TargetTerritory = new string(*(dep.TargetTerritory));
}

string OrderBlockade::getTarget() {
	return *TargetTerritory;
}


void OrderBlockade::blockade() {
	cout << "ORDER NUMBER " << getOrderID() << ": BEGIN OPERATION " << getOrderName() << endl;
	cout <<"The number of units on the territory"<< getTarget() << " has been tripled! It is now a neutral territory." << endl;
}
void OrderBlockade::execute() {
	if (validate()) {
		blockade();
		cout << "Order has been executed\n";

	}
	else
		cout << "Order has not been executed" << endl;
}

bool OrderBlockade::validate() {
	cout << "Order validity check...\n";
	if (true) {
		cout << "Order is valid\n";
		return true;
	}
	else {
		cout << "Order is invalid XXX Abort execution!" << endl;
		return false;
	}

}
/////////////////////////////////
OrderAirlift::OrderAirlift(int ID, int numofUnits, string name, string source, string target) : Order(ID, name) {
	this->numberOfunits = new int(numofUnits);
	this->SourceTerritory = new string(source);
	this->TargetTerritory = new string(target);
}

OrderAirlift::OrderAirlift() : Order() {
	this->numberOfunits = new int(0);
	this->SourceTerritory = new string("default");
	this->TargetTerritory = new string("default");
}
OrderAirlift& OrderAirlift::operator=(const OrderAirlift& dep) {
	Order::operator= (dep);
	this->numberOfunits = new int(*(dep.numberOfunits));
	this->SourceTerritory = new string(*(dep.SourceTerritory));
	this->TargetTerritory = new string(*(dep.TargetTerritory));
	return *this;
}

OrderAirlift::OrderAirlift(const OrderAirlift& dep) : Order(dep) {
	this->numberOfunits = new int(*(dep.numberOfunits));
	this->SourceTerritory = new string(*(dep.SourceTerritory));
	this->TargetTerritory = new string(*(dep.TargetTerritory));
}


int OrderAirlift::getUnits() {
	return *numberOfunits;
}

string OrderAirlift::getTarget() {
	return *TargetTerritory;
}
string OrderAirlift::getSource() {
	return *SourceTerritory;
}

void OrderAirlift::airlift() {
	cout << "ORDER NUMBER " << getOrderID() << ": BEGIN OPERATION " << getOrderName() << endl;
	cout << "Landing of  " << getUnits() << " units in " << getTarget() << " coming from " << getSource() << endl;
}
void OrderAirlift::execute() {
	if (validate()) {
		cout << "Order has been executed\n";
		airlift();
	}
	else
		cout << "Order has not been executed" << endl;
}

bool OrderAirlift::validate() {
	cout << "Order validity check...\n";
	if (getSource() != getTarget()) {
		return true;
	}
	else {
		cout << "Order is invalid XXX Abort execution!" << endl;
		return false;
	}

}
/////////////////////////////////
OrderNegotiate::OrderNegotiate(int ID, string name, string source, string target) : Order(ID, name) {
	this->SourceTerritory = new string(source);
	this->TargetTerritory = new string(target);
}

OrderNegotiate::OrderNegotiate() : Order() {
	this->SourceTerritory = new string("default");
	this->TargetTerritory = new string("default");
}
OrderNegotiate& OrderNegotiate::operator=(const OrderNegotiate& dep) {
	Order::operator= (dep);
	this->SourceTerritory = new string(*(dep.SourceTerritory));
	this->TargetTerritory = new string(*(dep.TargetTerritory));
	return *this;
}

OrderNegotiate::OrderNegotiate(const OrderNegotiate& dep) : Order(dep) {
	this->SourceTerritory = new string(*(dep.SourceTerritory));
	this->TargetTerritory = new string(*(dep.TargetTerritory));
}

string OrderNegotiate::getTarget() {
	return *TargetTerritory;
}
string OrderNegotiate::getSource() {
	return *SourceTerritory;
}

void OrderNegotiate::negotiate() {
	cout << "ORDER NUMBER " << getOrderID() << ": BEGIN OPERATION " << getOrderName() << endl;
	cout << getTarget() << " and  " << getSource() <<" can no longer attack each other"<< endl;
}
void OrderNegotiate::execute() {
	if (validate()) {
		cout << "Order has been executed\n";
		negotiate();
	}
	else
		cout << "Order has not been executed" << endl;
}

bool OrderNegotiate::validate() {
	cout << "Order validity check...\n";
	if (getSource() != getTarget()) {
		return true;
	}
	else {
		cout << "Order is invalid XXX Abort execution!" << endl;
		return false;
	}

}
/////////////////////////////////
//std::ostream& operator<<(std::ostream& strm, const Order& a) {
	//return strm << "Order(" << a.getOrderID() << ")";
//}




int main() {
	cout << "Hello World\n";
	Order o1(int(46), "First Order");
	Order treas = o1;
	Order o2;
	o1.execute();
	cout << "The OrderID is " << o1.getOrderID() << "\n";
	cout << "The OrderID is " << treas.getOrderID() << "\n";
	cout << "The Order name is "<< o1.getOrderName() << "\n";
	cout << "The Order name is " << treas.getOrderName() << "\n";
	treas.setOrderID(9);
	cout << "The OrderID is " << o1.getOrderID() << "\n";
	cout << "The OrderID is " << treas.getOrderID() << "\n";
	//cout << "The OrderID is " << o1.getOrderID() << "\n";
	cout << "The OrderID is " << o2.getOrderID() << endl;
	OrderAdvance od1(2121, 667, "First arrival", "Quebec", "Quebec");
	cout << "OD1 Info: \n" << od1.getOrderName() << " From " << od1.getSource() << " to " << od1.getTarget() << "\n";
	cout << od1.getUnits() << " UNITS INCOMING" << endl;
	OrderAdvance od2 = od1;
	cout << "OD2 Info: \n" << od2.getOrderName() << " From " << od2.getSource() << " to " << od2.getTarget() << "\n";
	cout << od2.getUnits() << " UNITS INCOMING" << endl;
	OrderAdvance od3= OrderAdvance();
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