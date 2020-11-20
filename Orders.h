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
//	string getType();
	
private:
	//string name;
	string type;
};

class OrderList
{
	
public:
	list <Order> orderlist;
	OrderList();
	~OrderList();
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
	~Deploy();
	Deploy(Player* p, Territory*, int);
	Deploy(const Deploy& Deploy);
	Deploy& operator << (const Deploy &p);
	bool validate();
	void execute();
	void sticker();
private:
    const string type="deploy";
    Player* p;
    Territory* t;
    int* numOfArmies;
};

class Advance : public Order 
{
public:
	Advance();
	~Advance();
	Advance(Player* p, Territory* t, Territory* t1, int numOfArmies);
	Advance(const Advance& Advance);
	Advance& operator << (const Advance &p);
	bool validate();
	void execute();
	void sticker();
    Territory* getSource();
    Territory* getTarget();
private:
    const string type="advance";
    Player* p;
    Territory* source;
    Territory* target;
    int* numOfArmies;
	
};	

class Bomb : public Order 
{
public:
	Bomb();
	~Bomb();
	Bomb(Player* p, Territory* t);
	Bomb(const Bomb& Bomb);
	Bomb& operator = (const Bomb &p);
	bool validate();
	void execute();
	void sticker();
private:
    const string type="bomb";
    Player* p;
    Territory* target;
};

class Blockade : public Order 
{
public:
	Blockade();
	~Blockade();
	Blockade(Player* p, Territory* t);
	Blockade(const Blockade& Blockade);
	Blockade& operator = (const Blockade &p);
	bool validate();
	void execute();
	void sticker();
private:
    const string type="blockade";
    Player* p;
    Territory* t;
};

class Airlift : public Order 
{
public:
	Airlift();
	~Airlift();
	Airlift(Player* p,Territory* t, Territory* t1, int numOfArmies);
	Airlift(const Airlift& Airlift);
	Airlift& operator = (const Airlift &p);
	bool validate();
	void execute();
	void sticker();
    Territory* getSource();
    Territory* getTarget();
private:
    const string type="airlift";
    Player* p;
    Territory* source;
    Territory* target;
    int* numOfArmies;
};

class Negotiate : public Order 
{
public:
	Negotiate();
	~Negotiate();
	Negotiate(Player* p1, Player* p2);
	Negotiate(const Negotiate& Negotiate);
	Negotiate& operator = (const Negotiate &p);
	bool validate();
	void execute();
	void sticker();
private:
    const string type="negotiate";
    Player* p1;
    Player* p2;
};