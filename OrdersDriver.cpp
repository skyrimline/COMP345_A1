
#include "Orders.h"


int main() 
{
	OrderList OL1;
	Deploy d1;
	Advance a1;
	Bomb b1;
	Blockade bl1;
	Airlift al1;
	Negotiate n1;

	d1.execute(d1);
	OL1.move(d1);
	OL1.remove(d1);
	a1.execute(a1);
	OL1.move(a1);
	OL1.remove(a1);
	b1.execute(b1);
	OL1.move(b1);
	OL1.remove(b1);
	bl1.execute(bl1);
	OL1.move(bl1);
	OL1.remove(bl1);
	al1.execute(al1);
	OL1.move(al1);
	OL1.remove(al1);
	n1.execute(n1);
	OL1.move(n1);
	OL1.remove(n1);

	

	return 0;
}
