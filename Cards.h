#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <random>

#include "Player.h"



using namespace std;

class Card {
public:

	string types[5] = { "bomb", "reinforcement", "blockade", "airlift", "diplomacy" };
	Card(); //default constructor
	Card(string t); //constructor
	Card(const Card& card2); //copy constructor
	friend ostream& operator << (ostream& out, const Card& c); //stream insertion operator

	string getType();

private:
	string* type; //The card's type
};


class Deck
{
public:

	Deck(); //default constructor
	Deck(const Deck& deck2); //copy constructor 
	friend ostream& operator << (ostream& out, const Deck& d); //stream insertion operator

	//Card getCardAt(int index);
	Card draw();
	void add(Card newCard);

private:
	vector<Card>* cardsVector;
};

class Player
{
public:
	string getName() { return ""; }

};

class Hand
{
public:
	Hand(); //constructor
	Hand(const Hand& hand2); //copy constructor
	friend ostream& operator << (ostream& out, const Hand& h); //stream insertion operator

	void add(Card newCard);
	void playCard(int index, Deck deck);

	bool isEmpty();

private:
	Player* owner;
	vector<Card>* cardsVector;
};

