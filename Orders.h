#pragma once
#include <iostream>
#include <list>
#include <string>
#include <vector>
#include "Player.h"
using namespace std;


class Order
{
public:
	/*
	Order();
	Order(string name);
	Order(const Order& order);
	Order& operator << (const Order& order);
	*/
	//virtual bool validate();
	virtual void execute();
	virtual void sticker();
	
private:
	//string name;
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
	void remove();

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
	bool validate(Player* p, Territory* t);
	void execute(Player* p, Territory* t, int num);
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
	bool validate(Player* p, Territory* t, Territory* t1);
	void execute(Player* p, Territory* t, Territory* t1, int num);
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
	bool validate(Player* p, Territory* t);
	void execute(Player* p, Territory* t);
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
	bool validate(Player* p, Territory* t);
	void execute(Player* p, Territory* t);
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
	bool validate(Player* p, Territory* t, Territory* t1);
	void execute(Player* p, Territory* t, Territory* t1, int num);
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
	bool validate(Player* p1, Player* p2);
	void execute(Player* p1, Player* p2);
	void sticker();
private:
	string name;
	
};
