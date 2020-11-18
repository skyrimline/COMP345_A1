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
	list<Order> orderlist;
	OrderList();
	OrderList(string name);
<<<<<<< HEAD
	OrderList(const OrderList &OrderList);
	OrderList &operator<<(const OrderList &p);
	void move(Order &p_order);
=======
	OrderList(const OrderList& OrderList);
	OrderList& operator << (const OrderList &p);
	void move(Order& p_order);
>>>>>>> 43f30952a0a1169f312b6d197751438325a03fc6
	void remove();

private:
	string name;
};

class Deploy : public Order
{
public:
	Deploy();
	Deploy(string name);
<<<<<<< HEAD
	Deploy(const Deploy &Deploy);
	Deploy &operator<<(const Deploy &p);
	bool validate(Player &p, Territory &t);
	void execute(Player &p, Territory &t, int &num);
=======
	Deploy(const Deploy& Deploy);
	Deploy& operator << (const Deploy &p);
	bool validate(Player& p, Territory& t);
	void execute(Player& p, Territory& t, int& num);
>>>>>>> 43f30952a0a1169f312b6d197751438325a03fc6
	void sticker();

private:
	string name;
};

class Advance : public Order
{
public:
	Advance();
	Advance(string name);
<<<<<<< HEAD
	Advance(const Advance &Advance);
	Advance &operator<<(const Advance &p);
	bool validate(Player &p, Territory &t, Territory *t1);
	void execute(Player &p, Territory &t, Territory *t1, int &num);
=======
	Advance(const Advance& Advance);
	Advance& operator << (const Advance &p);
	bool validate(Player& p, Territory& t, Territory* t1);
	void execute(Player& p, Territory& t, Territory* t1, int& num);
>>>>>>> 43f30952a0a1169f312b6d197751438325a03fc6
	void sticker();

private:
	string name;
};

class Bomb : public Order
{
public:
	Bomb();
	Bomb(string name);
<<<<<<< HEAD
	Bomb(const Bomb &Bomb);
	Bomb &operator=(const Bomb &p);
	bool validate(Player &p, Territory &t);
	void execute(Player &p, Territory &t);
=======
	Bomb(const Bomb& Bomb);
	Bomb& operator = (const Bomb &p);
	bool validate(Player& p, Territory& t);
	void execute(Player& p, Territory& t);
>>>>>>> 43f30952a0a1169f312b6d197751438325a03fc6
	void sticker();

private:
	string name;
};

class Blockade : public Order
{
public:
	Blockade();
	Blockade(string name);
<<<<<<< HEAD
	Blockade(const Blockade &Blockade);
	Blockade &operator=(const Blockade &p);
=======
	Blockade(const Blockade& Blockade);
	Blockade& operator = (const Blockade &p);
>>>>>>> 43f30952a0a1169f312b6d197751438325a03fc6
	bool validate();
	void execute();
	void sticker();

private:
	string name;
};

class Airlift : public Order
{
public:
	Airlift();
	Airlift(string name);
<<<<<<< HEAD
	Airlift(const Airlift &Airlift);
	Airlift &operator=(const Airlift &p);
	bool validate(Player &p, Territory &t, Territory *t1);
	void execute(Player &p, Territory &t, Territory *t1, int &num);
=======
	Airlift(const Airlift& Airlift);
	Airlift& operator = (const Airlift &p);
	bool validate(Player& p, Territory& t, Territory* t1);
	void execute(Player& p, Territory& t, Territory* t1, int& num);
>>>>>>> 43f30952a0a1169f312b6d197751438325a03fc6
	void sticker();

private:
	string name;
};

class Negotiate : public Order
{
public:
	Negotiate();
	Negotiate(string name);
<<<<<<< HEAD
	Negotiate(const Negotiate &Negotiate);
	Negotiate &operator=(const Negotiate &p);
=======
	Negotiate(const Negotiate& Negotiate);
	Negotiate& operator = (const Negotiate &p);
>>>>>>> 43f30952a0a1169f312b6d197751438325a03fc6
	bool validate();
	void execute();
	void sticker();

private:
	string name;
};
