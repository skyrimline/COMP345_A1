#include <iostream>
#include <list>
#include "Orders.h"
#include "Orders.cpp"

int main() {
	OrderList OL1;
	deploy d1;
	bomb b1;
	blockade bl1;
	airlift al1;
	negotiate n1;
	d1.validate;
	d1.execute;
	OL1.move(d1);
	OL1.move(b1);
	OL1.remove(b1);

	return 0;
}
