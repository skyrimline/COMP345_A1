#include <iostream>
#include <list>
#include "Orders.h"
using namespace std;


class Order
{
public:
	Order();
	Order(Order &order, string oname);
	Order()
	{
	}
	Order& operator = (const Order &order)
	{
		return *this;
	};
	virtual bool validate(Order p_order)
	{
			return 0;
	};
	virtual void execute(Order p_order);

private:
	string name;
};
class OrderList
{
	static list <Order> order;
public:
	OrderList();
	OrderList(const OrderList &orderlist)
	{

	};
	OrderList& operator = (const OrderList &orderlist)
	{
		return *this;
	};
	friend void move(Order order)
	{
		list.push_back(order);
		cout << "Player has added Order " << order.name << " to the OrderList" endl;

	};
	friend void remove()
	{
		list.pop_back();

	};
};

class deploy : public Order 
{
public:
	deploy();
	deploy(deploy &deploy);
	deploy& operator = (const deploy &p);
	friend bool validate(Order p_order)
	{	
		if (p_order.name == this->name)
			return 1;
		else
			return 0;
	};
	 void execute(Order p_order) {
		if (validate(p_order))
			cout << "Player1 has deployed their army." << endl;
		else
			cout << "" << endl;
	};
private:
	string name = "deploy";
};

class advance : public Order 
{
public:
	advance();
	advance(advance &advance);
	advance& operator = (const advance &p);
	friend bool validate(Order p_order)
	{
		if (p_order.name == this->name)
			return 1;
		else
			return 0;
	};
	 void execute(Order p_order) {
		if (validate(p_order))
			cout << "Player1 has advanced their army." << endl;
		else
			cout << "" << endl;
	 };
	
private:
	string name = "advance";
};

class bomb : public Order 
{
public:
	bomb();
	bomb(bomb &bomb);
	bomb& operator = (const bomb &p);
	friend bool validate(Order p_order)
	{
		if (p_order.name == this->name)
			return 1;
		else
			return 0;
	};
	void execute(Order p_order) {
		if (validate(p_order))
			cout << "Player1 has bombed." << endl;
		else
			cout << "" << endl;
	};

private:
	string name = "bomb";
};

class blockade : public Order 
{
public:
	blockade();
	blockade(blockade &blockade);
	blockade& operator = (const blockade &p);
	friend bool validate(Order p_order)
	{
		if (p_order.name == this->name)
			return 1;
		else
			return 0;
	};
	void execute(Order p_order) {
		if (validate(p_order))
			cout << "Player1 has blockaded their territory." << endl;
		else
			cout << "" << endl;
	};

private:
	string name = "blockade";
};

class airlift : public Order 
{
public:
	airlift();
	airlift(airlift &airlift);
	airlift& operator = (const airlift &p);
	friend bool validate(Order p_order)
	{
		if (p_order.name == this->name)
			return 1;
		else
			return 0;
	};
	void execute(Order p_order) {
		if (validate(p_order))
			cout << "Player1 has airlifted his army." << endl;
		else
			cout << "" << endl;
	};

private:
	string name = "airlift";
};

class negotiate : public Order 
{
public:
	negotiate();
	negotiate(negotiate &negotiate);
	negotiate& operator = (const negotiate &p);
	friend bool validate(Order p_order)
	{	
		if (p_order.name == this->name)
			return 1;
		else
			return 0;
	};
	void execute(Order p_order) {
		if (validate(p_order))
			cout << "Player1 has used diplomacy." << endl;
		else
			cout << "" << endl;
	};

private:
	string name = "negotiate";
};



int main() {


	return 0;
}
