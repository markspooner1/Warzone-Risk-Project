#include <iostream>
#include <cctype>
#include <cstdlib>
using namespace std;
#include "Orders.h"

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
        Notify(this);
		cout << "Order has been executed";
	}
}
std::string Order::stringToLog(){
    return "Command Executed: " + getOrderName();
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
OrderAdvance::OrderAdvance(Player* p, int ID, int numofUnits, string name, string source, string target) : Order(ID, name) {
	this->orderOwner = p;
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
	Territory *source = this->orderOwner->getTerritoryFromName(this->getSource());
	Territory *target;
	for(int i = 0; i < source->getNeighbours().size(); i++){
			if(this->getTarget() == source->getNeighbours()[i]->getName()){
				target = source->getNeighbours()[i];
			}
	}
	if (validate()) {
		if(this->orderOwner->ownsTerritory(this->getTarget())){
			source->army_units -= this->getUnits();
			target->army_units += this->getUnits();
			cout << "Advance order executeed player has moved army units from: " << source->getName() << " to " << target->getName() << endl;
		}else{
			cout << "---Player " << this->orderOwner->name << "---- has issued an advance order on: " << target->getName() << endl;
					cout << "\n";

			int randNumber;
			int attacker = *source->army_units;
			int defender = *target->army_units;
			for(int i = 0;;i++){
				randNumber = rand() % 10 + 1;
				if(randNumber <= 6){
					attacker--;
				}
				else if(randNumber <= 7){
					defender--;
				}
				if(attacker <= 0){
					cout << this->orderOwner->name << " has lost the battle to " << target->getName() << endl;
					cout << "Moving " << defender << " army units to " << source->getName() << endl;
					*source->army_units += defender;
					this->orderOwner->removeTerritory(source);
					target->owner->addTerritory(source);
					break;
					
				}if(defender <= 0){
					cout << this->orderOwner->name << " has won the battle against " << target->getName() << endl;
					cout << "Moving " << attacker << " army units to " << target->getName() << endl;
							cout << "\n";

					*target->army_units += attacker;
					this->orderOwner->removeTerritory(source);
					target->owner->addTerritory(source);
					break;
				}
			}

		}

        Notify(this);
	}
}

bool OrderAdvance::validate() {
	Player *p = this->orderOwner;

	bool owns = false;
	if(p->ownsTerritory(this->getSource())){
		owns = true;
	}else{
		cout << "Invalid order: " << p->name << " doesnt own " << this->getSource() << endl;
				cout << "\n";

	}
	if(!owns) return false;
 	Territory *source = p->getTerritoryFromName(this->getSource());
	bool isAdj = false;
	

	for(int i = 0; i < source->getNeighbours().size(); i++){
			if(this->getTarget() == source->getNeighbours()[i]->getName()){
				isAdj = true;
			}
	}
	if(!isAdj){
		cout << "Invalid Order: " << this->getTarget() << " is not adjacent to " << source->getName() << endl;
				cout << "\n";

		return false;

	}
	return true;
	
}

ostream& operator<<(ostream& os, const OrderAdvance& ordre)
{
	os << "Arrival of " << *ordre.numberOfunits << " units to " << *ordre.TargetTerritory << " coming from " << *ordre.SourceTerritory << endl;
	return os;
}
//////////////////////////////////
OrderDeploy::OrderDeploy(Player* p,int ID, int numofUnits, string name, string target) : Order(ID, name) {
	this->orderOwner = p;
	this->numberOfunits = numofUnits;
	this->TargetTerritory = target;
}

OrderDeploy::OrderDeploy() : Order() {
	this->numberOfunits = (0);
	this->TargetTerritory = "default";
}
OrderDeploy& OrderDeploy::operator=(const OrderDeploy& dep) {
	Order::operator= (dep);
	this->numberOfunits = dep.numberOfunits;
	this->TargetTerritory = dep.TargetTerritory;
	return *this;
}

OrderDeploy::OrderDeploy(const OrderDeploy& dep) : Order(dep) {
	this->numberOfunits = dep.numberOfunits;
	this->TargetTerritory = dep.TargetTerritory;
}


int OrderDeploy::getUnits() {
	return numberOfunits;
}

string OrderDeploy::getTarget() {
	return TargetTerritory;
}

void OrderDeploy::execute() {
	Player *p = this->orderOwner;
	if(validate()){
		Territory *t = p->getTerritoryFromName(this->getTarget());
		t->army_units += this->getUnits();
		cout << "\nPlayer " << p->name << "'s deploy order has executed on: \n" << t->getName() << endl;
				cout << "\n";

	}else{
		cout << "Player " << p->name << "'s deploy order was invalid on: " << p->getTerritoryFromName(this->getTarget())->getName() << endl;
		cout << "\n";
	}
}

bool OrderDeploy::validate() {
	Player *p = this->orderOwner;
	return(p->ownsTerritory(this->getTarget()));

}

ostream& operator<<(ostream& os, const OrderDeploy& ordre)
{
	os  << "Deployment of " << ordre.TargetTerritory << " units to " << ordre.numberOfunits << endl;
	return os;
}
//////////////////////////////////
OrderBomb::OrderBomb(Player* p,int ID, string name, string target) : Order(ID, name) {
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
		Territory *t;
		t = this->orderOwner->getTerritoryFromName(this->getTarget());
		*t->army_units = *t->army_units / 2;
		cout << "\nPlayer " << this->orderOwner->name << "'s Bomb order has executed on: \n" << this->getTarget() << endl;
		delete t;
		t = NULL;
	}
	else{
		cout << "Bomb Order was not executed - invalid" << endl;
	}
	}


bool OrderBomb::validate() {
	bool neighbour = false;
	for(int i = 0; i < this->orderOwner->getTerritories().size(); i++){
		for(int j = 0; j < this->orderOwner->getTerritories()[i]->getNeighbours().size(); j++){
			if(this->getTarget() == this->orderOwner->getTerritories()[i]->getNeighbours()[j]->getName()){
				return true;
			}
	}
	}
	return true;

}

ostream& operator<<(ostream& os, const OrderBomb& ordre)
{
	os << *ordre.TargetTerritory << " has been bombed successfully!! Half of the units were wiped out!" << endl;
	return os;
}

//////////////////////////////////
OrderBlockade::OrderBlockade(Player* p,int ID, string name, string target) : Order(ID, name) {
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
		*this->orderOwner->getTerritoryFromName(this->getTarget())->army_units *= 2;
		cout << "\nPlayer " << this->orderOwner->name << "'s Blockade order has executed on: \n" << this->getTarget() << endl;

	}
	else{
		cout << "invalid order" << endl;
	}
}

bool OrderBlockade::validate() {
	Player *p = this->orderOwner;
	if(p->getTerritoryFromName(this->getTarget()) == NULL){
		return false;
	}
	delete p;
	p = NULL;

}

ostream& operator<<(ostream& os, const OrderBlockade& ordre)
{
	os << "The number of units on the territory" << *ordre.TargetTerritory << " has been tripled! It is now a neutral territory." << endl;
	return os;
}
/////////////////////////////////
OrderAirlift::OrderAirlift(Player* p,int ID, int numofUnits, string name, string source, string target) : Order(ID, name) {
	this->orderOwner = p;
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
		cout << this->getUnits() << " units have arrived in " << this->getTarget() << " from " << *SourceTerritory << endl;
		int unitsToMove = this->getUnits();
		this->orderOwner->getTerritoryFromName(this->getSource())->army_units -= unitsToMove;
		this->orderOwner->getTerritoryFromName(this->getTarget())->army_units += unitsToMove;
        Notify(this);
	}
	else{
		cout << "Order Airlift was not valid and not has not been executed" << endl;
	}
}

bool OrderAirlift::validate() {
	
	if(!(this->orderOwner->ownsTerritory(this->getSource()) && this->orderOwner->ownsTerritory(this->getTarget()))){
		return false;
	}else{
		return true;
	}

}

ostream& operator<<(ostream& os, const OrderAirlift& ordre)
{
	os << "Landing of  " << *ordre.numberOfunits << " units in " << *ordre.TargetTerritory << " coming from " << *ordre.SourceTerritory << endl;
	return os;
}

/////////////////////////////////
OrderNegotiate::OrderNegotiate(Player* p,int ID, string name, string source, string target) : Order(ID, name) {
	this->orderOwner = p;
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
		cout<< *TargetTerritory << " and  " << *SourceTerritory << " can no longer attack each other" << endl;
		cout << "Negotiation Order has been executed\n";
        Notify(this);
	}
	else
		cout << "Order has not been executed" << endl;
}

bool OrderNegotiate::validate() {
	cout << "Order validity check...\n";
	if (getSource() != getTarget()) {
		cout << "Order is valid\n";
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

ostream& operator<<(ostream& os, const OrdersList& ordre)
{
	os <<"This list contains " << (ordre.ol).size() << " orders:\n";
	for (auto it = (ordre.ol).begin(); it != (ordre.ol).end(); ++it)
		cout << ' ' << (*it);
	return os;
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

void OrdersList::remove(Order *o) {
	ol.erase(std::remove(ol.begin(),ol.end(),o),ol.end());

}

 void OrdersList::addOrder(Order* o) {
 	this->ol.push_back(o);

     Notify(this);

 }

std::string OrdersList::stringToLog(){
    return "Command Issued: " + ol.back()->getOrderName();
}
