
#include "Orders.h"
#include "Player.h"

using namespace std;

int divide(int *x, int *y)
{
	return (*x) / (*y);
}
/*
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
*/


/*
bool Order::validate()
{
	return false;
}
*/

void Order::execute()
{
	
}

void Order::sticker()
{
	
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

void OrderList::remove()
{
	orderlist.pop_back();
	cout << "Player has removed the last Order from the OrderList" << endl;
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

bool Deploy::validate(Player* p, Territory* t)//check if it is one kind of order
{	if (p->isOwner(t))
		return true;
	else
	{
		cout << "invalid order " << endl;
		return false;
	}
}	

void Deploy::execute(Player* p, Territory* t, int num)//implement the order
{
	if (validate(p, t))
	{ 
		cout << "Player has deployed army." << endl;
		t->numberOfArmies += num;
	}
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

	

bool Advance::validate(Player* p, Territory* t, Territory* t1)
{
	if (!t->isNeighbour(t1))
	{ 
		cout << "invalid order " << endl;
		return false;
	}
	else if (p->isOwner(t))
		return true;
	else
	{
		cout << "invalid order " << endl;
		return false;
	}
}

void Advance::execute(Player* p, Territory* t, Territory* t1, int num)
{
	if (validate(p, t, t1))
	{
		if (p->isOwner(t) && p->isOwner(t1))
		{
			cout << "Player has advanced army to an friendly territory " << endl;
			t->numberOfArmies -= num;
			t1->numberOfArmies += num;
		}
		else
		{
			t->numberOfArmies -= num;
			int attackingforce = num;
			if (!t1->hasOwner())
			{
				p->addTerritory(t1);
				cout << "Player has occupied a neutral territory " << endl;
			}
			else
			{
				cout << "Player has advanced army to enemies territory " << endl;
				cout << "Battle starts " << endl;
				for (int i = 0; i < num; i++)
				{
					int attack_chance, defend_chance;
					attack_chance = rand() % 100 + 1;
					defend_chance = rand() % 100 + 1;
					if (attack_chance <= 60)
						t1->numberOfArmies -= 1;
					if (defend_chance <= 70)
						attackingforce -= 1;
					
				}
				
				if (t1->numberOfArmies == 0)
				{
					p->addTerritory(t1);
					t1->numberOfArmies += attackingforce;
					//p.addCards();

					cout << "Player has conquered enemies' territory and gets a new card" << endl;
				}
			}
			
		}
	}
	
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

bool Bomb::validate(Player* p, Territory* t)
{
	if (p->isOwner(t))
	{
		cout << "invalid order, cannot bomb friendly territory" << endl;
		return false;
	}
	else
	{
		cout << "valid " << endl;
		return true;
	}
}

void Bomb::execute(Player* p, Territory* t)
{
	if (validate(p, t))
	{
		int* num = t->getNumberOfArmies();
		t->setNumberOfArmies(*num / 2);
		cout << "Player has bombed enemies' territory, half of the defensive armies are lost " << endl;
	}
	
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

bool Blockade::validate(Player* p, Territory* t)
{
	if (p->isOwner(t))
		return true;
	else
	{
		cout << "invalid order " << endl;
		return false;
	}
		
}

void Blockade::execute(Player* p, Territory* t)
{
	if (validate(p, t))
	{	
		int* num = t->getNumberOfArmies();
		t->setNumberOfArmies(*num * 2);
		cout << "Player has blockaded territory." << endl;
		//add a function to turn neutral
	}
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

bool Airlift::validate(Player* p, Territory* t, Territory* t1)
{
	if ((!p->isOwner(t)) && (!p->isOwner(t1))	)
	{
		cout << "invalid order " << endl;
		return false;
	}
	else
	{ 
		return true;
	}
}

void Airlift::execute(Player* p, Territory* t, Territory* t1, int num)
{
	if (validate(p, t, t1))
	{
		if (p->isOwner(t) && p->isOwner(t1))
		{
			cout << "Player has airlifted army to an friendly territory " << endl;
			t->numberOfArmies -= num;
			t1->numberOfArmies += num;
		}
		else
		{
			if (p->isOwner(t))
			{
				t->numberOfArmies -= num;
				int attackingforce = num;
				if (!t1->hasOwner())
				{
					p->addTerritory(t1);
					cout << "Player has occupied a neutral territory " << endl;
				}
				else
				{
					cout << "Player has airlifted army to enemies territory " << endl;
					cout << "Battle starts " << endl;
					for (int i = 0; i < num; i++)
					{
						int attack_chance, defend_chance;
						attack_chance = rand() % 100 + 1;
						defend_chance = rand() % 100 + 1;
						if (attack_chance <= 60)
							t1->numberOfArmies -= 1;
						if (defend_chance <= 70)
							attackingforce -= 1;

					}

					if (t1->numberOfArmies == 0)
					{
						p->addTerritory(t1);
						t1->numberOfArmies += attackingforce;
						//p.addCards();

						cout << "Player has conquered enemies' territory and gets a new card" << endl;
					}
				}
			}
			

		}
	}
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

bool Negotiate::validate(Player* p1, Player* p2)
{
	if (p1 == p2)
	{
		cout << "invalid order " << endl;
		return false;
	}
	else
	{
		return true;
	}
}

void Negotiate::execute(Player* p1, Player* p2)
{
	if (validate(p1, p2))
	{
		cout << "Player has started negotiation." << endl;
	}
}
void Negotiate::sticker()
{
	cout << "Negotiate";
}









