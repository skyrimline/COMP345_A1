
#include "Orders.h"
#include "Player.h"
#include "Map.h"
#include <algorithm>

using namespace std;

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
    list<Order> orderlist;
}

OrderList::OrderList(const OrderList &orderlist)
{
    *this = orderlist;
}

OrderList &OrderList::operator<<(const OrderList &p)
{
    return *this;
}

void OrderList::move(Order &p_order)
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

Deploy::Deploy(const Deploy &deploy)
{
    *this = deploy;
}

Deploy &Deploy::operator<<(const Deploy &p)
{
    return *this;
}

bool Deploy::validate(Player &p, Territory &t) //check if it is one kind of order
{
    if (find(p.getTerritories().begin(), p.getTerritories().end(), &t) != p.getTerritories().end())
        return true;
    else
    {
        cout << "invalid order " << endl;
        return false;
    }
}

void Deploy::execute(Player &p, Territory &t, int &num) //implement the order
{
    if (validate(p, t))
    {
        cout << "Player has deployed army of " + num << endl;
        *t.getNumberOfArmies() += num;
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

Advance::Advance(const Advance &advance)
{
    *this = advance;
}

Advance &Advance::operator<<(const Advance &p)
{
    return *this;
}

void Advance::sticker()
{
    cout << "Advance";
}

bool Advance::validate(Player &p, Territory &t, Territory *t1)
{
    if (t.isNeighbour(t1))
        return false;
    else if (find(p.getTerritories().begin(), p.getTerritories().end(), &t) != p.getTerritories().end())
        return true;
    else
    {
        cout << "invalid order " << endl;
        return false;
    }
}

void Advance::execute(Player &p, Territory &t, Territory *t1, int &num)
{
    if (validate(p, t, t1))
    {
        if (find(p.getTerritories().begin(), p.getTerritories().end(), &t) != p.getTerritories().end() && find(p.getTerritories().begin(), p.getTerritories().end(), t1) != p.getTerritories().end())
        {
            cout << "Player has advanced army of " + num << endl;
            *t.getNumberOfArmies() -= num;
            *t1->getNumberOfArmies() += num;
        }
        else
        {
            for (int i = 0; i < num; i++)
            {
                int attack_chance, defend_chance;
                attack_chance = rand() % 100 + 1;
                defend_chance = rand() % 100 + 1;
                if (attack_chance <= 60)
                    *t1->getNumberOfArmies() -= 1;
                if (attack_chance <= 70)
                    *t.getNumberOfArmies() -= 1;
            }
            if (*t1->getNumberOfArmies() == 0)
            {
                p.getTerritories().push_back(t1);
                // Card c;
                //p.cards.push_back(c);
                cout << "Player has conquered enemies' territory and gets a new card as reward" << endl;
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

Bomb::Bomb(const Bomb &bomb)
{
    *this = bomb;
}

Bomb &Bomb::operator=(const Bomb &p)
{
    return *this;
}

bool Bomb::validate(Player &p, Territory &t)
{
    if (find(p.getTerritories().begin(), p.getTerritories().end(), &t) != p.getTerritories().end())
        return false;
    else
        return true;
}

void Bomb::execute(Player &p, Territory &t)
{
    if (validate(p, t))
    {
        int *num = t.getNumberOfArmies();
        *num /= 2;
        cout << "Player has bombed enemies' territory, half of the armies are lost" << endl;
    }
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

Blockade::Blockade(const Blockade &blockade)
{
    *this = blockade;
}

Blockade &Blockade::operator=(const Blockade &p)
{
    return *this;
}

bool Blockade::validate()
{
    return true;
}

void Blockade::execute()
{
    if (validate())
        cout << "Player has blockaded." << endl;
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

Airlift::Airlift(const Airlift &airlift)
{
    *this = airlift;
}

Airlift &Airlift::operator=(const Airlift &p)
{
    return *this;
}

bool Airlift::validate(Player &p, Territory &t, Territory *t1)
{
    if (find(p.getTerritories().begin(), p.getTerritories().end(), &t) != p.getTerritories().end() || find(p.getTerritories().begin(), p.getTerritories().end(), t1) != p.getTerritories().end())
        return true;
    else
        return false;
}

void Airlift::execute(Player &p, Territory &t, Territory *t1, int &num)
{
    if (validate(p, t, t1))
        if (find(p.getTerritories().begin(), p.getTerritories().end(), &t) != p.getTerritories().end() && find(p.getTerritories().begin(), p.getTerritories().end(), t1) != p.getTerritories().end())
        {
            cout << "Player has airlifted army of " + num << endl;
            *t.getNumberOfArmies() -= num;
            *t1->getNumberOfArmies() += num;
        }
        else
        {
            if (find(p.getTerritories().begin(), p.getTerritories().end(), &t) != p.getTerritories().end())
            {
                for (int i = 0; i < num; i++)
                {
                    int attack_chance, defend_chance;
                    attack_chance = rand() % 100 + 1;
                    defend_chance = rand() % 100 + 1;
                    if (attack_chance <= 60)
                        *t1->getNumberOfArmies() -= 1;
                    if (attack_chance <= 70)
                        *t.getNumberOfArmies() -= 1;
                }
                if (*t1->getNumberOfArmies() == 0)
                {
                    p.getTerritories().push_back(t1);
                    // Card c;
                    //p.cards.push_back(c);
                    cout << "Player has conquered enemies' territory and gets a new card as reward" << endl;
                }
            }
        }
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

Negotiate::Negotiate(const Negotiate &negotiate)
{
    *this = negotiate;
}

Negotiate &Negotiate::operator=(const Negotiate &p)
{
    return *this;
}

bool Negotiate::validate()
{
    return true;
}

void Negotiate::execute()
{
    if (validate())
        cout << "Player has started negotiation." << endl;
    else
        cout << "" << endl;
}
void Negotiate::sticker()
{
    cout << "Negotiate";
}
