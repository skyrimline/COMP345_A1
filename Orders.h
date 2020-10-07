#pragma once
#include <iostream>
using namespace std;
class OrderList{
	public:
		OrderList();
		OrderList(string);
		OrderList(OrderList &OrderList, string olName);
		OrderList& operator = (const OrderList &p)
	{

		return *this;
	}
	
};
class Order : public OrderList {
	public:
		Order();
		Order(string);
		Order(Order &Order, string oName);
		Order& operator = (const Order &p)
		{

			return *this;
		}

	private:
		string oName;
};
