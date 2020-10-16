#include "Orders.h"

using namespace std;

//default constructor//constructor//copy constructor
Order::Order() {

}
	
Order::Order(string name) {
	this->name = name;
}

Order::Order(const Order & order)
{
	*this = order;
}

Order & Order::operator<<(const Order & order)
{
	return *this;
}



bool Order::validate(Order)
{
	return false;
}

void Order::execute(Order)
{
	
}

void Order::sticker()
{
	cout << " ";
}



//default constructor//constructor//copy constructor	
OrderList::OrderList()
{
}
OrderList::OrderList(string name)
{
	this->name = name;
	list <Order> orderlist;
}

OrderList::OrderList(const OrderList & orderlist)
{
	*this = orderlist;
}

OrderList & OrderList::operator<<(const OrderList & p)
{
	return *this;
}



void OrderList::move(Order& p_order)
{
	orderlist.push_back(p_order);
	cout << "Player has added Order ";
	p_order.sticker();
	cout << " to the OrderList" << endl;
}

void OrderList::remove(Order& p_order)
{
	orderlist.pop_back();
	cout << "Player has removed Order "; 
	p_order.sticker();
	cout << " from the OrderList" << endl;
}
	


//default constructor//constructor//copy constructor
Deploy::Deploy()
{
}

Deploy::Deploy(string name)
{
	this->name = name;
}

Deploy::Deploy(const Deploy & deploy)
{
	*this = deploy;
}

Deploy & Deploy::operator<<(const Deploy & p)
{
	return *this;
}

bool Deploy::validate(Deploy d)//check if it is one kind of order
{
	return true;
}

void Deploy::execute(Deploy d)//implement the order
{
	if (validate(d))
		cout << "Player1 has deployed their army." << endl;
	else
		cout << "" << endl;
}

void Deploy::sticker()
{
	cout << "Deploy";
}

//default constructor//constructor//copy constructor
Advance::Advance()
{
}

Advance::Advance(string name)
{
	this->name = name;
}

Advance::Advance(const Advance & advance)
{
	*this = advance;
}

Advance & Advance::operator<<(const Advance & p)
{
	return *this;
}

void Advance::sticker()
{
	cout << "Advance";
}

	

bool Advance::validate(Advance a)
{
	return true;
}

void Advance::execute(Advance a)
{
	if (validate(a))
		cout << "Player1 has advanced their army." << endl;
	else
		cout << "" << endl;
}
	

//default constructor//constructor//copy constructor	
Bomb::Bomb()
{
}

Bomb::Bomb(string name)
{
	this->name = name;
}

Bomb::Bomb(const Bomb & bomb)
{
	*this = bomb;
}

Bomb & Bomb::operator=(const Bomb & p)
{
	return *this;
}

bool Bomb::validate(Bomb b)
{
	return true;
}

void Bomb::execute(Bomb b)
{
	if (validate(b))
		cout << "Player1 has bombed." << endl;
	else
		cout << "" << endl;
}
void Bomb::sticker()
{
	cout << "Bomb";
}


//default constructor//constructor//copy constructor
Blockade::Blockade()
{
}

Blockade::Blockade(string name)
{
	this->name = name;
}

Blockade::Blockade(const Blockade & blockade)
{
	*this = blockade;
}

Blockade & Blockade::operator=(const Blockade & p)
{
	return *this;
}

bool Blockade::validate(Blockade b)
{
	return true;
}

void Blockade::execute(Blockade b)
{
	if (validate(b))
		cout << "Player1 has blockaded." << endl;
	else
		cout << "" << endl;
}
void Blockade::sticker()
{
	cout << "Blockade";
}


//default constructor//constructor//copy constructor
Airlift::Airlift()
{
}

Airlift::Airlift(string name)
{
	this->name = name;
}

Airlift::Airlift(const Airlift & airlift)
{
	*this = airlift;
}

Airlift & Airlift::operator=(const Airlift & p)
{
	return *this;
}

bool Airlift::validate(Airlift a)
{
	return true;
}

void Airlift::execute(Airlift a)
{
	if (validate(a))
		cout << "Player1 has airlifted their army." << endl;
	else
		cout << "" << endl;
}
void Airlift::sticker()
{
	cout << "Airlift";
}



//default constructor//constructor//copy constructor
Negotiate::Negotiate()
{
}

Negotiate::Negotiate(string name)
{
	this->name = name;
}

Negotiate::Negotiate(const Negotiate & negotiate)
{
	*this = negotiate;
}

Negotiate & Negotiate::operator=(const Negotiate & p)
{
	return *this;
}

bool Negotiate::validate(Negotiate n)
{
	return true;
}

void Negotiate::execute(Negotiate n)
{
	if (validate(n))
		cout << "Player1 has started negotiation." << endl;
	else
		cout << "" << endl;
}
void Negotiate::sticker()
{
	cout << "Negotiate";
}
