#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <random>

class Player;

using namespace std;

class Card
{
public:
	static const string types[];

	Card();													 //default constructor
	Card(string t);											 //constructor
	Card(const Card &card2);								 //copy constructor
	friend ostream &operator<<(ostream &out, const Card &c); //stream insertion operator

	string getType();

private:
	string *type; //The card's type
};

class Deck
{
public:
	Deck();													 //default constructor
	Deck(const Deck &deck2);								 //copy constructor
	friend ostream &operator<<(ostream &out, const Deck &d); //stream insertion operator

	//Card getCardAt(int index);
	Card draw();
	void add(Card newCard);

private:
	vector<Card> *cardsVector;
};

class Hand
{
public:
	Hand();													 //constructor
	Hand(const Hand &hand2);								 //copy constructor
	friend ostream &operator<<(ostream &out, const Hand &h); //stream insertion operator

	void add(Card newCard);
	void playCard(int index, Deck deck);

	bool isEmpty();

private:
	Player *owner;
	vector<Card> *cardsVector;
};
