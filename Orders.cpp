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
OrderAdvance::OrderAdvance(Player* p, int ID, int numofUnits, string name, Territory* source, Territory* target) : Order(ID, name) {
	this->orderOwner = p;
	this->numberOfunits = numofUnits;
	this->SourceTerritory = source;
	this->TargetTerritory = target;
}

OrderAdvance::OrderAdvance():Order() {
	this->numberOfunits = (0);

}
OrderAdvance& OrderAdvance::operator=(const OrderAdvance& dep) {
	Order::operator= (dep);
	this->numberOfunits = dep.numberOfunits;
	this->SourceTerritory = dep.SourceTerritory;
	this->TargetTerritory = dep.TargetTerritory;
	return *this;
}

OrderAdvance::OrderAdvance(const OrderAdvance& dep) : Order(dep) {
	this->numberOfunits = dep.numberOfunits;
	this->SourceTerritory = dep.SourceTerritory;
	this->TargetTerritory = dep.TargetTerritory;
}


int OrderAdvance::getUnits() {
	return numberOfunits;
}

Territory* OrderAdvance::getTarget() {
	return TargetTerritory;
}
Territory* OrderAdvance::getSource() {
	return SourceTerritory;
}

void OrderAdvance::execute() {
	if (validate()) {
			cout << "\t-----Order Advance Execution---------\n" << endl;

			Territory *source = this->getSource();
			Territory *target = this->getTarget();
		if((this->getTarget()->owner->name == this->orderOwner->name)){
			source->army_units -= this->getUnits();
			target->army_units += this->getUnits();
			cout << "Advance order executeed player has moved army units from: " << source->getName() << " to " << target->getName() << endl;
		}else{
			cout << "---Player " << this->orderOwner->name << "---- has issued an advance order on: " << target->getName() << endl;
					cout << "\n";

			int randNumber;
			int attacker = source->army_units;
			int defender = target->army_units;
			for(int i = 0;;i++){
				randNumber = rand() % 10 + 1;
				if(attacker <= 0){
					cout << this->orderOwner->name << " has lost the battle to " << target->getName() << endl;
					cout << "Moving " << defender << " army units to " << source->getName() << endl;
					source->army_units += defender;
					cout << "removing " << source->getName();
					this->orderOwner->removeTerritory(source);
					cout << target->owner->name << " has conquered " << source->getName() << endl;
					target->owner->addTerritory(source);
					break;
					
				}else if(defender <= 0){
					cout << this->orderOwner->name << " has won the battle against " << target->getName() << endl;
					cout << "Moving " << attacker << " army units to " << target->getName() << endl;
							cout << "\n";

					target->army_units += attacker;
					target->owner->removeTerritory(target);
					this->orderOwner->addTerritory(target);
					break;
				}else{
					if(randNumber <= 6){
						attacker--;
					}
					if(randNumber <= 7){
						defender--;
					}
				}
			
			}

		}

        Notify(this);
	}

}

bool OrderAdvance::validate() {
		cout << "\t-----Order Advance Validation---------\n" << endl;

	Player *p = this->orderOwner;
	bool owns = false;
	if(this->getSource()->owner->name == this->orderOwner->name){
		owns = true;
	}else{
		cout << "Invalid order: " << p->name << " doesnt own " << this->getSource()->getName() << endl;
				cout << "\n";

	}
	if(!owns) return false;
 	Territory *source = this->getSource();
	bool isAdj = false;
	

	for(int i = 0; i < source->getNeighbours().size(); i++){
			if(this->getTarget()->getName() == source->getNeighbours()[i]->getName()){
				isAdj = true;
			}
	}
	if(!isAdj){
		cout << "Invalid Order: " << this->getTarget()->getName() << " is not adjacent to " << source->getName() << endl;
		cout << "\n";
		return false;
	}
	return true;
	
}

ostream& operator<<(ostream& os, const OrderAdvance& ordre)
{
	os << "Arrival of " << ordre.numberOfunits << " units to " << ordre.TargetTerritory << " coming from " << ordre.SourceTerritory << endl;
	return os;
}
//////////////////////////////////
OrderDeploy::OrderDeploy(Player* p,int ID, int numofUnits, string name, Territory* target) : Order(ID, name) {
	this->orderOwner = p;
	this->numberOfunits = numofUnits;
	this->TargetTerritory = target;
}

OrderDeploy::OrderDeploy() : Order() {
	this->numberOfunits = (0);
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

Territory* OrderDeploy::getTarget() {
	return TargetTerritory;
}

void OrderDeploy::execute() {

	Player *p = this->orderOwner;
	if(validate()){
				cout << "\t-----Order Deploy Execution---------\n" << endl;

		Territory *t = this->getTarget();
		t->army_units += this->getUnits();
		cout << "\nPlayer " << p->name << "'s deploy order has executed on: \n" << t->getName() << endl;
		cout << "\n";

	}else{
		cout << "Player " << p->name << "'s deploy order was invalid on: " << this->getTarget()->getName() << endl;
		cout << "\n";
	}
}

bool OrderDeploy::validate() {
	cout << "\t-----Order Deploy validation---------\n" << endl;

	Player *p = this->orderOwner;
	return(p->name == this->getTarget()->owner->name);

}

ostream& operator<<(ostream& os, const OrderDeploy& ordre)
{
	os  << "Deployment of " << ordre.TargetTerritory << " units to " << ordre.numberOfunits << endl;
	return os;
}
//////////////////////////////////
OrderBomb::OrderBomb(Player* p,int ID, string name, Territory* target) : Order(ID, name) {
	this->orderOwner = p;
	this->TargetTerritory = target;
}

OrderBomb::OrderBomb() : Order() {
}
OrderBomb& OrderBomb::operator=(const OrderBomb& dep) {
	Order::operator= (dep);
	this->TargetTerritory = dep.TargetTerritory;
	return *this;
}


Territory* OrderBomb::getTarget() {
	return TargetTerritory;
}

void OrderBomb::execute() {

	if (validate()) {
					cout << "\t-----Order Bomb Execution---------\n" << endl;

		Territory *t = this->getTarget();
		t->army_units = t->army_units / 2;
		cout << "\nPlayer " << this->orderOwner->name << "'s Bomb order has executed on: \n" << this->getTarget()->getName() << endl;
	}
	else{
		cout << "Bomb Order was not executed - invalid" << endl;
	}
		Notify(this);

	}


bool OrderBomb::validate() {
				cout << "\t-----Order Bomb Validation---------\n" << endl;

	Territory *t = this->getTarget();
	if(t->owner->name == this->orderOwner->name){
		return false;
	}
	for(int i = 0; this->orderOwner->getTerritories().size(); i++){
		for(int j = 0; j < this->orderOwner->getTerritories()[i]->getNeighbours().size(); j++){
			if(t->getName() == this->orderOwner->getTerritories()[i]->getNeighbours()[j]->getName()){
				return true;
			}
		}
	}
}

ostream& operator<<(ostream& os, const OrderBomb& ordre)
{
	os << ordre.TargetTerritory << " has been bombed successfully!! Half of the units were wiped out!" << endl;
	return os;
}

//////////////////////////////////
OrderBlockade::OrderBlockade(Player* p,int ID, string name, Territory* target) : Order(ID, name) {
	this->orderOwner = p;
	this->TargetTerritory = target;
}

OrderBlockade::OrderBlockade() : Order() {
}
OrderBlockade& OrderBlockade::operator=(const OrderBlockade& dep) {
	Order::operator= (dep);
	this->TargetTerritory = dep.TargetTerritory;
	return *this;
}

OrderBlockade::OrderBlockade(const OrderBlockade& dep) : Order(dep) {
	this->TargetTerritory = dep.TargetTerritory;
}

Territory* OrderBlockade::getTarget() {
	return TargetTerritory;
}



void OrderBlockade::execute() {

	if (validate()) {
						cout << "\t-----Order Blockade Execution---------\n" << endl;

		this->getTarget()->army_units *= 2;
		cout << "\nPlayer " << this->orderOwner->name << "'s Blockade order has executed on: \n" << this->getTarget()->getName() << endl;
		cout << this->getTarget()->getName() << " has transferred to the neutral player" << endl;
	}	
	else{
		cout << "invalid Blockade order" << endl;
	}
}

bool OrderBlockade::validate() {
				cout << "\t-----Order Blockade Validation---------\n" << endl;

	Player *p = this->orderOwner;

	if(this->getTarget()->owner->name == this->orderOwner->name){
		return true;
	}

	return false;

}

ostream& operator<<(ostream& os, const OrderBlockade& ordre)
{
	os << "The number of units on the territory" << ordre.TargetTerritory << " has been tripled! It is now a neutral territory." << endl;
	return os;
}
/////////////////////////////////
OrderAirlift::OrderAirlift(Player* p,int ID, int numofUnits, string name,Territory* source,Territory* target) : Order(ID, name) {
	this->orderOwner = p;
	this->numberOfunits = numofUnits;
	this->SourceTerritory = source;
	this->TargetTerritory = target;
}

OrderAirlift::OrderAirlift() : Order() {
	this->numberOfunits = 0;

}
OrderAirlift& OrderAirlift::operator=(const OrderAirlift& dep) {
	Order::operator= (dep);
	this->numberOfunits = dep.numberOfunits;
	this->SourceTerritory = dep.SourceTerritory;
	this->TargetTerritory = dep.TargetTerritory;
	return *this;
}

OrderAirlift::OrderAirlift(const OrderAirlift& dep) : Order(dep) {
	this->numberOfunits = dep.numberOfunits;
	this->SourceTerritory = dep.SourceTerritory;
	this->TargetTerritory = dep.TargetTerritory;
}


int OrderAirlift::getUnits() {
	return numberOfunits;
}

Territory* OrderAirlift::getTarget() {
	return TargetTerritory;
}
Territory* OrderAirlift::getSource() {
	return SourceTerritory;
}

void OrderAirlift::execute() {

	if (validate()) {
						cout << "\t-----Order Airlift Execution---------\n" << endl;

		cout << this->getUnits() << " units have arrived in " << this->getTarget()->getName() << " from " << this->getSource()->getName() << endl;
		int unitsToMove = this->getUnits();
		this->getSource()->army_units -= unitsToMove;
		this->getTarget()->army_units += unitsToMove;
         Notify(this);
	}
	else{
		cout << "Order Airlift was not valid and not has not been executed" << endl;
	}
}

bool OrderAirlift::validate() {
	cout << "\t-----Order Airlift Validation---------\n" << endl;

	
	if(!(orderOwner->name == this->getSource()->owner->name) && orderOwner->name == (this->getTarget()->owner->name)){
		return false;
	}else{
		return true;
	}

}

ostream& operator<<(ostream& os, const OrderAirlift& ordre)
{
	os << "Landing of  " << ordre.numberOfunits << " units in " << ordre.TargetTerritory << " coming from " << ordre.SourceTerritory << endl;
	return os;
}

/////////////////////////////////
OrderNegotiate::OrderNegotiate(Player* p,int ID, string name, Territory* source, Territory* target) : Order(ID, name) {
	this->orderOwner = p;
	this->SourceTerritory = source;
	this->TargetTerritory = target;
}

OrderNegotiate::OrderNegotiate() : Order() {

}
OrderNegotiate& OrderNegotiate::operator=(const OrderNegotiate& dep) {
	Order::operator= (dep);
	this->SourceTerritory = dep.SourceTerritory;
	this->TargetTerritory = dep.TargetTerritory;
	return *this;
}

OrderNegotiate::OrderNegotiate(const OrderNegotiate& dep) : Order(dep) {
	this->SourceTerritory = dep.SourceTerritory;
	this->TargetTerritory = dep.TargetTerritory;
}

Territory* OrderNegotiate::getTarget() {
	return TargetTerritory;
}
Territory* OrderNegotiate::getSource() {
	return SourceTerritory;
}

void OrderNegotiate::execute() {

	if (validate()) {
						cout << "\t-----Order Negotiate Execution---------\n" << endl;

		cout<< this->getTarget()->getName() << " and  " << this->getSource()->getName() << " can no longer attack each other" << endl;
		for(int i = 0; i < this->orderOwner->toAttack().size(); i++){
			if(this->orderOwner->toAttack()[i]->getName() == getTarget()->getName()){
				this->orderOwner->toAttack().erase(std::remove(this->orderOwner->toAttack().begin(),this->orderOwner->toAttack().end(),getTarget()),this->orderOwner->toAttack().end());
			}
		}
		cout << "Negotiation Order has been executed\n";

        Notify(this);
	}
	else
		cout << "Order has not been executed" << endl;
}

bool OrderNegotiate::validate() {
	cout << "\t-----Order Negotiate Validation---------\n" << endl;

	if (getSource()->getName() != getTarget()->getName()) {
		cout << "Order is valid\n";
		return true;
	}
	else {
		cout << "Order is invalid" << endl;
		return false;
	}

}

ostream& operator<<(ostream& os, const OrderNegotiate& ordre)
{
	os << ordre.TargetTerritory << " and  " << ordre.SourceTerritory << " can no longer attack each other" << endl;
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
	cout << "size before removal of order: "<<ol.size() << endl;
	ol.erase(std::remove(ol.begin(),ol.end(),o),ol.end());
	delete o;
	cout << "size after removal of order: "<<ol.size() << endl;


}

 void OrdersList::addOrder(Order* o) {
 	this->ol.push_back(o);

     Notify(this);

 }

std::string OrdersList::stringToLog(){
    return "Command Issued: " + ol.back()->getOrderName();
}
