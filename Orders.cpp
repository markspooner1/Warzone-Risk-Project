#include <iostream>
#include <cctype>
#include <cstdlib>
using namespace std;
#include "Orders.h"
vector<Order>::iterator;

Order::Order(int ID, string name) {
	this->OrderID = new int(ID);
	this->name = new string(name);
}

Order::Order() {
	this->OrderID = new int(0);
	this->name = new string("No name");
}

Order::Order(const Order& copyed) {
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

void Order::setOrderName(string nom) {
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
ostream& operator<<(ostream& os, const Order& ordre)
{
	os << *ordre.name << '/' << *ordre.OrderID << endl;
	return os;
}
//////////////////////////////////////////
OrderAdvance::OrderAdvance(int ID, int numofUnits, string name, string source, string target) : Order(ID, name) {
	this->numberOfunits = new int(numofUnits);
	this->SourceTerritory = new string(source);
	this->TargetTerritory = new string(target);
}

OrderAdvance::OrderAdvance() : Order() {
	this->numberOfunits = new int(0);
	this->SourceTerritory = new string("default");
	this->TargetTerritory = new string("default");
}
OrderAdvance& OrderAdvance::operator=(const OrderAdvance& dep) {
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

void OrderAdvance::execute() {
	if (validate()) {
		cout << "Advance Order has been executed\n";
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

ostream& operator<<(ostream& os, const OrderAdvance& ordre)
{
	os << "Arrival of " << *ordre.numberOfunits << " units to " << *ordre.TargetTerritory << " coming from " << *ordre.SourceTerritory << endl;
	return os;
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

void OrderDeploy::execute() {
	if (validate()) {
		cout << "Deploy Order has been executed\n";
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

ostream& operator<<(ostream& os, const OrderDeploy& ordre)
{
	os  << "Deployment of " << *ordre.TargetTerritory << " units to " << *ordre.numberOfunits << endl;
	return os;
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

void OrderBomb::execute() {
	if (validate()) {
		cout << "Bomb order has been executed\n";

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

ostream& operator<<(ostream& os, const OrderBomb& ordre)
{
	os << *ordre.TargetTerritory << " has been bombed successfully!! Half of the units were wiped out!" << endl;
	return os;
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



void OrderBlockade::execute() {
	if (validate()) {
		cout << "Blockade order has been executed\n";

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

ostream& operator<<(ostream& os, const OrderBlockade& ordre)
{
	os << "The number of units on the territory" << *ordre.TargetTerritory << " has been tripled! It is now a neutral territory." << endl;
	return os;
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

void OrderAirlift::execute() {
	if (validate()) {
		cout << "Airlift order has been executed\n";
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

ostream& operator<<(ostream& os, const OrderAirlift& ordre)
{
	os << "Landing of  " << *ordre.numberOfunits << " units in " << *ordre.TargetTerritory << " coming from " << *ordre.SourceTerritory << endl;
	return os;
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

void OrderNegotiate::execute() {
	if (validate()) {
		cout << "Negotiation Order has been executed\n";
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

ostream& operator<<(ostream& os, const OrderNegotiate& ordre)
{
	os << *ordre.TargetTerritory << " and  " << *ordre.SourceTerritory << " can no longer attack each other" << endl;
	return os;
}

/////////////////////////////////
OrdersList::OrdersList() {
	ol;
}

OrdersList::OrdersList(const OrdersList& cop) {
	this->ol = vector<Order*>((cop.ol).size());
	for (int i = 0; i < (cop.ol).size(); i++)
		ol[i] = new Order(*(cop.ol)[i]);    // if HeapItem supports copy construction
}

OrdersList& OrdersList::operator =(const OrdersList& o) {
	this->ol = vector<Order*>((o.ol).size());
	for (int i = 0; i < (o.ol).size(); i++)
		ol[i] = new Order(*(o.ol)[i]);
	return *this;
}

void OrdersList::move() {
	int id;
	cout << "What is the ID of the Order to be moved?: ";
	cin >> id;
	int index = 0;
	std::vector<Order*>::iterator it;
	std::vector<Order*>::iterator ot=ol.begin();
	for (it = ol.begin(); it != ol.end(); ++it) {
		if ((*it)->getOrderID() == id) {
			ol.push_back((*it));
			ot = ol.begin() + index;
			ol.erase(ot);
			break;
		}
		index++;
	}
	
}

void OrdersList::remove() {
	int index = 0;
	int id;
	cout << "What is the ID of the Order to be deleted?: ";
	cin >> id;
	std::vector<Order*>::iterator it;
	for (it = ol.begin(); it != ol.end(); ++it) {
		if ((*it)->getOrderID()==id) {
			ol.erase(it);
			break;
		}
	}
}
