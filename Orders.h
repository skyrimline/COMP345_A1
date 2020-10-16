#pragma once
#include <iostream>
#include <list>
#include <string>
using namespace std;


class Order
{
public:
	Order();
	Order(string name);
	Order(const Order& order);
	Order& operator << (const Order& order);
	bool validate(Order);
	void execute(Order);
	virtual void sticker();
	
private:
	string name;
};

class OrderList
{
	
public:
	list <Order> orderlist;
	OrderList();
	OrderList(string name);
	OrderList(const OrderList& OrderList);
	OrderList& operator << (const OrderList &p);
	void move(Order& p_order);
	void remove(Order& p_order);

private:
	string name;
	
};

class Deploy : public Order 
{
public:
	Deploy();
	Deploy(string name);
	Deploy(const Deploy& Deploy);
	Deploy& operator << (const Deploy &p);
	bool validate(Deploy);
	void execute(Deploy);
	void sticker();
private:
	string name;
	
};

class Advance : public Order 
{
public:
	Advance();
	Advance(string name);
	Advance(const Advance& Advance);
	Advance& operator << (const Advance &p);
	bool validate(Advance);
	void execute(Advance);
	void sticker();
private:
	string name;
	
};	

class Bomb : public Order 
{
public:
	Bomb();
	Bomb(string name);
	Bomb(const Bomb& Bomb);
	Bomb& operator = (const Bomb &p);
	bool validate(Bomb);
	void execute(Bomb);
	void sticker();
private:
	string name;
	
};

class Blockade : public Order 
{
public:
	Blockade();
	Blockade(string name);
	Blockade(const Blockade& Blockade);
	Blockade& operator = (const Blockade &p);
	bool validate(Blockade);
	void execute(Blockade);
	void sticker();
private:
	string name;
	
};

class Airlift : public Order 
{
public:
	Airlift();
	Airlift(string name);
	Airlift(const Airlift& Airlift);
	Airlift& operator = (const Airlift &p);
	bool validate(Airlift);
	void execute(Airlift);
	void sticker();
private:
	string name;
	
};

class Negotiate : public Order 
{
public:
	Negotiate();
	Negotiate(string name);
	Negotiate(const Negotiate& Negotiate);
	Negotiate& operator = (const Negotiate &p);
	bool validate(Negotiate);
	void execute(Negotiate);
	void sticker();
private:
	string name;
	
};
