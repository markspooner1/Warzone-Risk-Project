#ifndef ORDERS_H
#define ORDERS_H

#include <iostream>
#include <iterator>
#include <list>
#include <vector>
#include "LoggingObserver.h"
#include "Player.h"
#include "Map.h"
class Territory;
using namespace std;
class Player;
class Order: public Subject, public ILoggable {
public:
	virtual bool validate();
	virtual void execute();
	Order(int, string);
	Order();
	Order(const Order& cop);
	Order& operator =(const Order& o);
	int getOrderID();
	void setOrderID(int);
	std::string getOrderName();
	void setOrderName(string);
	friend ostream& operator<<(ostream& os, const Order& ordre);
    std::string stringToLog();
	int* OrderID;
	std::string* name;
private:
};

class OrdersList: public Subject, public ILoggable{
public:
	void move();
	void remove(Order *o);
	OrdersList();
	OrdersList(const OrdersList& cop);
	OrdersList& operator =(const OrdersList& o);
	vector<Order *> ol;
	friend ostream& operator<<(ostream& os, const OrdersList& ordre);
	void addOrder(Order *o);
	
    std::string stringToLog();
};

class OrderAdvance :public Order {
public:
	bool validate();
	void execute();
	OrderAdvance();
	OrderAdvance(Player*, int, int, string, Territory*, Territory*);
	OrderAdvance(const OrderAdvance& dep);
	~OrderAdvance();
	OrderAdvance& operator =(const OrderAdvance& dep);
	Territory* getSource();
	Territory* getTarget();
	int getUnits();
	friend ostream& operator<<(ostream& os, const OrderAdvance& ordre);
		Player* orderOwner;

	Territory* SourceTerritory;
	Territory* TargetTerritory;

private:
	
	int numberOfunits;
};

class OrderDeploy :public Order {
public:
	bool validate();
	void execute();
	OrderDeploy();
	OrderDeploy(Player*, int, int, string, Territory*);
	OrderDeploy(const OrderDeploy& dep);
	~OrderDeploy();
	OrderDeploy& operator =(const OrderDeploy& dep);
	Territory* getTarget();
	int getUnits();
	friend ostream& operator<<(ostream& os, const OrderDeploy& ordre);
		Player* orderOwner;
		Territory* TargetTerritory;

private:
	
	int numberOfunits;
};

class OrderBomb :public Order {
public:
	Player* orderOwner;
	bool validate();
	void execute();
	OrderBomb();
	OrderBomb(Player*, int, string, Territory*);
	OrderBomb(const OrderBomb& dep);
	~OrderBomb();
	OrderBomb& operator =(const OrderBomb& dep);
	Territory* getTarget();
	friend ostream& operator<<(ostream& os, const OrderBomb& ordre);
	Territory* TargetTerritory;
private:
};

class OrderBlockade :public Order {
public:
	bool validate();
	void execute();
	OrderBlockade();
	OrderBlockade(Player*, int, string, Territory*);
	OrderBlockade(const OrderBlockade& dep);
	~OrderBlockade();
	OrderBlockade& operator =(const OrderBlockade& dep);
	Territory* getTarget();
	friend ostream& operator<<(ostream& os, const OrderBlockade& ordre);
		Player* orderOwner;
		Territory* TargetTerritory;


private:

};

class OrderAirlift :public Order {
public:
	bool validate();
	void execute();
	OrderAirlift();
	OrderAirlift(Player*, int, int, string, Territory*, Territory*);
	OrderAirlift(const OrderAirlift& dep);
	~OrderAirlift();
	OrderAirlift& operator =(const OrderAirlift& dep);
	Territory* getSource();
	Territory* getTarget();
	int getUnits();
	friend ostream& operator<<(ostream& os, const OrderAirlift& ordre);
		Player *orderOwner;
	Territory* SourceTerritory;
	Territory* TargetTerritory;

private:

	int numberOfunits;
};

class OrderNegotiate :public Order {
public:
	bool validate();
	void execute();
	OrderNegotiate();
	OrderNegotiate(Player*, int, string, Territory*, Territory*);
	OrderNegotiate(const OrderNegotiate& dep);
	~OrderNegotiate();
	OrderNegotiate& operator =(const OrderNegotiate& dep);
	Territory* getSource();
	Territory* getTarget();
	friend ostream& operator<<(ostream& os, const OrderNegotiate& ordre);
		Player *orderOwner;
	Territory* SourceTerritory;
	Territory* TargetTerritory;

private:
	
};
void testOrdersExecution();

#endif //ORDERS_H
