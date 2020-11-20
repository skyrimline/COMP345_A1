
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

Deploy::Deploy(Player* p, Territory* territory, int numOfArmies)
{
    this->p=p;
	this->t=territory;
	this->numOfArmies=new int(numOfArmies);
}

Deploy::Deploy(const Deploy & deploy)
{
//	*this = deploy;
}

Deploy & Deploy::operator<<(const Deploy & p)
{
	return *this;
}

bool Deploy::validate()//check if it is one kind of order
{	if (p->isOwner(t))
		return true;
	else
	{
		cout << "invalid order " << endl;
		return false;
	}
}	

void Deploy::execute()//implement the order
{
	if (validate())
	{
        *t->numberOfArmies += *numOfArmies;
        *p->armies-=*numOfArmies;
		cout <<p->getName() <<" has deployed "<<*numOfArmies<<"army(ies) to"<<t->getName()<<"." << endl;
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

Advance::Advance(Player* p, Territory* t, Territory* t1, int numOfArmies)
{
    this->p=p;
	this->source = t;
	this->target=t1;
	this->numOfArmies=new int(numOfArmies);
}

Advance::Advance(const Advance & advance)
{
//	*this = advance;
}

Advance & Advance::operator<<(const Advance & p)
{
	return *this;
}

void Advance::sticker()
{
	cout << "Advance";
}

bool Advance::validate()
{
	if (p->isOwner(source)&&source->isNeighbour(target)) {
        return true;
    }
	else
	{
		cout << "invalid order " << endl;
		return false;
	}
}

void Advance::execute()
{
	if (validate())
	{
		if (p->isOwner(target))
		{
			cout << "You have advanced army to an friendly territory." << endl;
			*source->numberOfArmies -= *numOfArmies;
			*target->numberOfArmies += *numOfArmies;
		}
		else
		{
            cout << "You are attacking another territory!" << endl;
			*source->numberOfArmies -= *numOfArmies;
			int attackingForce = *numOfArmies;
				for (int i = 0; i < *numOfArmies; i++)
				{
					int attack_chance, defend_chance;
					attack_chance = rand() % 100 + 1;
					defend_chance = rand() % 100 + 1;
					if (attack_chance <= 60)
						*target->numberOfArmies -= 1;
					if (defend_chance <= 70)
						attackingForce -= 1;
					
				}
				if (target->numberOfArmies == 0)
				{
					p->addTerritory(target);
					*target->numberOfArmies += attackingForce;
					p->getHand()->getCardsVector().push_back(p->getHand()->getDeck()->draw());
					cout << "You have conquered an enemy's territory and get a new card" << endl;
				}
				else {
				    cout<<"You have lost the battle."<<endl;
                }
			}
			
		}
	}

Territory *Advance::getSource()  {
    return source;
}

Territory *Advance::getTarget() {
    return target;
}


//default constructor//constructor//copy constructor	
Bomb::Bomb()
{
}

Bomb::Bomb(Player* p, Territory* t)
{
	this->p = p;
	this->target=t;
}

Bomb::Bomb(const Bomb & bomb)
{
	*this = bomb;
}

Bomb & Bomb::operator=(const Bomb & p)
{
	return *this;
}

bool Bomb::validate()
{
	if (p->isOwner(target))
	{
		cout << "Invalid order, cannot bomb friendly territory!" << endl;
		return false;
	}
	else
	{
		cout << "valid " << endl;
		return true;
	}
}

void Bomb::execute()
{
	if (validate())
	{
		int* num = target->getNumberOfArmies();
		target->setNumberOfArmies(*num / 2);
		cout << "You have bombed an enemy's territory, half of the defensive armies are lost." << endl;
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

Blockade::Blockade(Player* p, Territory* t)
{
    this->p=p;
	this->t = t;
}

Blockade::Blockade(const Blockade & blockade)
{
	*this = blockade;
}

Blockade & Blockade::operator=(const Blockade & p)
{
	return *this;
}

bool Blockade::validate()
{
	if (p->isOwner(t))
		return true;
	else
	{
		cout << "invalid order " << endl;
		return false;
	}
		
}

void Blockade::execute()
{
	if (validate())
	{	
		int* num = t->getNumberOfArmies();
		t->setNumberOfArmies(*num * 2);
		t->setNeutral();
		cout << "You have blockaded this territory." << endl;
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

Airlift::Airlift(Player* p, Territory* territory, Territory* territory1, int numOfArmies)
{
    this->p=p;
	this->source=territory;
	this->target=territory1;
	this->numOfArmies=new int(numOfArmies);
}

Airlift::Airlift(const Airlift & airlift)
{
	*this = airlift;
}

Airlift & Airlift::operator=(const Airlift & p)
{
	return *this;
}

bool Airlift::validate()
{
	if ((!p->isOwner(source)))
	{
		cout << "invalid order " << endl;
		return false;
	}
	else
	{ 
		return true;
	}
}

void Airlift::execute()
{
	if (validate())
	{
        if (p->isOwner(target))
        {
            cout << "You have airlifted army to a friendly territory." << endl;
            *source->numberOfArmies -= *numOfArmies;
            *target->numberOfArmies += *numOfArmies;
        }
        else
        {
            cout << "You are attacking another territory!" << endl;
            *source->numberOfArmies -= *numOfArmies;
            int attackingForce = *numOfArmies;
            for (int i = 0; i < *numOfArmies; i++)
            {
                int attack_chance, defend_chance;
                attack_chance = rand() % 100 + 1;
                defend_chance = rand() % 100 + 1;
                if (attack_chance <= 60)
                    *target->numberOfArmies -= 1;
                if (defend_chance <= 70)
                    attackingForce -= 1;
            }
            if (target->numberOfArmies == 0)
            {
                p->addTerritory(target);
                *target->numberOfArmies += attackingForce;
                p->getHand()->getCardsVector().push_back(p->getHand()->getDeck()->draw());
                cout << "You have conquered an enemy's territory and get a new card" << endl;
            }
            else {
                cout<<"You have lost the battle."<<endl;
            }
        }

	}
}

void Airlift::sticker()
{
	cout << "Airlift";
}

Territory *Airlift::getSource() {
    return source;
}

Territory *Airlift::getTarget() {
    return target;
}


//default constructor//constructor//copy constructor
Negotiate::Negotiate()
{
}

Negotiate::Negotiate(Player* p1, Player* p2)
{
	this->p1 = p1;
	this->p2=p2;
}

Negotiate::Negotiate(const Negotiate & negotiate)
{
	*this = negotiate;
}

Negotiate & Negotiate::operator=(const Negotiate & p)
{
	return *this;
}

bool Negotiate::validate()
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

void Negotiate::execute()
{
	if (validate())
	{
		cout << "Player has started negotiation, and all attacks have been removed." << endl;
//		for(int i=0;i<p1->getOrders().size();i++){
//		    if(p1->getOrders()[i]->getType()=="advance"){
//		        Advance* advance=dynamic_cast<Advance*>(p1->getOrders()[i]);
//		        if(advance->getTarget()->getOwner()==p2){
//                    p1->getOrders().erase(p1->getOrders().begin()+i);
//		        }
//		    }
//		    else if(p1->getOrders()[i]->getType()=="airlift"){
//                Airlift* advance=dynamic_cast<Airlift*>(p1->getOrders()[i]);
//                if(advance->getTarget()->getOwner()==p2){
//                    p1->getOrders().erase(p1->getOrders().begin()+i);
//                }
//            }
//		}
//        for(int i=0;i<p2->getOrders().size();i++){
//            if(p2->getOrders()[i]->getType()=="advance"){
//                Advance* advance=dynamic_cast<Advance*>(p2->getOrders()[i]);
//                if(advance->getTarget()->getOwner()==p1){
//                    p2->getOrders().erase(p2->getOrders().begin()+i);
//                }
//            }
//            else if(p2->getOrders()[i]->getType()=="airlift"){
//                Airlift* advance=dynamic_cast<Airlift*>(p2->getOrders()[i]);
//                if(advance->getTarget()->getOwner()==p1){
//                    p2->getOrders().erase(p2->getOrders().begin()+i);
//                }
//            }
//        }
	}
}

void Negotiate::sticker()
{
	cout << "Negotiate";
}









