
#include "Orders.h"
#include "Player.h"


int main() 
{
	
	
	Deploy *d1 = new Deploy();
	Advance *a1 = new Advance();
	Bomb *b1 = new Bomb();
	Blockade *bl1 = new Blockade();
	Airlift *al1 = new Airlift();
	Negotiate *n1 = new Negotiate();
	Player *p1 = new Player();
	Player *p2 = new Player();
	Territory *t1 = new Territory();
	Territory *t2 = new Territory();

	//test start
	p1->addTerritory(t1);
	//p1.addTerritory(t2);
	p2->addTerritory(t2);
	t1->addNeighbour(t2);
	t1->setNumberOfArmies(4);
	t2->setNumberOfArmies(4);
	int* numbefore = t1->getNumberOfArmies();
	
	/*
	d1->validate(p1, t1);
	d1->execute(p1, t1, 3);
	
	a1->validate(p1, t1, t2);
	a1->execute(p1, t1, t2, 3);

	al1->validate(p1, t1, t2);
	al1->execute(p1, t1, t2, 3);

	b1->validate(p1, t2);
	b1->execute(p1, t2);
	int* numafter = t2->getNumberOfArmies();
	cout << *numbefore << endl;
	cout << *numafter << endl;


	bl1->validate(p1, t1);
	bl1->execute(p1, t1);
	int* numafter = t1->getNumberOfArmies();
	cout << *numbefore << endl;
	cout << *numafter << endl;


	n1->validate(p1, p2);
	n1->execute(p1, p2);


	*/
	
	

	

	

	return 0;
	
}
