#ifndef ORDERS_H
#define ORDERS_H

#include <iostream>
#include <iterator>
#include <list>
#include <vector>
using namespace std;

class Order {
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
private:
	int* OrderID;
	std::string* name;
};

class OrdersList {
public:
	void move();
	void remove();
	OrdersList();
	OrdersList(const OrdersList& cop);
	OrdersList& operator =(const OrdersList& o);
	vector<Order *> ol;
	friend ostream& operator<<(ostream& os, const OrdersList& ordre);
	void addOrder(Order o);
};

class OrderAdvance :public Order {
public:
	bool validate();
	void execute();
	OrderAdvance();
	OrderAdvance(int, int, string, string, string);
	OrderAdvance(const OrderAdvance& dep);
	OrderAdvance& operator =(const OrderAdvance& dep);
	string getSource();
	string getTarget();
	int getUnits();
	friend ostream& operator<<(ostream& os, const OrderAdvance& ordre);
private:
	std::string* SourceTerritory;
	std::string* TargetTerritory;
	int* numberOfunits;
};

class OrderDeploy :public Order {
public:
	bool validate();
	void execute();
	OrderDeploy();
	OrderDeploy(int, int, string, string);
	OrderDeploy(const OrderDeploy& dep);
	OrderDeploy& operator =(const OrderDeploy& dep);
	string getTarget();
	int getUnits();
	friend ostream& operator<<(ostream& os, const OrderDeploy& ordre);
private:
	std::string* TargetTerritory;
	int* numberOfunits;
};

class OrderBomb :public Order {
public:
	bool validate();
	void execute();
	OrderBomb();
	OrderBomb(int, string, string);
	OrderBomb(const OrderBomb& dep);
	OrderBomb& operator =(const OrderBomb& dep);
	string getTarget();
	friend ostream& operator<<(ostream& os, const OrderBomb& ordre);
private:
	std::string* TargetTerritory;
};

class OrderBlockade :public Order {
public:
	bool validate();
	void execute();
	OrderBlockade();
	OrderBlockade(int, string, string);
	OrderBlockade(const OrderBlockade& dep);
	OrderBlockade& operator =(const OrderBlockade& dep);
	string getTarget();
	friend ostream& operator<<(ostream& os, const OrderBlockade& ordre);
private:
	std::string* TargetTerritory;
};

class OrderAirlift :public Order {
public:
	bool validate();
	void execute();
	OrderAirlift();
	OrderAirlift(int, int, string, string, string);
	OrderAirlift(const OrderAirlift& dep);
	OrderAirlift& operator =(const OrderAirlift& dep);
	string getSource();
	string getTarget();
	int getUnits();
	friend ostream& operator<<(ostream& os, const OrderAirlift& ordre);
private:
	std::string* SourceTerritory;
	std::string* TargetTerritory;
	int* numberOfunits;
};

class OrderNegotiate :public Order {
public:
	bool validate();
	void execute();
	OrderNegotiate();
	OrderNegotiate(int, string, string, string);
	OrderNegotiate(const OrderNegotiate& dep);
	OrderNegotiate& operator =(const OrderNegotiate& dep);
	string getSource();
	string getTarget();
	friend ostream& operator<<(ostream& os, const OrderNegotiate& ordre);
private:
	std::string* SourceTerritory;
	std::string* TargetTerritory;
};
void testOrdersLists();

#endif //ORDERS_H
