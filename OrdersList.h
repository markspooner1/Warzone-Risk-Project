#ifndef ORDERSLIST_H
#define ORDERSLIST_H

#include <iostream>
using namespace std;

	//void move(Order order);
	//void remove(Order order);

	class Order {
	public:	
		bool validate();
		void execute();
		Order(int, string);
		Order();
		Order(const Order& cop);
		Order& operator =(const Order& o);
		int getOrderID();
		void setOrderID(int);
		std::string getOrderName();
		void setOrderName(string);
	private:
		int *OrderID;
		std::string* name;
	};

	class OrderAdvance :public Order {
	public:
		bool validate();
		void execute();
		void advance();
		OrderAdvance();
		OrderAdvance(int,int, string, string,string);
		OrderAdvance(const OrderAdvance& dep);
		OrderAdvance& operator =(const OrderAdvance& dep);
		string getSource();
		string getTarget();
		int getUnits();
	private:
		std::string* SourceTerritory;
		std::string* TargetTerritory;
		int* numberOfunits;
	};

	class OrderDeploy :public Order {
	public:
		bool validate();
		void execute();
		void deploy();
		OrderDeploy();
		OrderDeploy(int, int, string, string);
		OrderDeploy(const OrderDeploy& dep);
		OrderDeploy& operator =(const OrderDeploy& dep);
		string getTarget();
		int getUnits();
	private:
		std::string* TargetTerritory;
		int* numberOfunits;
	};
	
	class OrderBomb :public Order {
	public:
		bool validate();
		void execute();
		void bomb();
		OrderBomb();
		OrderBomb(int, string, string);
		OrderBomb(const OrderBomb& dep);
		OrderBomb& operator =(const OrderBomb& dep);
		string getTarget();
	private:
		std::string* TargetTerritory;
	};

	class OrderBlockade :public Order {
	public:
		bool validate();
		void execute();
		void blockade();
		OrderBlockade();
		OrderBlockade(int, string, string);
		OrderBlockade(const OrderBlockade& dep);
		OrderBlockade& operator =(const OrderBlockade& dep);
		string getTarget();
	private:
		std::string* TargetTerritory;
	};

	class OrderAirlift :public Order {
	public:
		bool validate();
		void execute();
		void airlift();
		OrderAirlift();
		OrderAirlift(int, int, string, string, string);
		OrderAirlift(const OrderAirlift& dep);
		OrderAirlift& operator =(const OrderAirlift& dep);
		string getSource();
		string getTarget();
		int getUnits();
	private:
		std::string* SourceTerritory;
		std::string* TargetTerritory;
		int* numberOfunits;
	};

	class OrderNegotiate :public Order {
	public:
		bool validate();
		void execute();
		void negotiate();
		OrderNegotiate();
		OrderNegotiate(int, string, string, string);
		OrderNegotiate(const OrderNegotiate& dep);
		OrderNegotiate& operator =(const OrderNegotiate& dep);
		string getSource();
		string getTarget();
	private:
		std::string* SourceTerritory;
		std::string* TargetTerritory;
	};
	
	
#endif //ORDERSLIST_H